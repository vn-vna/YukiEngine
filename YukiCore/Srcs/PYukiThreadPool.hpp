/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiCore/YukiThreadPool.hpp"
#include "YukiDebug/YukiError.hpp"

namespace Yuki::Core
{

class YukiThreadPool final : virtual public IYukiThreadPool
{
protected:
  Vector<Thread>            m_aWorkers;
  Thread                    m_ManagerThread;
  ConditionVariable         m_ActionQueueWaiter;
  Mutex                     m_ActionQueueMutex;
  Queue<CallbackFuncType>   m_ActionQueue;
  CallbackFuncType          m_WorkerFunc;
  CallbackFuncType          m_ManagerFunc;
  Atomic<bool>              m_bPoolActive;
  Atomic<bool>              m_bPoolStarted;
  std::chrono::milliseconds m_tInvokeInterval;


public:
  explicit YukiThreadPool(int poolSize, long long invokeInterval);
  ~YukiThreadPool() = default;

  void Start() override;
  void Join() override;
  void PushAction(const CallbackFuncType& callback) override;
  void Terminate() override;

  const Vector<Thread>&          GetWorkers() override;
  const Thread&                  GetManagerThread() override;
  const ConditionVariable&       GetWorkerWaiter() override;
  const Mutex&                   GetActionQueueMutex() override;
  const Queue<CallbackFuncType>& GetActionQueue() override;
  const CallbackFuncType&        GetWorkerFuncCallback() override;
  const CallbackFuncType&        GetManagerFuncCallback() override;
  bool                           IsPoolActive() override;
  bool                           IsPoolStarted() override;
  long long                      GetInvokeInterval() override;
};

} // namespace Yuki::Core
