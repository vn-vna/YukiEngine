#include "YukiCore/YukiPCH.hpp"

#include "PYukiThread.hpp"

std::map<DWORD, Yuki::Core::IYukiThread*> g_mThreadManager{};

DWORD CALLBACK Win32APIThreadCallback(LPVOID args)
{
  AutoType threadID    = (DWORD*) args;
  AutoType pYukiThread = g_mThreadManager.at(*threadID);
  if (pYukiThread)
  {
    try
    {
      pYukiThread->RunCallback();
    }
    catch (Yuki::Debug::YukiError& err)
    {
      Yuki::Core::GetYukiApp()->GetLogger()->PushDebugMessage(err.getErrorMessage());
    }
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
  if (!m_pHandle)
  {
    return;
  }
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

YukiMutex::YukiMutex()
{
  m_pMutexHandler = CreateMutexW(NULL, FALSE, NULL);
  if (!m_pMutexHandler)
  {
    THROW_YUKI_ERROR(Debug::YukiMutexCreationError);
  }
}

YukiMutex::~YukiMutex()
{
  if (m_pMutexHandler)
  {
    CloseHandle(m_pMutexHandler);
  }
}

void YukiMutex::LockMutex()
{
  DWORD mutexWaitResult = WaitForSingleObject(m_pMutexHandler, INFINITE);
  switch (mutexWaitResult)
  {
  case WAIT_OBJECT_0:
    break;
  case WAIT_ABANDONED:
    THROW_YUKI_ERROR(Debug::YukiMutexWaitAbandoned);
  case WAIT_FAILED:
    THROW_YUKI_ERROR(Debug::YukiMutexWaitFunctionFailed);
  default:
    break;
  }
}

void YukiMutex::UnlockMutex()
{
  ReleaseMutex(m_pMutexHandler);
}

HANDLE YukiMutex::GetHandler()
{
  return m_pMutexHandler;
}

SharedPtr<IYukiThread> CreateYukiThread()
{
  return {(IYukiThread*) new YukiThread(), std::default_delete<IYukiThread>()};
}

SharedPtr<IYukiThread> CreateYukiThread(const YukiThreadCallbackFuncType& callback)
{
  return {(IYukiThread*) new YukiThread(callback), std::default_delete<IYukiThread>()};
}

SharedPtr<IYukiThread> CreateYukiThread(const SharedPtr<YukiThreadCallbackFuncType>& pcallback)
{
  return {(IYukiThread*) new YukiThread(pcallback), std::default_delete<IYukiThread>()};
}

SharedPtr<IYukiMutex> CreateYukiMutex()
{
  return {(IYukiMutex*) new YukiMutex(), std::default_delete<IYukiMutex>()};
}

void WaitForThreads(std::initializer_list<SharedPtr<IYukiThread>> threads, bool waitAll, unsigned long timeOut)
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