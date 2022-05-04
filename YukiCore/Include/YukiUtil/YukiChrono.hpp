/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once
#include "YukiCore/YukiPCH.hpp"

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

using TimePointType = std::chrono::system_clock::time_point;
using TimeType      = std::time_t;
using TMType        = std::tm;
using SystemClockNS = std::chrono::nanoseconds;
using TimerAction   = std::function<void(float, long long)>;

typedef struct YUKIAPI StDateTimeFormat
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

const float YUKIAPI   CurrentTimeNanos();
const float YUKIAPI   CurrentTimeMilis();
TimePointType YUKIAPI CurrentTimePoint();
TimeType YUKIAPI      CurrentTimePointTT();
TMType YUKIAPI        CurrentTimePointTM();
const String YUKIAPI  DateTimeString(const DateTimeFormat& format = DateTimeFormat{});

class YUKIAPI IYukiTimer
{};

class YUKIAPI YukiTimer : public IYukiTimer
{
protected:
  const float m_nStartTimePoint;
  const float m_nInterval;
};

} // namespace Yuki::Chrono