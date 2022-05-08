#include "YukiCore/YukiPCH.hpp"
#include "YukiUtil/YukiChrono.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiDebug/YukiError.hpp"

#include "PYukiLogger.hpp"

namespace Yuki::Debug
{

YukiLogger::YukiLogger()
    : m_pOutFileStream(nullptr)
{}

YukiLogger::~YukiLogger() = default;

void YukiLogger::PushMessage(const String& message, const String& prioty)
{
  String sstr = "[YUKI " + prioty + " REPORT] - >> " + Clock::DateTimeString() + " <<\n\t" + message.c_str() + "\n";
#ifndef NDEBUG
  std::cout << sstr;
#endif // !NDEBUG
  if (!m_pOutFileStream->good())
  {
    THROW_YUKI_ERROR(CreateLogFileError);
  }
  GetOutFileStream() << sstr;
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

OutputLogFileType& YukiLogger::GetOutFileStream()
{
  return *m_pOutFileStream;
}

void YukiLogger::Create()
{
  Chrono::DateTimeFormat format{};
  m_pOutFileStream = std::make_shared<OutputLogFileType>(Clock::DateTimeString(format) + ".ylg");
#ifndef NDEBUG
  // OutputDebugStringW(L"[YUKI CONFIGURATION REPORT] Application is running in DEBUG MODE\n");
  PushDebugMessage("Application is running in DEBUG MODE");
#else
  PushDebugMessage("Application is running in RELEASE MODE");
#endif // NDEBUG
}

void YukiLogger::Destroy()
{
  m_pOutFileStream->close();
}

SharedPtr<IYukiLogger> CreateYukiLogger()
{
  return Core::CreateInterfaceInstance<IYukiLogger, YukiLogger>();
}

} // namespace Yuki::Debug