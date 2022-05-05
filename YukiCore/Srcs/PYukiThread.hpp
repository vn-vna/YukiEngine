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
#include "YukiCore/YukiThread.hpp"
#include "YukiDebug/YukiError.hpp"

#include <condition_variable>
#include <chrono>
#include <thread>

namespace Yuki::Core
{

class YukiThread final : virtual public IYukiThread
{
protected:
  ThreadType       m_CppThread;
  CallbackFuncType m_fnCallback;
  bool             m_bThreadReady;

public:
  explicit YukiThread(const CallbackFuncType& callback);
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

class YukiThreadPool final : virtual public IYukiThreadPool
{
protected:
  Vector<std::thread>       m_aWorkers;
  std::thread               m_ManagerThread;
  std::condition_variable   m_ActionQueueWaiter;
  std::mutex                m_ActionQueueMutex;
  Queue<CallbackFuncType>   m_ActionQueue;
  CallbackFuncType          m_WorkerFunc;
  CallbackFuncType          m_ManagerFunc;
  bool                      m_bPoolActive;
  bool                      m_bPoolStarted;
  std::chrono::milliseconds m_tInvokeInterval;


public:
  explicit YukiThreadPool(int poolSize, long long invokeInterval);
  ~YukiThreadPool() = default;

  void Start() override;
  void Join() override;
  void PushAction(const CallbackFuncType& callback) override;
  void Terminate() override;
};

} // namespace Yuki::Core
