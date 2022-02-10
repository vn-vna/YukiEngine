#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiCore/YukiThread.hpp"
#include "YukiDebug/YukiError.hpp"

DWORD CALLBACK Win32APIThreadCallback(LPVOID args);

namespace Yuki::Core
{

class YukiThread : public virtual IYukiThread
{
protected:
  SharedPtr<YukiThreadCallbackFuncType> m_pfnRunnable;
  DWORD                                 m_nThreadID;
  HANDLE                                m_pHandle;

  void CreateWin32Thread();
  void AttachWin32Thread();
  void DestroyWin32Thread();
  void DetachWin32Thread();

public:
  YukiThread();
  YukiThread(const YukiThreadCallbackFuncType& callback);
  YukiThread(const SharedPtr<YukiThreadCallbackFuncType>& pcallback);

  virtual ~YukiThread();

  void         Start() override;
  void         Suspend() override;
  void         WaitForThread(unsigned long timeOut = INFINITE) override;
  void         RunCallback() override;
  const DWORD& GetID() override;
  const HANDLE GetHandler() override;
};

class YukiMutex : public IYukiMutex
{
protected:
  HANDLE m_pMutexHandler;

public:
  YukiMutex();
  virtual ~YukiMutex();

  void   LockMutex() override;
  void   UnlockMutex() override;
  HANDLE GetHandler() override;
};

} // namespace Yuki::Core