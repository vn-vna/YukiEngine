#include "YukiCore/YukiPCH.hpp"
#include "YukiUtil/YukiChrono.hpp"

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
  StringStream asstr{};
  asstr << format.year
        << format.dateSeparator
        << format.month
        << format.dateSeparator
        << format.day
        << format.timeDateSeparator
        << format.hour
        << format.timeSeparator
        << format.minute
        << format.timeSeparator
        << format.second;

  String tformat = asstr.str();
  asstr.str("");

  AutoType crrTMTime = CurrentTimePointTM();

  asstr << std::put_time(&crrTMTime, tformat.c_str());

  return {std::move(asstr.str())};
}

} // namespace Yuki::Chrono