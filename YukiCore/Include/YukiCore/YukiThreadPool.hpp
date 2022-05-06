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
#include <atomic>

namespace Yuki::Core
{

using CallbackFuncType  = std::function<void()>;
using Thread            = std::thread;
using ThreadID          = std::thread::id;
using ConditionVariable = std::condition_variable;
using Mutex             = std::mutex;

template <typename T>
using Atomic = std::atomic<T>;

class YUKIAPI IYukiThreadPool
{
public:
  virtual void Start()                                    = 0;
  virtual void Join()                                     = 0;
  virtual void PushAction(const CallbackFuncType& action) = 0;
  virtual void Terminate()                                = 0;

  virtual const Vector<Thread>&          GetWorkers()             = 0;
  virtual const Thread&                  GetManagerThread()       = 0;
  virtual const ConditionVariable&       GetWorkerWaiter()        = 0;
  virtual const Mutex&                   GetActionQueueMutex()    = 0;
  virtual const Queue<CallbackFuncType>& GetActionQueue()         = 0;
  virtual const CallbackFuncType&        GetWorkerFuncCallback()  = 0;
  virtual const CallbackFuncType&        GetManagerFuncCallback() = 0;
  virtual bool                           IsPoolActive()           = 0;
  virtual bool                           IsPoolStarted()          = 0;
  virtual long long                      GetInvokeInterval()      = 0;
};

unsigned YUKIAPI                   GetHardwareConcurrency();
SharedPtr<IYukiThreadPool> YUKIAPI CreateThreadPool(int poolSize = -1, long long invokeInterval = 100);

} // namespace Yuki::Core
