#pragma once

#include "YukiCore/YukiObject.hpp"

// std
#include <thread>

namespace Yuki::Core
{

using YukiThreadCallbackFuncType = std::function<void()>;
using ThreadType                 = std::thread;
using ThreadIDType               = std::thread::id;

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

unsigned YUKIAPI               GetHardwareConcurrency();
SharedPtr<IYukiThread> YUKIAPI CreateYukiThread(const YukiThreadCallbackFuncType& callback);
SharedPtr<IYukiThread> YUKIAPI CreateYukiThread(SharedPtr<YukiThreadCallbackFuncType> pcallback);
SharedPtr<IYukiMutex> YUKIAPI  CreateYukiMutex();
void YUKIAPI                   WaitForThreads(std::initializer_list<SharedPtr<IYukiThread>> threads, bool waitAll = true, unsigned long timeOut = INFINITE);

} // namespace Yuki::Core
