#pragma once
#include "YukiCore/YukiVE.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Debug
{

using OutputLogFileType = std::ofstream;

class YUKIAPI ILogger : public Core::IYukiObject
{
public:
  ILogger()          = default;
  virtual ~ILogger() = default;

  virtual void PushDebugMessage(const String& message)   = 0;
  virtual void PushWarningMessage(const String& message) = 0;
  virtual void PushErrorMessage(const String& message)   = 0;
};

class YUKIAPI Logger : public ILogger
{
protected:
  OutputLogFileType m_OutFile;

public:
  Logger();
  virtual ~Logger();
};

} // namespace Yuki::Debug