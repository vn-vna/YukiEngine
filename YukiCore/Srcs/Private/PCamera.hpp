/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiComp/Camera.hpp"

#include "PObjects.hpp"

namespace Yuki::Comp
{

using Core::YukiObject;

class YukiCamera final : virtual public ICamera,
                         virtual public YukiObject
{
public:
  YukiCamera();
  ~YukiCamera() override;

  const Mat4F& GetCameraViewMatrix() const override;
  const Mat4F& GetCameraProjectionMatrix() const override;
  const Vec3F& GetCameraPosition() const override;
  const Vec3F& GetCameraDirection() const override;
  const Vec3F  GetCameraTopAxis() const override;
  const Vec3F  GetCameraHorizontalAxis() const override;
  const Vec3F  GetCameraVerticalAxis() const override;
  float        GetFieldOfView() const override;
  float        GetViewportAspectRatio() const override;
  float        GetNearPerspective() const override;
  float        GetFarPerspective() const override;

  void CameraRotateViewport(float rad) override;
  void CameraRotateDirection(const Vec3F& rotAxis, float rad) override;
  void LookAtPoint(const Vec3F& point) override;
  void SetCameraDirection(const Vec3F& direction) override;
  void MoveCamera(const Vec3F& mov) override;
  void SetCameraPosition(const Vec3F& position) override;
  void SetFieldOfView(float fov) override;
  void SetViewportAspectRatio(float ratio) override;
  void SetViewportAspectRatio(float width, float height) override;
  void SetNearPerspective(float nNear) override;
  void SetFarPerspective(float nFar) override;

  void Update() override;

private:
  Mat4F m_ViewMatrix;
  Vec3F m_CamPos;
  Vec3F m_CamDirection;
  Vec3F m_CamTop;

  Mat4F m_ProjectionMatrix;
  float m_nFOV;
  float m_nAspectRatio;
  float m_nNear;
  float m_nFar;

  const unsigned m_nCamID;
};

} // namespace Yuki::Comp
