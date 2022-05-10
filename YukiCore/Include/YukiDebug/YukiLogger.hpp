/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

#define YUKI_DEBUG_MESSAGE_PRIOTY_NORMAL  "DEBUG"
#define YUKI_DEBUG_MESSAGE_PRIOTY_WARNING "WARNING"
#define YUKI_DEBUG_MESSAGE_PRIOTY_ERROR   "ERROR"

namespace Yuki::Debug
{

using Core::IYukiObject;

typedef OutputFileStream OutputLogFile;

class YUKIAPI IYukiLogger : virtual public IYukiObject
{
public:
  virtual void               PushMessage(const String& message, const String& prioty) = 0;
  virtual void               PushDebugMessage(const String& message)                  = 0;
  virtual void               PushWarningMessage(const String& message)                = 0;
  virtual void               PushErrorMessage(const String& message)                  = 0;
  virtual OutputLogFile& GetOutFileStream()                                       = 0;
};

SharedPtr<IYukiLogger> CreateYukiLogger();

} // namespace Yuki::Debug