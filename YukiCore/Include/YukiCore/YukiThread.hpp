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

namespace Yuki::Core
{

using CallbackFuncType = std::function<void()>;
using ThreadType       = std::thread;
using ThreadIDType     = std::thread::id;

class YUKIAPI IYukiThread
{
public:
  virtual void Start()                             = 0;
  virtual void Join()                              = 0;
  virtual void Detach()                            = 0;
  virtual void Swap(SharedPtr<IYukiThread> thread) = 0;

  virtual bool         IsJoinable()   = 0;
  virtual ThreadIDType GetThreadID()  = 0;
  virtual ThreadType&  GetRawThread() = 0;
};

class YUKIAPI IYukiMutex
{
public:
  virtual void Lock()   = 0;
  virtual void UnLock() = 0;
};

class YUKIAPI IYukiThreadPool
{
public:
  virtual void Start()                                    = 0;
  virtual void Join()                                     = 0;
  virtual void PushAction(const CallbackFuncType& action) = 0;
  virtual void Terminate()                                = 0;
};

unsigned YUKIAPI                   GetHardwareConcurrency();
SharedPtr<IYukiThread> YUKIAPI     CreateYukiThread(const CallbackFuncType& callback);
SharedPtr<IYukiThread> YUKIAPI     CreateYukiThread(SharedPtr<CallbackFuncType> pcallback);
SharedPtr<IYukiMutex> YUKIAPI      CreateYukiMutex();
SharedPtr<IYukiThreadPool> YUKIAPI CreateThreadPool(int poolSize = -1, long long invokeInterval = 30);
void YUKIAPI                       WaitForThreads(std::initializer_list<SharedPtr<IYukiThread>> threads, bool waitAll = true, unsigned long timeOut = INFINITE);

} // namespace Yuki::Core
