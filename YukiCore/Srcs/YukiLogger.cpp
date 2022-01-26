#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiChrono.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiDebug/YukiError.hpp"

namespace Yuki::Debug
{

class YUKIAPI YukiLogger : public IYukiLogger
{
protected:
  SharedPtr<OutputLogFileType> m_pOutFileStream;

public:
  YukiLogger();
  virtual ~YukiLogger() = default;

  void               PushMessage(const String& message, const String& prioty);
  void               PushDebugMessage(const String& message) override;
  void               PushWarningMessage(const String& message) override;
  void               PushErrorMessage(const String& message) override;
  OutputLogFileType& GetOutFileStream() override;
  void               Create() override;
  void               Destroy() override;
};

} // namespace Yuki::Debug

namespace Yuki::Debug
{

YukiLogger::YukiLogger()
    : m_pOutFileStream(nullptr)
{
}

void YukiLogger::PushMessage(const String& message, const String& prioty)
{
  String sstr = L"[YUKI " + prioty + L" REPORT] - >> " + Chrono::DateTimeString() + L" <<\n\t" + message.c_str() + L"\n";
#ifndef NDEBUG
  std::wcout << sstr;
#endif // !NDEBUG
  if (!m_pOutFileStream->good())
  {
    THROW_YUKI_ERROR(Debug::YukiCreateLogFileError);
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
  Chrono::AsciiDateTimeFormat format{};
  format.timeSeperator = YUKI_ASCII_TIMESTR_SLASH_SEPERATOR;
  m_pOutFileStream     = std::make_shared<OutputLogFileType>(Chrono::DateTimeAsciiString(format) + ".ylg");
#ifndef NDEBUG
  //OutputDebugStringW(L"[YUKI CONFIGURATION REPORT] Application is running in DEBUG MODE\n");
  PushDebugMessage(L"Application is running in DEBUG MODE");
#else
  PushDebugMessage(L"Application is running in RELEASE MODE");
#endif // NDEBUG
}

void YukiLogger::Destroy()
{
  m_pOutFileStream->close();
}

SharedPtr<IYukiLogger> CreateYukiLogger()
{
  return {(IYukiLogger*) new YukiLogger(), std::default_delete<IYukiLogger>()};
}

} // namespace Yuki::Debug