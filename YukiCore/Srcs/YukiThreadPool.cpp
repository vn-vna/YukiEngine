#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiWindow.hpp"
#include "YukiCore/YukiObject.hpp"

#include "PYukiThreadPool.hpp"

namespace Yuki::Core
{

YukiThreadPool::YukiThreadPool(int poolSize, bool oglContext)
    : m_pManager(GetThreadPoolManager()), m_aWorkers(), m_ActionQueue(), m_ActionQueueMutex(), m_ActionQueueWaiter(),
      m_PoolWaiter(), m_bPoolActive(false), m_bPoolStarted(false), m_nNumThreadReady(0),
      m_bCreateOGLContext(oglContext), m_WorkerFunc([&]() {
        bool threadReady = false;
        ++m_nNumThreadReady;
        if (m_nNumThreadReady == m_aWorkers.capacity())
        {
          m_PoolWaiter.notify_all();
        }

        while (m_bPoolActive)
        {
          std::unique_lock<std::mutex> locker{m_ActionQueueMutex, std::defer_lock};

          locker.lock();
          bool queueEmpty = m_ActionQueue.empty();

          if (queueEmpty)
          {
            m_ActionQueueWaiter.wait(locker);
            locker.unlock();
            continue;
          }

          if (!m_bPoolActive)
          {
            break;
          }

          AutoType action = this->m_ActionQueue.front();
          m_ActionQueue.pop();
          locker.unlock();
          if (action)
          {
            action();
          }
        }

        --m_nNumThreadReady;
      })
{
  if (poolSize < 1)
  {
    poolSize = (int) GetHardwareConcurrency();
  }
  m_aWorkers.reserve(poolSize);
}


YukiThreadPool::~YukiThreadPool() = default;

void YukiThreadPool::Start()
{
  if (m_bPoolStarted)
  {
    THROW_YUKI_ERROR(ThreadPoolAlreadyStarted);
  }

  if (m_bCreateOGLContext) {}

  m_bPoolActive = true;
  for (int i = 0; i < m_aWorkers.capacity(); ++i)
  {
    m_aWorkers.emplace_back(m_WorkerFunc);
  }

  // m_ManagerThread = std::thread(m_ManagerFunc);
}

void YukiThreadPool::Join()
{
  for (AutoType& worker : this->m_aWorkers)
  {
    if (worker.joinable())
    {
      worker.join();
    }
  }

  // m_ManagerThread.join();
}

void YukiThreadPool::PushAction(const CallbackFunc& callback) { m_ActionQueue.push(callback); }

void YukiThreadPool::Terminate()
{
  m_bPoolActive = false;

  while (m_nNumThreadReady)
  {
    this->NotifyWorkers();
  }
}

void YukiThreadPool::WaitForPoolReady()
{
  std::unique_lock<std::mutex> locker{m_PoolMutex};
  m_PoolWaiter.wait(locker);
}

void YukiThreadPool::NotifyWorkers() { m_ActionQueueWaiter.notify_all(); }

Vector<Thread>& YukiThreadPool::GetWorkers() { return m_aWorkers; }

ConditionVariable& YukiThreadPool::GetWorkerWaiter() { return m_ActionQueueWaiter; }

Mutex& YukiThreadPool::GetActionQueueMutex() { return m_ActionQueueMutex; }

Queue<CallbackFunc>& YukiThreadPool::GetActionQueue() { return m_ActionQueue; }

CallbackFunc& YukiThreadPool::GetWorkerFuncCallback() { return m_WorkerFunc; }

bool YukiThreadPool::IsPoolActive() { return m_bPoolActive; }

bool YukiThreadPool::IsPoolStarted() { return m_bPoolStarted; }

void InvokeAllThreads()
{
  AutoType manager = GetThreadPoolManager();
  for (AutoType pool : *manager)
  {
    if (pool)
    {
      if (pool->GetActionQueue().empty())
      {
        continue;
      }
      pool->GetWorkerWaiter().notify_all();
    }
  }
}

unsigned GetHardwareConcurrency() { return std::thread::hardware_concurrency(); }

SharedPtr<ThreadPoolManager> GetThreadPoolManager()
{
  static SharedPtr<ThreadPoolManager> pTPManager;
  if (!pTPManager.get())
  {
    pTPManager = std::make_shared<ThreadPoolManager>();
  }
  return pTPManager;
}

SharedPtr<IYukiThreadPool> CreateThreadPool(int poolSize, bool oglContext)
{
  AutoType manager = GetThreadPoolManager();

  AutoType deleter = [manager](IYukiThreadPool* p) {
    manager->erase(p);
    delete dynamic_cast<YukiThreadPool*>(p);
  };

  SharedPtr<IYukiThreadPool> pThreadPool{
      dynamic_cast<IYukiThreadPool*>(new YukiThreadPool{poolSize, oglContext}), deleter};
  if (manager->find(pThreadPool.get()) != manager->end())
  {
    THROW_YUKI_ERROR(ThreadPoolManagerDuplicateKey);
  }

  manager->emplace(pThreadPool.get());
  return pThreadPool;

  return pThreadPool;
}

} // namespace Yuki::Core