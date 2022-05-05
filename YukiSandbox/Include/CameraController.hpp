/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 */

#pragma once

#include <YukiEntity/Entity.hpp>
#include <YukiUtil/YukiUtilities.hpp>

using Yuki::Utils::IsKeyReleased;
using Yuki::Core::KeyCode;

class CameraController : virtual public Yuki::Entity::YukiEntity
{
protected:
  Yuki::SharedPtr<Yuki::Comp::IYukiCamera>     pCamera;
  Yuki::SharedPtr<Yuki::Core::IYukiInpControl> pInpControl;

public:
  explicit CameraController(const Yuki::String& name);
  ~CameraController() override;

  void OnCreate() override;
  void OnAwake() override;
  void OnUpdate() override;
  void OnRender() override;
  void OnDestroy() override;

  static Yuki::SharedPtr<Yuki::Entity::YukiEntity> GetInstance();
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
}

inline void CameraController::OnRender()
{
}

inline void CameraController::OnDestroy()
{
}

inline CameraController::CameraController(const Yuki::String& name)
    : Yuki::Entity::YukiEntity(name)
{
}

inline CameraController::~CameraController() = default;

inline Yuki::SharedPtr<Yuki::Entity::YukiEntity> CameraController::GetInstance()
{
  static Yuki::SharedPtr<Yuki::Entity::YukiEntity> instance;
  if (!instance.get())
  {
    instance = Yuki::Core::CreateInterfaceInstance<Yuki::Entity::YukiEntity, CameraController>("camera_controller");
  }
  return instance;
}