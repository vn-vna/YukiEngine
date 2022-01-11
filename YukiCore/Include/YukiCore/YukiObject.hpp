#pragma once

#include "YukiCore/YukiVE.hpp"

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

} // namespace Yuki::Core

namespace Yuki
{

namespace Core
{

class YUKIAPI  IYukiApp;
class YUKIAPI  IYukiGfxControl;
class YUKIAPI  IYukiWindow;
class YUKIAPI  IYukiInpControl;

} // namespace Core

namespace Debug
{

enum class YUKIAPI YukiErrCode;
class YUKIAPI      YukiError;
class YUKIAPI      IYukiLogger;

} // namespace Debug

namespace Chrono
{
typedef struct YUKIAPI StDateTimeFormat;
typedef struct YUKIAPI StAsciiDateTimeFormat;
class YUKIAPI          IYukiTimer;
} // namespace Chrono

} // namespace Yuki