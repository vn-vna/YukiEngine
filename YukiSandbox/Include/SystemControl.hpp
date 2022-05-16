/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 */

#pragma once

#include <YukiEntity/Entity.hpp>
#include <YukiUtil/YukiUtilities.hpp>
#include <YukiUtil/YukiSystem.hpp>

using Yuki::Core::KeyCode;

class SystemControl : virtual public Yuki::Entity::YukiEntity
{
protected:
  Yuki::SharedPtr<Yuki::Comp::IYukiCamera>     pCamera;
  Yuki::SharedPtr<Yuki::Core::IYukiInpControl> pInpControl;
  Yuki::SharedPtr<Yuki::Chrono::IYukiTimer>    pTimer;
  Yuki::SharedPtr<Yuki::Utils::IYukiSystem>    pSysControl;

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
  pSysControl = Yuki::Utils::GetYukiSystemController();

  pTimer = Yuki::Chrono::CreateTimer([&](Yuki::Chrono::IYukiTimer* pTimer) {
    AutoType info = pSysControl->GetResourceActivityInfo();
    std::cout << "Cpu AVG = " << info.avgCpuLoad << "%\n"
              << "Ram Usage = " << (float) info.memoryUsed / std::pow(1024, 3) << "GB\n";
  },
      1'000'000'000);

  pTimer->Start();
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

  if (!IsKeyReleased(Yuki::Core::KeyCode::KEY_1))
  {
    pTimer->Pause();
  }

  if (!IsKeyReleased(Yuki::Core::KeyCode::KEY_2))
  {
    pTimer->Resume();
  }

  if (!IsKeyReleased(Yuki::Core::KeyCode::KEY_3))
  {
    pTimer->Terminate();
  }

  if (!IsKeyReleased(Yuki::Core::KeyCode::KEY_F1))
  {
    pInpControl->LockMouse(1336 / 2, 768 / 2);
  }

  if (!IsKeyReleased(Yuki::Core::KeyCode::KEY_F2))
  {
    pInpControl->UnlockMouse();
  }

  if (!IsKeyReleased(Yuki::Core::KeyCode::KEY_V))
  {
    Yuki::Core::GetYukiApp()->GetWorkerPool()->PushAction([]() {
      std::cout << "Pressed V\n";
    });
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
