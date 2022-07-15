#include "YukiCore/Headers.hpp"
#include "YukiUtil/Chrono.hpp"
#include "YukiDebug/Loggers.hpp"
#include "YukiDebug/Errors.hpp"

#include "YukiCore/Srcs/Private/PLogger.hpp"

#include <fmt/format.h>

namespace Yuki::Debug
{

using Chrono::Clock;

YukiLogger::YukiLogger()
    : m_pOutFileStream(nullptr)
{}

YukiLogger::~YukiLogger() = default;

void YukiLogger::PushMessage(const String& message, const String& prioty)
{
  String outMessage = fmt::format("[YUKI {} REPORT] - {}\n\t{}\n", prioty,
                                  Clock::DateTimeString(), message);
#ifndef NDEBUG
  std::cout << outMessage;
#endif // !NDEBUG
  if (!m_pOutFileStream->good())
  {
    THROW_YUKI_ERROR(CreateLogFileError);
  }
  GetOutFileStream() << outMessage;
}

void YukiLogger::PushDebugMessage(const String& message)
{
  PushMessage(message, YUKI_DEBUG_MESSAGE_PRIOTY_NORMAL);
}

void YukiLogger::PushWarningMessage(const String& message)
{
  PushMessage(message, YUKI_DEBUG_MESSAGE_PRIOTY_WARNING);
}

void YukiLogger::PushErrorMessage(const String& message)
{
  PushMessage(message, YUKI_DEBUG_MESSAGE_PRIOTY_ERROR);
}

OutputLogFile& YukiLogger::GetOutFileStream()
{
  return *m_pOutFileStream;
}

void YukiLogger::Create()
{
  Chrono::DateTimeFormat format {};
  m_pOutFileStream =
      std::make_shared<OutputLogFile>(Clock::DateTimeString(format) + ".ylg");
#ifndef NDEBUG
  // OutputDebugStringW(L"[YUKI CONFIGURATION REPORT]
  // Application is running in DEBUG MODE\n");
  PushDebugMessage("Application is running in DEBUG MODE");
#else
  PushDebugMessage("Application is running in RELEASE MODE");
#endif // NDEBUG
}

void YukiLogger::Destroy()
{
  m_pOutFileStream->close();
}

SharedPtr<ILogger> CreateYukiLogger()
{
  return Core::CreateInterfaceInstance<ILogger, YukiLogger>();
}

} // namespace Yuki::Debug
