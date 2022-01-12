#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Core
{

using YukiThreadCallbackFuncType = std::function<void()>;

class YUKIAPI IYukiThread
{
public:
  IYukiThread()          = default;
  virtual ~IYukiThread() = default;

  virtual void         Start()                                    = 0;
  virtual void         Suspend()                                  = 0;
  virtual void         WaitForThread(unsigned long timeOut = INFINITE) = 0;
  virtual void         RunCallback()                              = 0;
  virtual const DWORD& GetID()                                    = 0;
  virtual const HANDLE GetHandler()                               = 0;
};

class YUKIAPI YukiThread : public IYukiThread
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

  static void WaitForThreads(std::initializer_list<SharedPtr<IYukiThread>> threads, bool waitAll = true, unsigned long timeOut = INFINITE);
};

} // namespace Yuki::Core