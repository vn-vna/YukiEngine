#pragma once
#include "YukiCore/YukiPCH.hpp"
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
  virtual void               PushMessage(const String& message, const String& prioty) = 0;
  virtual void               PushDebugMessage(const String& message)                  = 0;
  virtual void               PushWarningMessage(const String& message)                = 0;
  virtual void               PushErrorMessage(const String& message)                  = 0;
  virtual OutputLogFileType& GetOutFileStream()                                       = 0;
};

SharedPtr<IYukiLogger> CreateYukiLogger();

} // namespace Yuki::Debug
