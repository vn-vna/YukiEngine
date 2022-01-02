#pragma once
#include "YukiCore/YukiVE.hpp"
#include "YukiCore/YukiObject.hpp"

#define YUKI_DEBUG_MESSAGE_PRIOTY_NORMAL  L"DEBUG"
#define YUKI_DEBUG_MESSAGE_PRIOTY_WARNING L"WARNING"
#define YUKI_DEBUG_MESSAGE_PRIOTY_ERROR   L"ERROR"

namespace Yuki::Debug
{

using OutputLogFileType = std::wofstream;

class YUKIAPI IYukiLogger : public Core::IYukiObject
{
public:
  IYukiLogger()          = default;
  virtual ~IYukiLogger() = default;

  virtual void               PushMessage(const String& message, const String& prioty) = 0;
  virtual void               PushDebugMessage(const String& message)                  = 0;
  virtual void               PushWarningMessage(const String& message)                = 0;
  virtual void               PushErrorMessage(const String& message)                  = 0;
  virtual OutputLogFileType& GetOutFileStream()                                       = 0;
};

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

  static SharedPtr<IYukiLogger> CreateYukiLogger();
};

} // namespace Yuki::Debug