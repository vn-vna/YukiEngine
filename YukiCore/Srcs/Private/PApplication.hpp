/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/Application.hpp"
#include "YukiCore/WindowManager.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/Input.hpp"
#include "YukiComp/Scene.hpp"
#include "YukiDebug/Errors.hpp"
#include "YukiDebug/Loggers.hpp"

#include "PObjects.hpp"
#include "YukiUtil/System.hpp"

namespace Yuki::Core
{

using Comp::IYukiScene;
using Debug::IYukiLogger;
using Utils::IYukiSystem;

class YukiApp final : virtual public IYukiApp,
                      virtual public YukiObject
{
public:
  YukiApp();
  ~YukiApp() override;

  void Reload() override;
  void Terminate() override;
  void RunApp() override;

  SharedPtr<IYukiScene>      GetCurrentScene() override;
  SharedPtr<IYukiGfxControl> GetGraphicsController() override;
  SharedPtr<IYukiInpControl> GetInputController() override;
  SharedPtr<IYukiWindow>     GetWindow() override;
  SharedPtr<IYukiLogger>     GetLogger() override;
  SharedPtr<IYukiThreadPool> GetWorkerPool() override;
  SharedPtr<IYukiSystem>     GetSystemController() override;

  void SetCurrentScene(SharedPtr<IYukiScene> scene) override;

  void Create() override;
  void Awake() override;
  void Update() override;
  void Destroy() override;

private:
  SharedPtr<IYukiWindow>     m_pWindow;
  SharedPtr<IYukiGfxControl> m_pGfxController;
  SharedPtr<IYukiInpControl> m_pInputController;
  SharedPtr<IYukiLogger>     m_pLogger;
  SharedPtr<IYukiScene>      m_pCurrentScene;
  SharedPtr<IYukiThreadPool> m_pWorkerPool;
  SharedPtr<IYukiSystem>     m_pSysCtrl;
  Atomic<bool>               m_bAlive;
  Atomic<bool>               m_bWillCreate;
  Atomic<bool>               m_bWillDestroy;
  Atomic<bool>               m_bWillUpdate;
  Atomic<bool>               m_bWillTerminate;
};

} // namespace Yuki::Core
