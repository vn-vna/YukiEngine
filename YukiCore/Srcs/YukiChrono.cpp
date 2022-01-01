#include "YukiCore/YukiVE.hpp"
#include "YukiCore/Chrono.hpp"

// std
#include <chrono>

namespace Yuki::Chrono
{

const float CurrentTimeNanos()
{
  return (float) std::chrono::duration_cast<SystemClockNS>(CurrentTimePoint().time_since_epoch()).count();
}

const float CurrentTimeMilis()
{
  return CurrentTimeNanos() / 1'000'000.0f;
}

TimePointType CurrentTimePoint()
{
  return std::chrono::system_clock::now();
}

TimeType CurrentTimePointTT()
{
  return std::chrono::system_clock::to_time_t(CurrentTimePoint());
}

TMType CurrentTimePointTM()
{
  AutoType point_tt = CurrentTimePointTT();
  TMType   tm{};
  gmtime_s(&tm, &point_tt);
  return tm;
}

const String DateTimeString(const DateTimeFormat& format)
{
  StringStream wss{};
  wss << format.year
      << format.dateSeperator
      << format.month
      << format.dateSeperator
      << format.day
      << format.timeDateSeperator
      << format.hour
      << format.timeSeperator
      << format.minute
      << format.timeSeperator
      << format.second;

  String tformat = wss.str();
  wss.str(L"");

  AutoType crrTMTime = CurrentTimePointTM();

  wss << std::put_time(&crrTMTime, tformat.c_str());

  return {std::move(wss.str())};
}

} // namespace Yuki::Chrono