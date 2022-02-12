#pragma once

#include "YukiComp/YukiCamera.hpp"

namespace Yuki::Comp
{

class YukiCamera : public IYukiCamera
{
protected:
  glm::mat4 m_ViewMatrix;
  glm::vec3 m_CamPos;
  glm::vec3 m_CamDirection;
  glm::vec3 m_CamTop;

  glm::mat4 m_ProjectionMatrix;
  float     m_nFOV;
  float     m_nAspectRatio;
  float     m_nNear;
  float     m_nFar;

  const unsigned m_nCamID;

public:
  YukiCamera();
  virtual ~YukiCamera();

  const glm::mat4& GetCameraViewMatrix() override;
  const glm::mat4& GetCameraProjectionMatrix() override;
  const glm::vec3& GetCameraPosition() override;
  const glm::vec3& GetCameraDirection() override;

  const glm::vec3 GetCameraTopAxis() override;
  const glm::vec3 GetCameraHorizontalAxis() override;
  const glm::vec3 GetCameraVerticalAxis() override;

  const float& GetFieldOfView() override;
  const float& GetViewportAspectRatio() override;
  const float& GetNearPerspective() override;
  const float& GetFarPerspective() override;

  void CameraRotateViewport(const float& rad) override;
  void CameraRotateDirection(const glm::vec3& rotAxis, const float& rad) override;
  void LookAtPoint(const glm::vec3& point) override;
  void SetCameraDirection(const glm::vec3& direction) override;
  void SetCameraPosition(const glm::vec3& position) override;
  void SetFieldOfView(const float& fov) override;
  void SetViewportAspectRatio(const float& ratio) override;
  void SetViewportAspectRatio(const float& width, const float& height) override;
  void SetNearPerspective(const float& pnear) override;
  void SetFarPerspective(const float& pfar) override;

  void SetCameraKeyCallback(const Core::YukiInpKeyboardCallbackT& callback) override;
  void SetCameraCursorCallback(const Core::YukiInpCursorCallbackT& callback) override;

  void Update() override;
};

} // namespace Yuki::Comp