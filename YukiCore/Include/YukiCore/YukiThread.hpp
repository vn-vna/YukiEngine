#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Core
{

using YukiThreadCallbackFuncType = std::function<void()>;

class YUKIAPI IYukiThread
{
public:
  virtual void         Start()                                         = 0;
  virtual void         Suspend()                                       = 0;
  virtual void         WaitForThread(unsigned long timeOut = INFINITE) = 0;
  virtual void         RunCallback()                                   = 0;
  virtual const DWORD& GetID()                                         = 0;
  virtual const HANDLE GetHandler()                                    = 0;
};

class YUKIAPI IYukiMutex
{
public:
  virtual void   LockMutex()   = 0;
  virtual void   UnlockMutex() = 0;
  virtual HANDLE GetHandler()  = 0;
};

SharedPtr<IYukiThread> YUKIAPI CreateYukiThread();
SharedPtr<IYukiThread> YUKIAPI CreateYukiThread(const YukiThreadCallbackFuncType& callback);
SharedPtr<IYukiThread> YUKIAPI CreateYukiThread(const SharedPtr<YukiThreadCallbackFuncType>& pcallback);
SharedPtr<IYukiMutex> YUKIAPI  CreateYukiMutex();
void YUKIAPI                   WaitForThreads(std::initializer_list<SharedPtr<IYukiThread>> threads, bool waitAll = true, unsigned long timeOut = INFINITE);

} // namespace Yuki::Core
