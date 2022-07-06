/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiDebug/Loggers.hpp"
#include "YukiCore/ThreadPool.hpp"
#include "YukiDebug/Errors.hpp"
#include "YukiUtil/Chrono.hpp"

namespace Yuki::Core
{

using Chrono::MiliSeconds;

class YukiThreadPool final : virtual public IYukiThreadPool
{
public:
  YukiThreadPool(int poolSize, bool oglContext);
  ~YukiThreadPool();

  void Start() override;
  void Join() override;
  void PushAction(const CallbackFunc& callback) override;
  void Terminate() override;
  void WaitForPoolReady() override;
  void NotifyWorkers() override;

  Vector<Thread>&      GetWorkers() override;
  ConditionVariable&   GetWorkerWaiter() override;
  Mutex&               GetActionQueueMutex() override;
  Queue<CallbackFunc>& GetActionQueue() override;
  CallbackFunc&        GetWorkerFuncCallback() override;
  bool                 IsPoolActive() override;
  bool                 IsPoolStarted() override;

private:
  SharedPtr<ThreadPoolManager> m_pManager;
  Mutex                        m_PoolMutex;
  Mutex                        m_ActionQueueMutex;
  Vector<Thread>               m_aWorkers;
  ConditionVariable            m_ActionQueueWaiter;
  Queue<CallbackFunc>          m_ActionQueue;
  CallbackFunc                 m_WorkerFunc;
  Atomic<bool>                 m_bPoolActive;
  Atomic<bool>                 m_bPoolStarted;
  Atomic<int>                  m_nNumThreadReady;
  ConditionVariable            m_PoolWaiter;
  bool                         m_bCreateOGLContext;
};

} // namespace Yuki::Core
