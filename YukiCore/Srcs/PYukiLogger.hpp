#pragma once

#include "YukiDebug/YukiLogger.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Debug
{

class YUKIAPI YukiLogger : virtual public IYukiLogger,
                           virtual public Core::YukiObject
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