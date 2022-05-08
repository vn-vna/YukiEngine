/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#include "PYukiTimer.hpp"

namespace Yuki::Chrono
{

using Core::CreateInterfaceInstance;

YukiTimer::YukiTimer(const TimerAction& callback, long long interval, bool parallel)
    : m_nCycleSkipped(0),
      m_nEstimateCycle(0),
      m_bExecuteParallel(parallel),
      m_nTimeSkipped(0),
      m_nTimeStartNanos(0),
      m_nPrevExecuteCycle(0),
      m_nInterval(interval),
      m_bPaused(false),
      m_bStarted(false),
      m_bWillExecute(false),
      m_fnCallback(callback)
{
  AutoType manager = GetTimerManager();
  if (manager->find(this) == manager->end())
  {
    manager->insert({this, 0});
  }
}

YukiTimer::~YukiTimer()
{
  AutoType manager   = GetTimerManager();
  AutoType thisTimer = manager->find(this);
  if (thisTimer != manager->end())
  {
    manager->erase(this);
  }
}

void YukiTimer::Start()
{
  m_nTimeStartNanos = Clock::CurrentTimeNanos();
  m_bStarted        = true;
}

void YukiTimer::Pause()
{
  m_bPaused = true;
}

void YukiTimer::Resume()
{
  m_bPaused = false;
}

void YukiTimer::Terminate()
{
  m_bStarted = false;
}

void YukiTimer::Restart()
{
  m_bStarted        = true;
  m_nTimeStartNanos = Clock::CurrentTimeNanos();
}

void YukiTimer::SeekTimer(long long millis, long long nanos)
{
  m_nTimeSkipped += 1000 * millis + nanos;
}

void YukiTimer::SeekTimer(float seconds)
{
  m_nTimeSkipped += seconds * 1'000'000'000;
}

void YukiTimer::SeekCycle(long long cycles)
{
  m_nCycleSkipped += cycles;
}

void YukiTimer::SetInterval(long long milis, long long nanos)
{
  m_nInterval += milis * 1'000'000 + nanos;
}

void YukiTimer::SetEstimateCycle(long long cycles)
{
  m_nEstimateCycle = cycles;
}

void YukiTimer::SetParallelExecution(bool sep)
{
  m_bExecuteParallel = sep;
}

void YukiTimer::SetCallback(const TimerAction& callback)
{
  m_fnCallback = callback;
}

long long YukiTimer::GetCycle()
{
  return m_nEstimateCycle;
}

long long YukiTimer::GetInterval()
{
  return m_nInterval;
}

long long YukiTimer::GetRawElapsedTime()
{
  return Clock::CurrentTimeNanos() - m_nTimeStartNanos;
}

long long YukiTimer::GetElapsedTime()
{
  return m_nTimeSkipped + this->GetRawElapsedTime();
}

long long YukiTimer::GetElapsedCycle()
{
  return this->GetElapsedTime() / m_nInterval;
}

long long YukiTimer::GetRawElapsedCycle()
{
  return this->GetRawElapsedTime() / m_nInterval;
}

bool YukiTimer::IsParallelExecution()
{
  return m_bExecuteParallel;
}

bool YukiTimer::IsPaused()
{
  return m_bPaused;
}

bool YukiTimer::IsStarted()
{
  return m_bStarted;
}

const TimerAction& YukiTimer::GetCallback()
{
  return m_fnCallback;
}

void YukiTimer::ExecuteCallback()
{
  if (m_nPrevExecuteCycle != this->GetElapsedCycle() && this->GetCallback())
  {
    this->GetCallback()(this);
    m_nPrevExecuteCycle = this->GetElapsedCycle();
  }
}

void YukiTimer::UpdateTimers()
{
  AutoType timerManager = *GetTimerManager();
  for (AutoType pTimer : timerManager)
  {
    if (!pTimer)
    {
      continue;
    }
    if (!pTimer->IsStarted() || pTimer->IsPaused())
    {
      continue;
    }
    // execute time check
    AutoType currentCycle = pTimer->GetElapsedCycle();

    if (pTimer->IsParallelExecution())
    {
      // TODO: Add parallel execution method
    }
    else
    {
      pTimer->ExecuteCallback();
    }
  }
}

SharedPtr<TimerManager> GetTimerManager()
{
  static SharedPtr<TimerManager> pManager;
  if (!pManager.get())
  {
    pManager = std::make_shared<TimerManager>();
  }
  return pManager;
}

SharedPtr<IYukiTimer> CreateTimer(const TimerAction& callback, long long interval, bool parallexEx)
{
  return CreateInterfaceInstance<IYukiTimer, YukiTimer>(callback, interval, parallexEx);
}


} // namespace Yuki::Chrono