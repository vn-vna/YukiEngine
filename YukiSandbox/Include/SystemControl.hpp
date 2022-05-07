/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 */

#pragma once

#include <YukiCore/YukiWindow.hpp>
#include <YukiEntity/Entity.hpp>
#include <YukiUtil/YukiUtilities.hpp>

using Yuki::Utils::IsKeyReleased;
using Yuki::Core::KeyCode;

class SystemControl : virtual public Yuki::Entity::YukiEntity
{
protected:
  Yuki::SharedPtr<Yuki::Core::IYukiInpControl> pInpControl;
  Yuki::SharedPtr<Yuki::Debug::IYukiLogger>    pLogger;
  Yuki::SharedPtr<Yuki::Core::IYukiWindow>     pWindow;

public:
  explicit SystemControl(const Yuki::String& name);
  ~SystemControl() override;

  void OnCreate() override;
  void OnAwake() override;
  void OnUpdate() override;
  void OnRender() override;
  void OnDestroy() override;

  static Yuki::SharedPtr<Yuki::Entity::YukiEntity> GetInstance();
};

inline SystemControl::SystemControl(const Yuki::String& name)
    : Yuki::Entity::YukiEntity(name)
{}

inline SystemControl::~SystemControl() = default;

inline void SystemControl::OnCreate()
{
  pInpControl = Yuki::Core::GetYukiApp()->GetInputController();
  pLogger     = Yuki::Core::GetYukiApp()->GetLogger();
  pWindow     = Yuki::Core::GetYukiApp()->GetWindow();
}

inline void SystemControl::OnAwake()
{
}

inline void SystemControl::OnUpdate()
{
  AutoType keyT = pInpControl->GetKeyStatus(KeyCode::KEY_T);
  if (keyT.ctrl && keyT.state == Yuki::Core::KeyState::PRESS)
  {
    Yuki::Core::GetYukiApp()->Terminate();
  }

  AutoType keyR = pInpControl->GetKeyStatus(KeyCode::KEY_R);
  if (keyR.ctrl && keyR.state == Yuki::Core::KeyState::PRESS)
  {
    Yuki::Core::GetYukiApp()->Reload();
  }

  if (!Yuki::Utils::IsKeyReleased(Yuki::Core::KeyCode::KEY_F3))
  {
    AutoType windowSize = pWindow->GetWindowSize();
    pInpControl->LockMouse(windowSize.x / 2, windowSize.y / 2);
  }

  if (!Yuki::Utils::IsKeyReleased(Yuki::Core::KeyCode::KEY_F2))
  {
    pInpControl->UnlockMouse();
  }
}

inline void SystemControl::OnRender()
{
}

inline void SystemControl::OnDestroy()
{
}

inline Yuki::SharedPtr<Yuki::Entity::YukiEntity> SystemControl::GetInstance()
{
  static Yuki::SharedPtr<Yuki::Entity::YukiEntity> instance;
  if (!instance.get())
  {
    instance = Yuki::Core::CreateInterfaceInstance<Yuki::Entity::YukiEntity, SystemControl>("sys_ctrl");
  }
  return instance;
}
