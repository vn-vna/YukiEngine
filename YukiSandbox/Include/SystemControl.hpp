/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 */

#pragma once

#include "YukiCore/YukiInputCtrl.hpp"
#include <YukiCore/YukiPCH.hpp>
#include <YukiCore/YukiApplication.hpp>
#include <YukiDebug/YukiLogger.hpp>
#include <YukiEntity/Entity.hpp>
#include <YukiUtil/YukiChrono.hpp>
#include <YukiUtil/YukiUtilities.hpp>
#include <YukiUtil/YukiSystem.hpp>

#include <fmt/format.h>

using Yuki::Core::KeyCode;
using Yuki::Utils::IsKeyReleased;

class SystemControl : virtual public Yuki::Entity::TemplateEntity
{
protected:
  Yuki::SharedPtr<Yuki::Chrono::IYukiTimer>    pTimer;
  Yuki::SharedPtr<Yuki::Core::IYukiApp>        pApp;
  Yuki::SharedPtr<Yuki::Core::IYukiInpControl> pInpControl;
  Yuki::SharedPtr<Yuki::Comp::IYukiCamera>     pCamera;
  Yuki::SharedPtr<Yuki::Debug::IYukiLogger>    pLogger;
  Yuki::SharedPtr<Yuki::Utils::IYukiSystem>    pSysControl;
  bool                                         bDefaultCursor;

public:
  explicit SystemControl(const Yuki::String& name);
  ~SystemControl() override;

  void OnCreate() override;
  void OnAwake() override;
  void OnUpdate() override;
  void OnRender() override;
  void OnDestroy() override;

  static Yuki::SharedPtr<Yuki::Entity::TemplateEntity> GetInstance();
};

inline SystemControl::SystemControl(const Yuki::String& name) : Yuki::Entity::TemplateEntity(name), bDefaultCursor(true)
{}

inline SystemControl::~SystemControl() = default;

inline void SystemControl::OnCreate()
{
  pApp        = Yuki::Core::GetYukiApp();
  pInpControl = pApp->GetInputController();
  pSysControl = pApp->GetSystemController();
  pLogger     = pApp->GetLogger();

  pTimer = Yuki::Chrono::CreateTimer(
      [&](Yuki::Chrono::IYukiTimer* pTimer) {
        AutoType resActivity = pSysControl->GetResourceActivityInfo();
        pLogger->PushDebugMessage(
            fmt::format("CPU Usage: {}%\n\tMem Usages: {}Bs", resActivity.avgCpuLoad, resActivity.memoryUsed));
      },
      1'000'000'000);

  pTimer->Start();
}

inline void SystemControl::OnAwake() {}

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
    Yuki::Core::GetYukiApp()->GetWorkerPool()->PushAction([]() { std::cout << "Pressed V\n"; });
  }

  if (!IsKeyReleased(Yuki::Core::KeyCode::KEY_V) && bDefaultCursor)
  {
    pInpControl->SetCursorStandardStyle(Yuki::Core::StandardCursorType::CURSOR_HAND);
    bDefaultCursor = false;
  }

  if (!IsKeyReleased(Yuki::Core::KeyCode::KEY_X) && !bDefaultCursor)
  {
    pInpControl->SetCursorStandardStyle(Yuki::Core::StandardCursorType::DEFAULT);
    bDefaultCursor = true;
  }
}

inline void SystemControl::OnRender() {}

inline void SystemControl::OnDestroy() {}

inline Yuki::SharedPtr<Yuki::Entity::TemplateEntity> SystemControl::GetInstance()
{
  static Yuki::SharedPtr<Yuki::Entity::TemplateEntity> instance;
  if (!instance.get())
  {
    instance = Yuki::Core::CreateInterfaceInstance<Yuki::Entity::TemplateEntity, SystemControl>("sys_ctrl");
  }
  return instance;
}
