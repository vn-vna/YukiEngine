#pragma once

#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiInputCtrl.hpp"

#include <glm/mat4x4.hpp>

namespace Yuki::Comp
{

class YUKIAPI IYukiCamera : virtual public Core::IYukiObject
{
public:
  virtual const Mat4F& GetCameraViewMatrix() const       = 0;
  virtual const Mat4F& GetCameraProjectionMatrix() const = 0;
  virtual const Vec3F& GetCameraPosition() const         = 0;
  virtual const Vec3F& GetCameraDirection() const        = 0;
  virtual const Vec3F  GetCameraTopAxis() const          = 0;
  virtual const Vec3F  GetCameraHorizontalAxis() const   = 0;
  virtual const Vec3F  GetCameraVerticalAxis() const     = 0;
  virtual float        GetFieldOfView() const            = 0;
  virtual float        GetViewportAspectRatio() const    = 0;
  virtual float        GetNearPerspective() const        = 0;
  virtual float        GetFarPerspective() const         = 0;

  virtual void CameraRotateViewport(float rad)                        = 0;
  virtual void CameraRotateDirection(const Vec3F& rotAxis, float rad) = 0;
  virtual void LookAtPoint(const Vec3F& point)                        = 0;
  virtual void SetCameraDirection(const Vec3F& direction)             = 0;
  virtual void SetCameraPosition(const Vec3F& position)               = 0;
  virtual void SetFieldOfView(float fov)                              = 0;
  virtual void SetViewportAspectRatio(float ratio)                    = 0;
  virtual void SetViewportAspectRatio(float width, float height)      = 0;
  virtual void SetNearPerspective(float pnear)                        = 0;
  virtual void SetFarPerspective(float pfar)                          = 0;
};

SharedPtr<IYukiCamera> YUKIAPI CreateYukiCamera();

} // namespace Yuki::Comp