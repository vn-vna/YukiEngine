#include "YukiCore/Headers.hpp"
#include "YukiUtil/Chrono.hpp"

// std
#include <chrono>

namespace Yuki::Chrono
{

long long Clock::CurrentTimeNanos()
{
  return std::chrono::duration_cast<SystemClockNS>(
             CurrentTimePoint().time_since_epoch()
  )
      .count();
}

long long Clock::CurrentTimeMilis()
{
  return Clock::CurrentTimeNanos() / 1'000'000.0f;
}

TimePoint Clock::CurrentTimePoint()
{
  return std::chrono::system_clock::now();
}

TimeType Clock::CurrentTimePointTT()
{
  return std::chrono::system_clock::to_time_t(Clock::CurrentTimePoint());
}

TMType Clock::CurrentTimePointTM()
{
  AutoType point_tt = Clock::CurrentTimePointTT();
  AutoType tm       = gmtime(&point_tt);
  return *tm;
}

const String Clock::DateTimeString(const DateTimeFormat& format)
{
  StringStream asstr {};
  asstr << format.year << format.dateSeparator << format.month
        << format.dateSeparator << format.day << format.timeDateSeparator
        << format.hour << format.timeSeparator << format.minute
        << format.timeSeparator << format.second;

  String tformat = asstr.str();
  asstr.str("");

  AutoType crrTMTime = Clock::CurrentTimePointTM();

  asstr << std::put_time(&crrTMTime, tformat.c_str());

  return {std::move(asstr.str())};
}

} // namespace Yuki::Chrono
