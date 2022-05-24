/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiUtil/YukiChrono.hpp"

#include <chrono>

namespace Yuki::Chrono
{

class YukiTimer final : virtual public IYukiTimer
{
public:
  explicit YukiTimer(const TimerAction& callback, long long interval, bool parallel = false);
  ~YukiTimer();

  void Start() override;
  void Pause() override;
  void Resume() override;
  void Terminate() override;
  void Restart() override;
  void ExecuteCallback() override;

  void SeekTimer(long long millis, long long nanos) override;
  void SeekTimer(float seconds) override;
  void SeekCycle(long long cycles) override;

  void SetInterval(long long milis, long long nanos) override;
  void SetEstimateCycle(long long cycles) override;
  void SetParallelExecution(bool sep) override;
  void SetCallback(const TimerAction& callback) override;

  long long          GetCycle() override;
  long long          GetInterval() override;
  long long          GetRawElapsedTime() override;
  long long          GetElapsedTime() override;
  long long          GetElapsedCycle() override;
  long long          GetRawElapsedCycle() override;
  bool               IsParallelExecution() override;
  bool               IsPaused() override;
  bool               IsStarted() override;
  const TimerAction& GetCallback() override;

  static void UpdateTimers();

private:
  long long    m_nTimeStartNanos;
  long long    m_nEstimateCycle;
  long long    m_nTimeSkipped;
  long long    m_nCycleSkipped;
  long long    m_nInterval;
  long long    m_nPrevExecuteCycle;
  Atomic<bool> m_bExecuteParallel;
  Atomic<bool> m_bPaused;
  Atomic<bool> m_bStarted;
  Atomic<bool> m_bWillExecute;
  TimerAction  m_fnCallback;
};

} // namespace Yuki::Chrono