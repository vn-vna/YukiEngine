#pragma once

#include "YukiCore/YukiPCH.hpp"

namespace Yuki::Core
{

class YUKIAPI IYukiObject
{
public:
  IYukiObject()          = default;
  virtual ~IYukiObject() = default;

  virtual void Create(){};
  virtual void Awake(){};
  virtual void Update(){};
  virtual void Render(){};
  virtual void Destroy(){};
};

class YUKIAPI IYukiProtectedObject
{
public:
  IYukiProtectedObject()          = default;
  virtual ~IYukiProtectedObject() = default;

  virtual void LockYukiObj()   = 0;
  virtual void UnlockYukiObj() = 0;
};

} // namespace Yuki::Core

namespace Yuki
{

namespace Core
{

class YUKIAPI IYukiApp;
class YUKIAPI IYukiGfxControl;
class YUKIAPI IYukiShaderProgram;
class YUKIAPI IYukiWindow;
class YUKIAPI IYukiInpControl;
class YUKIAPI IYukiThread;

} // namespace Core

namespace Debug
{

enum class YUKIAPI YukiErrCode;
class YUKIAPI      YukiError;
class YUKIAPI      IYukiLogger;

} // namespace Debug

namespace Chrono
{
struct YUKIAPI StDateTimeFormat;
struct YUKIAPI StAsciiDateTimeFormat;
class YUKIAPI  IYukiTimer;
} // namespace Chrono

} // namespace Yuki