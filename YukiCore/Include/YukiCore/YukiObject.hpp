#pragma once

#include "YukiCore/YukiPCH.hpp"

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
class YUKIAPI IYukiOGLObject;
class YUKIAPI IYukiOGLVertexBuffer;
class YUKIAPI IYukiOGLShaderProgram;
class YUKIAPI IYukiOGLElementBuffer;
class YUKIAPI IYukiOGLTexture;

enum class PrimitiveTopology;
enum class TextureType;
enum class TextureMinFilter;
enum class TextureMagFilter;
enum class TextureDepthStencilMode;
enum class TextureCompareFunc;
enum class TextureCompareMode;
enum class PixelBasedInternalFormat;
enum class VertexFlag;
enum class KeyState;
enum class JoyStickHatState;
enum class KeyCode;
enum class MouseBtnCode;
enum class JoystickBtnCode;
enum class GamepadBtnCode;
enum class GamepadAxes;
enum class KeyModifier;

struct StKeyStatus;
struct StVertexFormat;
struct StIndexData;
struct StKeyStatus;

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
struct YUKIAPI StDateTimeFormat;
class YUKIAPI  IYukiTimer;

} // namespace Chrono

namespace Comp
{

struct YUKIAPI StTransformationInfo;

class YUKIAPI IYukiMesh;
class YUKIAPI IYukiScene;
class YUKIAPI IYukiCamera;
class YUKIAPI IYukiModel;

} // namespace Comp

namespace Entity
{

class YUKIAPI YukiEntity;

}

} // namespace Yuki

namespace Yuki::Core
{

class YUKIAPI IYukiObject
{
public:
  virtual void Create()  = 0;
  virtual void Awake()   = 0;
  virtual void Update()  = 0;
  virtual void Render()  = 0;
  virtual void Destroy() = 0;
};

template <typename I, typename D, typename... Args>
SharedPtr<I> CreateInterfaceInstance(Args&&... args)
{
  return std::dynamic_pointer_cast<I>(std::make_shared<D>(args...));
}

} // namespace Yuki::Core