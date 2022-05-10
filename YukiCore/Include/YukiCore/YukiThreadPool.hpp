/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiObject.hpp"

// std
#include <thread>
#include <condition_variable>
#include <chrono>
#include <thread>

namespace Yuki::Core
{

using Thread            = std::thread;
using ThreadID          = std::thread::id;
using ConditionVariable = std::condition_variable;
using Mutex             = std::mutex;

typedef UnorderedSet<IYukiThreadPool*> ThreadPoolManager;
typedef VoidNParamCallback             CallbackFunc;

class YUKIAPI IYukiThreadPool
{
public:
  virtual void Start()                                = 0;
  virtual void Join()                                 = 0;
  virtual void PushAction(const CallbackFunc& action) = 0;
  virtual void Terminate()                            = 0;
  virtual void WaitForPoolReady()                     = 0;
  virtual void NotifyWorkers()                        = 0;

  virtual Vector<Thread>&      GetWorkers()            = 0;
  virtual ConditionVariable&   GetWorkerWaiter()       = 0;
  virtual Mutex&               GetActionQueueMutex()   = 0;
  virtual Queue<CallbackFunc>& GetActionQueue()        = 0;
  virtual CallbackFunc&        GetWorkerFuncCallback() = 0;
  virtual bool                 IsPoolActive()          = 0;
  virtual bool                 IsPoolStarted()         = 0;
  virtual long long            GetInvokeInterval()     = 0;
};

unsigned YUKIAPI                     GetHardwareConcurrency();
void YUKIAPI                         InvokeAllThreads();
SharedPtr<ThreadPoolManager> YUKIAPI GetThreadPoolManager();
SharedPtr<IYukiThreadPool> YUKIAPI   CreateThreadPool(int poolSize = -1);

} // namespace Yuki::Core
