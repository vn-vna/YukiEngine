/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include <YukiEntity/Entity.hpp>
#include <YukiUtil/Utilities.hpp>

using Yuki::Core::KeyCode;
using Yuki::Utils::IsKeyReleased;

class CameraController : virtual public Yuki::Entity::TemplateEntity
{
protected:
  Yuki::SharedPtr<Yuki::Comp::ICamera> pCamera;
  Yuki::SharedPtr<Yuki::Core::IInput>  pInpControl;

public:
  explicit CameraController(const Yuki::String& name);
  ~CameraController() override;

  void OnCreate() override;
  void OnAwake() override;
  void OnUpdate() override;
  void OnRender() override;
  void OnDestroy() override;

  static Yuki::SharedPtr<Yuki::Entity::TemplateEntity> GetInstance();
};

inline void CameraController::OnCreate()
{
  pCamera     = Yuki::Core::GetYukiApp()->GetCurrentScene()->GetCamera();
  pInpControl = Yuki::Core::GetYukiApp()->GetInputController();
}

inline void CameraController::OnAwake()
{}

inline void CameraController::OnUpdate()
{
  // Move
  if (!IsKeyReleased(KeyCode::KEY_D))
  {
    Yuki::Utils::MoveCameraRight(pCamera, 0.01f);
  }
  if (!IsKeyReleased(KeyCode::KEY_A))
  {
    Yuki::Utils::MoveCameraLeft(pCamera, 0.01f);
  }
  if (!IsKeyReleased(KeyCode::KEY_W))
  {
    Yuki::Utils::MoveCameraFront(pCamera, 0.01f);
  }
  if (!IsKeyReleased(KeyCode::KEY_S))
  {
    Yuki::Utils::MoveCameraBack(pCamera, 0.01f);
  }
  if (!IsKeyReleased(KeyCode::KEY_Q))
  {
    Yuki::Utils::MoveCameraUp(pCamera, 0.01f);
  }
  if (!IsKeyReleased(Yuki::Core::KeyCode::KEY_E))
  {
    Yuki::Utils::MoveCameraDown(pCamera, 0.01f);
  }
  // Rotate
  if (!IsKeyReleased(Yuki::Core::KeyCode::KEY_LEFT_CONTROL))
  {
    AutoType cursorVeloc = pInpControl->GetMouseVelocity();
    pCamera->CameraRotateDirection(
        Yuki::Vec3F {0.0f, 1.0f, 0.0f}, glm::radians(cursorVeloc.x * -0.5f)
    );
    pCamera->CameraRotateDirection(
        Yuki::Vec3F {1.0f, 0.0f, 0.0f}, glm::radians(cursorVeloc.y * 0.5f)
    );
  }
}

inline void CameraController::OnRender()
{}

inline void CameraController::OnDestroy()
{}

inline CameraController::CameraController(const Yuki::String& name)
    : Yuki::Entity::TemplateEntity(name)
{}

inline CameraController::~CameraController() = default;

inline Yuki::SharedPtr<Yuki::Entity::TemplateEntity>
CameraController::GetInstance()
{
  static Yuki::SharedPtr<Yuki::Entity::TemplateEntity> instance;
  if (!instance.get())
  {
    instance = Yuki::Core::CreateInterfaceInstance<
        Yuki::Entity::TemplateEntity, CameraController>("camera_controller");
  }
  return instance;
}