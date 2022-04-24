#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"

#include "PYukiThread.hpp"

namespace Yuki::Core
{

YukiThread::YukiThread(const YukiThreadCallbackFuncType& callback)
    : m_fnCallback(callback),
      m_bThreadReady(false),
      m_CppThread()
{}

YukiThread::~YukiThread() = default;

void YukiThread::Start()
{
  m_CppThread    = ThreadType{m_fnCallback};
  m_bThreadReady = true;
}

void YukiThread::Join()
{
  m_CppThread.join();
}

void YukiThread::Detach()
{
  m_CppThread.detach();
}

void YukiThread::Swap(SharedPtr<IYukiThread> thread)
{
  m_CppThread.swap(thread->GetRawThread());
}

bool YukiThread::IsJoinable()
{
  return m_CppThread.joinable();
}

ThreadIDType YukiThread::GetThreadID()
{
  return m_CppThread.get_id();
}

ThreadType& YukiThread::GetRawThread()
{
  return m_CppThread;
}

} // namespace Yuki::Core