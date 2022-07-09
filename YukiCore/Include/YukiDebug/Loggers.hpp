/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/Objects.hpp"

#define YUKI_DEBUG_MESSAGE_PRIOTY_NORMAL  "DEBUG"
#define YUKI_DEBUG_MESSAGE_PRIOTY_WARNING "WARNING"
#define YUKI_DEBUG_MESSAGE_PRIOTY_ERROR   "ERROR"

namespace Yuki::Debug
{

using Core::IObject;

typedef OutputFileStream OutputLogFile;

class ILogger : virtual public IObject
{
public:
  virtual void           PushMessage(const String& message, const String& prioty) = 0;
  virtual void           PushDebugMessage(const String& message)                  = 0;
  virtual void           PushWarningMessage(const String& message)                = 0;
  virtual void           PushErrorMessage(const String& message)                  = 0;
  virtual OutputLogFile& GetOutFileStream()                                       = 0;
};

SharedPtr<ILogger> CreateYukiLogger();

} // namespace Yuki::Debug
