#pragma once

#include "YukiDebug/YukiLogger.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Debug
{

using Core::YukiObject;

class YukiLogger final : virtual public IYukiLogger,
                         virtual public YukiObject
{
protected:
  SharedPtr<OutputLogFileType> m_pOutFileStream;

public:
  YukiLogger();
  ~YukiLogger() override;

  void               PushMessage(const String& message, const String& prioty) override;
  void               PushDebugMessage(const String& message) override;
  void               PushWarningMessage(const String& message) override;
  void               PushErrorMessage(const String& message) override;
  OutputLogFileType& GetOutFileStream() override;
  void               Create() override;
  void               Destroy() override;
};

} // namespace Yuki::Debug