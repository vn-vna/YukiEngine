/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 */

#pragma once

#include <YukiEntity/Entity.hpp>
#include <YukiUtil/YukiUtilities.hpp>

using Yuki::Utils::isKeyReleased;
using Yuki::Core::KeyCode;

class SystemControl : virtual public Yuki::Entity::YukiEntity
{
protected:
  Yuki::SharedPtr<Yuki::Comp::IYukiCamera>     pCamera;
  Yuki::SharedPtr<Yuki::Core::IYukiInpControl> pInpControl;

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
}

inline void SystemControl::OnAwake()
{
}

inline void SystemControl::OnUpdate()
{
  AutoType keyT = Yuki::Core::GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_T);
  if (keyT.ctrl && keyT.state == Yuki::Core::KeyState::PRESS)
  {
    Yuki::Core::GetYukiApp()->Terminate();
  }

  AutoType keyR = Yuki::Core::GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_R);
  if (keyR.ctrl && keyR.state == Yuki::Core::KeyState::PRESS)
  {
    Yuki::Core::GetYukiApp()->Reload();
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
