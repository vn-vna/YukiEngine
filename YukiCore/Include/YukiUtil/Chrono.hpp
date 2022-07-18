/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once
#include "YukiCore/Headers.hpp"
#include "YukiCore/Objects.hpp"
#include "YukiCore/Application.hpp"
#include "YukiCore/ThreadPool.hpp"

// std
#include <chrono>

#define YUKI_TIMESTR_YEAR_SHORT_FORMAT       "%y"
#define YUKI_TIMESTR_YEAR_LONG_FORMAT        "%Y"
#define YUKI_TIMESTR_YEAR_LLOCALE_FORMAT     "%EY"
#define YUKI_TIMESTR_YEAR_SLOCALE_FORMAT     "0y"
#define YUKI_TIMESTR_MONTH_NUMBER_FORMAT     "%m"
#define YUKI_TIMESTR_MONTH_ARREVIATED_FORMAT "%b"
#define YUKI_TIMESTR_MONTH_FULLNAME_FORMAT   "%B"
#define YUKI_TIMESTR_MONTH_LOCALE_FORMAT     "%0m"
#define YUKI_TIMESTR_DATE_NUMBER_FORMAT      "%d"
#define YUKI_TIMESTR_DATE_LLOCALE_FORMAT     "0d"
#define YUKI_TIMESTR_DATE_SHORT_FORMAT       "e"
#define YUKI_TIMESTR_DATE_SLOCALE_FORMAT     "0e"
#define YUKI_TIMESTR_HOUR_NUMBER_FORMAT      "%H"
#define YUKI_TIMESTR_MINUTE_NUMBER_FORMAT    "%M"
#define YUKI_TIMESTR_SECOND_NUMBER_FORMAT    "%S"
#define YUKI_TIMESTR_SLASH_SEPERATOR         "-"
#define YUKI_TIMESTR_COLON_SEPERATOR         ":"
#define YUKI_TIMESTR_DOT_SEPERATOR           "."
#define YUKI_TIMESTR_SPACE_SEPERATOR         " "

namespace Yuki::Chrono
{

using TimePoint     = std::chrono::system_clock::time_point;
using TimeType      = std::time_t;
using TMType        = std::tm;
using SystemClockNS = std::chrono::nanoseconds;
using MiliSeconds   = std::chrono::milliseconds;
using NanoSeconds   = std::chrono::nanoseconds;
using Seconds       = std::chrono::seconds;

typedef std::function<void(IYukiTimer*)> TimerAction;
typedef UnorderedSet<IYukiTimer*>        TimerManager;

typedef struct StDateTimeFormat
{
  String year              = YUKI_TIMESTR_YEAR_LONG_FORMAT;
  String month             = YUKI_TIMESTR_MONTH_NUMBER_FORMAT;
  String day               = YUKI_TIMESTR_DATE_NUMBER_FORMAT;
  String hour              = YUKI_TIMESTR_HOUR_NUMBER_FORMAT;
  String minute            = YUKI_TIMESTR_MINUTE_NUMBER_FORMAT;
  String second            = YUKI_TIMESTR_SECOND_NUMBER_FORMAT;
  String dateSeparator     = YUKI_TIMESTR_SLASH_SEPERATOR;
  String timeSeparator     = YUKI_TIMESTR_DOT_SEPERATOR;
  String timeDateSeparator = YUKI_TIMESTR_SPACE_SEPERATOR;
} DateTimeFormat;

class Clock
{
public:
  static long long CurrentTimeNanos();
  static long long CurrentTimeMilis();
  static TimePoint CurrentTimePoint();
  static TimeType  CurrentTimePointTT();
  static TMType    CurrentTimePointTM();
  static const String
  DateTimeString(const DateTimeFormat& format = DateTimeFormat {});
};

class IYukiStopwatch
{
public:
  virtual void      Start()          = 0;
  virtual long long GetElapsedTime() = 0;
};

class IYukiTimer
{
public:
  virtual void Start()           = 0;
  virtual void Pause()           = 0;
  virtual void Resume()          = 0;
  virtual void Terminate()       = 0;
  virtual void Restart()         = 0;
  virtual void ExecuteCallback() = 0;

  virtual void SeekTimer(long long millis, long long nanos) = 0;
  virtual void SeekTimer(float seconds)                     = 0;
  virtual void SeekCycle(long long cycles)                  = 0;

  virtual void SetInterval(long long milis, long long nanos) = 0;
  virtual void SetEstimateCycle(long long cycles) = 0; // Set the estimate
                                                       // cycle, -1 for infinite
  virtual void SetParallelExecution(bool sep
  ) = 0; // Execute callback from thread pool
  virtual void SetCallback(const TimerAction& callback) = 0;

  virtual long long GetCycle()    = 0; // Return the defined Cycle or -1 for
                                       // infinite
  virtual long long          GetInterval()         = 0;
  virtual long long          GetRawElapsedTime()   = 0;
  virtual long long          GetElapsedTime()      = 0;
  virtual long long          GetElapsedCycle()     = 0;
  virtual long long          GetRawElapsedCycle()  = 0;
  virtual bool               IsParallelExecution() = 0;
  virtual bool               IsPaused()            = 0;
  virtual bool               IsStarted()           = 0;
  virtual const TimerAction& GetCallback()         = 0;
};

SharedPtr<TimerManager> GetTimerManager();
SharedPtr<IYukiTimer>   CreateTimer(
      const TimerAction& callback, long long interval, bool parallexEx = false
  );

} // namespace Yuki::Chrono
