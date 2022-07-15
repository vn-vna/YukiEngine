/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Objects.hpp"

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

typedef UnorderedSet<IThreadPool*> ThreadPoolManager;
typedef VoidNParamCallback         CallbackFunc;

class IThreadPool
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
};

unsigned                     GetHardwareConcurrency();
void                         InvokeAllThreads();
SharedPtr<ThreadPoolManager> GetThreadPoolManager();
SharedPtr<IThreadPool>       CreateThreadPool(int  poolSize   = -1,
                                              bool oglContext = true);

} // namespace Yuki::Core
