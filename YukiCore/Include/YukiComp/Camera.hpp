/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Objects.hpp"
#include "YukiCore/Input.hpp"

namespace Yuki::Comp
{

using Core::IObject;

/**
 * @details
 * This class provide a camera to handle view in your scene.
 * You need to create a camera first then your scene can bee
 * rendered perfectly
 * @code
 * AutoType camera  = Yuki::Comp::CreateYukiCamera();
 * AutoType scene   = Yuki::Comp::CreateYukiScene();
 * scene->SetCamera(camera);
 */
class ICamera : virtual public IObject
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
  virtual void MoveCamera(const Vec3F& mov)                           = 0;
  virtual void SetCameraPosition(const Vec3F& position)               = 0;
  virtual void SetFieldOfView(float fov)                              = 0;
  virtual void SetViewportAspectRatio(float ratio)                    = 0;
  virtual void SetViewportAspectRatio(float width, float height)      = 0;
  virtual void SetNearPerspective(float pnear)                        = 0;
  virtual void SetFarPerspective(float pfar)                          = 0;
};

/**
 * Create a camera and return it's interface instance in
 * shared pointer form
 * @return A camera interface instance
 */
SharedPtr<ICamera> CreateYukiCamera();

} // namespace Yuki::Comp
