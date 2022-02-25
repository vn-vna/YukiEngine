#pragma once

#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiInputCtrl.hpp"

#include <glm/mat4x4.hpp>

namespace Yuki::Comp
{

class YUKIAPI IYukiCamera : public Core::IYukiObject
{
public:
  virtual const glm::mat4& GetCameraViewMatrix()       = 0;
  virtual const glm::mat4& GetCameraProjectionMatrix() = 0;
  virtual const glm::vec3& GetCameraPosition()         = 0;
  virtual const glm::vec3& GetCameraDirection()        = 0;

  virtual const glm::vec3 GetCameraTopAxis()        = 0;
  virtual const glm::vec3 GetCameraHorizontalAxis() = 0;
  virtual const glm::vec3 GetCameraVerticalAxis()   = 0;

  virtual float GetFieldOfView()         = 0;
  virtual float GetViewportAspectRatio() = 0;
  virtual float GetNearPerspective()     = 0;
  virtual float GetFarPerspective()      = 0;

  virtual void CameraRotateViewport(float rad)                            = 0;
  virtual void CameraRotateDirection(const glm::vec3& rotAxis, float rad) = 0;
  virtual void LookAtPoint(const glm::vec3& point)                        = 0;
  virtual void SetCameraDirection(const glm::vec3& direction)             = 0;
  virtual void SetCameraPosition(const glm::vec3& position)               = 0;
  virtual void SetFieldOfView(float fov)                                  = 0;
  virtual void SetViewportAspectRatio(float ratio)                        = 0;
  virtual void SetViewportAspectRatio(float width, float height)          = 0;
  virtual void SetNearPerspective(float pnear)                            = 0;
  virtual void SetFarPerspective(float pfar)                              = 0;

  virtual void SetCameraKeyCallback(const Core::YukiInpKeyboardCallbackT& callback)  = 0;
  virtual void SetCameraCursorCallback(const Core::YukiInpCursorCallbackT& callback) = 0;
};

SharedPtr<IYukiCamera> YUKIAPI CreateYukiCamera();

} // namespace Yuki::Comp