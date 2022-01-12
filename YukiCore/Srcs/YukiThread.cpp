#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiThread.hpp"
#include "YukiCore/YukiError.hpp"

std::map<DWORD, Yuki::Core::IYukiThread*> g_mThreadManager{};

DWORD CALLBACK Win32APIThreadCallback(LPVOID args)
{
  AutoType threadID    = (DWORD*) args;
  AutoType pYukiThread = g_mThreadManager.at(*threadID);
  if (pYukiThread)
  {
    pYukiThread->RunCallback();
  }
  return 0;
}

namespace Yuki::Core
{

YukiThread::YukiThread()
    : m_pfnRunnable(nullptr),
      m_nThreadID(0),
      m_pHandle(nullptr)
{}

YukiThread::YukiThread(const YukiThreadCallbackFuncType& callback)
    : m_pfnRunnable(new YukiThreadCallbackFuncType{callback}),
      m_nThreadID(0),
      m_pHandle(nullptr)
{}

YukiThread::YukiThread(const SharedPtr<YukiThreadCallbackFuncType>& pcallback)
    : m_pfnRunnable(pcallback),
      m_nThreadID(0),
      m_pHandle(nullptr)
{}

YukiThread::~YukiThread()
{
  DestroyWin32Thread();
}

void YukiThread::CreateWin32Thread()
{
  m_pHandle = CreateThread(NULL, 0, Win32APIThreadCallback, &m_nThreadID, CREATE_SUSPENDED, &m_nThreadID);
  if (!m_pHandle)
  {
    THROW_YUKI_ERROR(Debug::YukiThreadCreationError);
  }
  AttachWin32Thread();
}

void YukiThread::AttachWin32Thread()
{
  if (g_mThreadManager.find(m_nThreadID) != g_mThreadManager.end())
  {
    THROW_YUKI_ERROR(Debug::YukiThreadAssignmentDuplicateThreadIdError);
  }
  g_mThreadManager.emplace(m_nThreadID, this);
}

void YukiThread::DestroyWin32Thread()
{
  if (m_pHandle)
  {
    CloseHandle(m_pHandle);
    m_pHandle = nullptr;
    DetachWin32Thread();
  }
}

void YukiThread::DetachWin32Thread()
{
  if (g_mThreadManager.find(m_nThreadID) == g_mThreadManager.end())
  {
    THROW_YUKI_ERROR(Debug::YukiThreadDetachmentNotExistError);
  }
  g_mThreadManager.erase(m_nThreadID);
}

void YukiThread::Start()
{
  if (m_pHandle)
  {
    DestroyWin32Thread();
  }
  CreateWin32Thread();
  if (m_pHandle)
  {
    ResumeThread(m_pHandle);
  }
}

void YukiThread::Suspend()
{
  SuspendThread(m_pHandle);
}

void YukiThread::WaitForThread(unsigned long timeOut)
{
  WaitForSingleObject(m_pHandle, timeOut);
}

void YukiThread::RunCallback()
{
  if (m_pfnRunnable)
  {
    (*m_pfnRunnable)();
  }
}

const DWORD& YukiThread::GetID()
{
  return m_nThreadID;
}

const HANDLE YukiThread::GetHandler()
{
  return m_pHandle;
}

void YukiThread::WaitForThreads(std::initializer_list<SharedPtr<IYukiThread>> threads, bool waitAll, unsigned long timeOut)
{
  std::vector<HANDLE> handlers;
  handlers.reserve(threads.size());
  for (auto& t : threads)
  {
    handlers.emplace_back(t->GetHandler());
  }
  WaitForMultipleObjects(handlers.size(), handlers.data(), waitAll, timeOut);
}

} // namespace Yuki::Core