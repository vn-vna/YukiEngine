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

using Comp::IScene;
using Debug::ILogger;
using Utils::IYukiSystem;

class YukiApp final : virtual public IApplication,
                      virtual public YukiObject
{
public:
  YukiApp();
  ~YukiApp() override;

  void Reload() override;
  void Terminate() override;
  void RunApp() override;

  SharedPtr<IScene>      GetCurrentScene() override;
  SharedPtr<IGraphics>   GetGraphicsController() override;
  SharedPtr<IInput>      GetInputController() override;
  SharedPtr<IWindow>     GetWindow() override;
  SharedPtr<ILogger>     GetLogger() override;
  SharedPtr<IThreadPool> GetWorkerPool() override;
  SharedPtr<IYukiSystem> GetSystemController() override;

  void SetCurrentScene(SharedPtr<IScene> scene) override;

  void Create() override;
  void Awake() override;
  void Update() override;
  void Destroy() override;

private:
  SharedPtr<IWindow>     m_pWindow;
  SharedPtr<IGraphics>   m_pGfxController;
  SharedPtr<IInput>      m_pInputController;
  SharedPtr<ILogger>     m_pLogger;
  SharedPtr<IScene>      m_pCurrentScene;
  SharedPtr<IThreadPool> m_pWorkerPool;
  SharedPtr<IYukiSystem> m_pSysCtrl;
  Atomic<bool>           m_bAlive;
  Atomic<bool>           m_bWillCreate;
  Atomic<bool>           m_bWillDestroy;
  Atomic<bool>           m_bWillUpdate;
  Atomic<bool>           m_bWillTerminate;
};

} // namespace Yuki::Core
