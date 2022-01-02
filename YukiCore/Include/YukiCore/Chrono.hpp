#pragma once
#include "YukiCore/YukiVE.hpp"

// std
#include <chrono>

#define YUKI_TIMESTR_YEAR_SHORT_FORMAT       L"%y"
#define YUKI_TIMESTR_YEAR_LONG_FORMAT        L"%Y"
#define YUKI_TIMESTR_YEAR_LLOCALE_FORMAT     L"%EY"
#define YUKI_TIMESTR_YEAR_SLOCALE_FORMAT     L"0y"
#define YUKI_TIMESTR_MONTH_NUMBER_FORMAT     L"%m"
#define YUKI_TIMESTR_MONTH_ARREVIATED_FORMAT L"%b"
#define YUKI_TIMESTR_MONTH_FULLNAME_FORMAT   L"%B"
#define YUKI_TIMESTR_MONTH_LOCALE_FORMAT     L"%0m"
#define YUKI_TIMESTR_DATE_NUMBER_FORMAT      L"%d"
#define YUKI_TIMESTR_DATE_LLOCALE_FORMAT     L"0d"
#define YUKI_TIMESTR_DATE_SHORT_FORMAT       L"e"
#define YUKI_TIMESTR_DATE_SLOCALE_FORMAT     L"0e"
#define YUKI_TIMESTR_HOUR_NUMBER_FORMAT      L"%H"
#define YUKI_TIMESTR_MINUTE_NUMBER_FORMAT    L"%M"
#define YUKI_TIMESTR_SECOND_NUMBER_FORMAT    L"%S"
#define YUKI_TIMESTR_SLASH_SEPERATOR         L"-"
#define YUKI_TIMESTR_COLON_SEPERATOR         L":"
#define YUKI_TIMESTR_SPACE_SEPERATOR         L" "

#define YUKI_ASCII_TIMESTR_YEAR_SHORT_FORMAT       "%y"
#define YUKI_ASCII_TIMESTR_YEAR_LONG_FORMAT        "%Y"
#define YUKI_ASCII_TIMESTR_YEAR_LLOCALE_FORMAT     "%EY"
#define YUKI_ASCII_TIMESTR_YEAR_SLOCALE_FORMAT     "0y"
#define YUKI_ASCII_TIMESTR_MONTH_NUMBER_FORMAT     "%m"
#define YUKI_ASCII_TIMESTR_MONTH_ARREVIATED_FORMAT "%b"
#define YUKI_ASCII_TIMESTR_MONTH_FULLNAME_FORMAT   "%B"
#define YUKI_ASCII_TIMESTR_MONTH_LOCALE_FORMAT     "%0m"
#define YUKI_ASCII_TIMESTR_DATE_NUMBER_FORMAT      "%d"
#define YUKI_ASCII_TIMESTR_DATE_LLOCALE_FORMAT     "0d"
#define YUKI_ASCII_TIMESTR_DATE_SHORT_FORMAT       "e"
#define YUKI_ASCII_TIMESTR_DATE_SLOCALE_FORMAT     "0e"
#define YUKI_ASCII_TIMESTR_HOUR_NUMBER_FORMAT      "%H"
#define YUKI_ASCII_TIMESTR_MINUTE_NUMBER_FORMAT    "%M"
#define YUKI_ASCII_TIMESTR_SECOND_NUMBER_FORMAT    "%S"
#define YUKI_ASCII_TIMESTR_SLASH_SEPERATOR         "-"
#define YUKI_ASCII_TIMESTR_COLON_SEPERATOR         ":"
#define YUKI_ASCII_TIMESTR_SPACE_SEPERATOR         " "

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
  String dateSeperator     = YUKI_TIMESTR_SLASH_SEPERATOR;
  String timeSeperator     = YUKI_TIMESTR_COLON_SEPERATOR;
  String timeDateSeperator = YUKI_TIMESTR_SPACE_SEPERATOR;
} DateTimeFormat;

typedef struct YUKIAPI StAsciiDateTimeFormat
{
  AsciiString year              = YUKI_ASCII_TIMESTR_YEAR_LONG_FORMAT;
  AsciiString month             = YUKI_ASCII_TIMESTR_MONTH_NUMBER_FORMAT;
  AsciiString day               = YUKI_ASCII_TIMESTR_DATE_NUMBER_FORMAT;
  AsciiString hour              = YUKI_ASCII_TIMESTR_HOUR_NUMBER_FORMAT;
  AsciiString minute            = YUKI_ASCII_TIMESTR_MINUTE_NUMBER_FORMAT;
  AsciiString second            = YUKI_ASCII_TIMESTR_SECOND_NUMBER_FORMAT;
  AsciiString dateSeperator     = YUKI_ASCII_TIMESTR_SLASH_SEPERATOR;
  AsciiString timeSeperator     = YUKI_ASCII_TIMESTR_COLON_SEPERATOR;
  AsciiString timeDateSeperator = YUKI_ASCII_TIMESTR_SPACE_SEPERATOR;
} AsciiDateTimeFormat;

const float YUKIAPI       CurrentTimeNanos();
const float YUKIAPI       CurrentTimeMilis();
TimePointType YUKIAPI     CurrentTimePoint();
TimeType YUKIAPI          CurrentTimePointTT();
TMType YUKIAPI            CurrentTimePointTM();
const String YUKIAPI      DateTimeString(const DateTimeFormat& format = DateTimeFormat{});
const AsciiString YUKIAPI DateTimeAsciiString(const AsciiDateTimeFormat& format = AsciiDateTimeFormat{});

class YUKIAPI YukiTimer
{
protected:
  const float m_nStartTimePoint;
  const float m_nInterval;
};

} // namespace Yuki::Chrono