/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiCore/YukiThread.hpp"
#include "YukiDebug/YukiError.hpp"

namespace Yuki::Core
{

class YukiThread final : virtual public IYukiThread
{
protected:
  ThreadType                 m_CppThread;
  YukiThreadCallbackFuncType m_fnCallback;
  bool                       m_bThreadReady;

public:
  explicit YukiThread(const YukiThreadCallbackFuncType& callback);
  ~YukiThread();

  void Start() override;
  void Join() override;
  void Detach() override;
  void Swap(SharedPtr<IYukiThread> thread) override;

  bool         IsJoinable() override;
  ThreadIDType GetThreadID() override;
  ThreadType&  GetRawThread() override;
};

class YukiMutex final : public IYukiMutex
{
protected:
public:
};

} // namespace Yuki::Core
