#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiObject.hpp"

#include "PYukiThreadPool.hpp"

namespace Yuki::Core
{

YukiThreadPool::YukiThreadPool(int poolSize, long long invokeInterval)
    : m_aWorkers(),
      m_ActionQueue(),
      m_ActionQueueMutex(),
      m_ActionQueueWaiter(),
      m_tInvokeInterval(invokeInterval),
      m_bPoolActive(false),
      m_bPoolStarted(false),
      m_WorkerFunc([&]() {
        std::unique_lock<std::mutex> locker{this->m_ActionQueueMutex, std::defer_lock};
        while (true)
        {
          locker.lock();

          if (this->m_ActionQueue.empty())
          {
            this->m_ActionQueueWaiter.wait(locker);
            continue;
          }

          AutoType action = this->m_ActionQueue.front();
          this->m_ActionQueue.pop();
          locker.unlock();
          action();
        }
      }),
      m_ManagerFunc([&]() {
        this->m_bPoolStarted = true;
        while (this->m_bPoolActive)
        {
          std::lock_guard<std::mutex> queue_lock_guard{this->m_ActionQueueMutex};
          if (!this->m_ActionQueue.empty())
          {
            this->m_ActionQueueWaiter.notify_all();
          }
          std::this_thread::sleep_for(this->m_tInvokeInterval);
        }
        m_bPoolStarted = false;
      })
{
  if (poolSize < 1)
  {
    poolSize = std::thread::hardware_concurrency();
  }
  m_aWorkers.reserve(poolSize);
}

void YukiThreadPool::Start()
{
  if (m_bPoolStarted)
  {
    THROW_YUKI_ERROR(ThreadPoolAlreadyStarted);
  }

  m_bPoolActive = true;
  for (int i = 0; i < m_aWorkers.capacity(); ++i)
  {
    m_aWorkers.emplace_back(m_WorkerFunc);
  }


  m_ManagerThread = std::thread(m_ManagerFunc);
}

void YukiThreadPool::Join()
{

  for (AutoType& worker : m_aWorkers)
  {
    worker.join();
  }

  m_ManagerThread.join();
}

void YukiThreadPool::PushAction(const CallbackFuncType& callback)
{
  m_ActionQueue.push(callback);
}

void YukiThreadPool::Terminate()
{
  m_bPoolActive = false;
}

const Vector<Thread>& YukiThreadPool::GetWorkers()
{
  return m_aWorkers;
}

const Thread& YukiThreadPool::GetManagerThread()
{
  return m_ManagerThread;
}

const ConditionVariable& YukiThreadPool::GetWorkerWaiter()
{
  return m_ActionQueueWaiter;
}

const Mutex& YukiThreadPool::GetActionQueueMutex()
{
  return m_ActionQueueMutex;
}

const Queue<CallbackFuncType>& YukiThreadPool::GetActionQueue()
{
  return m_ActionQueue;
}

const CallbackFuncType& YukiThreadPool::GetWorkerFuncCallback()
{
  return m_WorkerFunc;
}

const CallbackFuncType& YukiThreadPool::GetManagerFuncCallback()
{
  return m_ManagerFunc;
}

bool YukiThreadPool::IsPoolActive()
{
  return m_bPoolActive;
}

bool YukiThreadPool::IsPoolStarted()
{
  return m_bPoolStarted;
}

long long YukiThreadPool::GetInvokeInterval()
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(m_tInvokeInterval).count();
}

SharedPtr<IYukiThreadPool> YUKIAPI CreateThreadPool(int poolSize, long long invokeInterval)
{
  return CreateInterfaceInstance<IYukiThreadPool, YukiThreadPool>(poolSize, invokeInterval);
}

} // namespace Yuki::Core