#pragma once

#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiComp/YukiComponent.hpp"

#include <glm/mat4x4.hpp>

namespace Yuki::Comp
{

class YUKIAPI IYukiCamera : public IYukiComp
{
public:
    virtual const glm::mat4& GetCameraViewMatrix()       = 0;
    virtual const glm::mat4& GetCameraProjectionMatrix() = 0;
    virtual const glm::vec3& GetCameraPosition()         = 0;
    virtual const glm::vec3& GetCameraDirection()        = 0;

    virtual const glm::vec3 GetCameraTopAxis()        = 0;
    virtual const glm::vec3 GetCameraHorizontalAxis() = 0;
    virtual const glm::vec3 GetCameraVerticalAxis()   = 0;

    virtual const float& GetFieldOfView()         = 0;
    virtual const float& GetViewportAspectRatio() = 0;
    virtual const float& GetNearPerspective()     = 0;
    virtual const float& GetFarPerspective()      = 0;

    virtual void CameraRotateViewport(const float& rad)                            = 0;
    virtual void CameraRotateDirection(const glm::vec3& rotAxis, const float& rad) = 0;
    virtual void LookAtPoint(const glm::vec3& point)                               = 0;
    virtual void SetCameraDirection(const glm::vec3& direction)                    = 0;
    virtual void SetCameraPosition(const glm::vec3& position)                      = 0;
    virtual void SetFieldOfView(const float& fov)                                  = 0;
    virtual void SetViewportAspectRatio(const float& ratio)                        = 0;
    virtual void SetViewportAspectRatio(const float& width, const float& height)   = 0;
    virtual void SetNearPerspective(const float& pnear)                            = 0;
    virtual void SetFarPerspective(const float& pfar)                              = 0;

    virtual void SetCameraKeyCallback(const Core::YukiInpKeyboardCallbackT& callback)  = 0;
    virtual void SetCameraCursorCallback(const Core::YukiInpCursorCallbackT& callback) = 0;
};

SharedPtr<IYukiCamera> YUKIAPI CreateYukiCamera();

} // namespace Yuki::Comp