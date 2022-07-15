/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"

namespace Yuki
{

namespace Core
{

class IObject;
class ISharedObject;
class IApplication;
class IGraphics;
class IWindow;
class IInput;
class IThreadPool;
class IOGLObject;
class IOGLVertexArray;
class IOGLVertexBuffer;
class IOGLShaderProgram;
class IOGLElementBuffer;
class IOGLRenderBuffer;
class IOGLFrameBuffer;
class IOGLTexture;

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
enum class StandardCursorType;

struct StKeyStatus;
struct StVertexFormat;
struct StIndexData;
struct StKeyStatus;

} // namespace Core

namespace Debug
{

class Errors;
class ILogger;

enum class YukiErrCode;

typedef ILogger SPILogger;

} // namespace Debug

namespace Chrono
{

class IYukiTimer;
class IYukiStopwatch;

struct StDateTimeFormat;

} // namespace Chrono

namespace Comp
{

class IMesh;
class IScene;
class ICamera;
class IModel;
class ILayer;
class IMaterial;

struct StTransformationInfo;

} // namespace Comp

namespace Entity
{

class TemplateEntity;


} // namespace Entity

} // namespace Yuki

namespace Yuki::Core
{

class IObject
{
public:
  virtual void Create()  = 0;
  virtual void Awake()   = 0;
  virtual void Update()  = 0;
  virtual void Render()  = 0;
  virtual void Destroy() = 0;
};

class ISharedObject : virtual public IObject
{
public:
  virtual void Require() = 0;
  virtual void Release() = 0;
};

template <class T, typename... Args>
inline SharedPtr<T> MakeShared(Args&&... args)
{
  return std::make_shared<T>(args...);
}

template <class Des, class Res>
inline SharedPtr<Des> DynamicPtrCast(SharedPtr<Res> ptr)
{
  return std::dynamic_pointer_cast<Des>(ptr);
}

template <class I, class D, typename... Args>
inline SharedPtr<I> CreateInterfaceInstance(Args&&... args)
{
  return DynamicPtrCast<I>(MakeShared<D>(args...));
}

} // namespace Yuki::Core
