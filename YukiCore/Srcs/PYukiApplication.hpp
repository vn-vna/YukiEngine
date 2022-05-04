/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiWindow.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiComp/YukiScene.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiDebug/YukiLogger.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

using Debug::IYukiLogger;
using Comp::IYukiScene;

class YUKIAPI YukiApp final : virtual public IYukiApp,
                              virtual public YukiObject
{
protected:
  SharedPtr<IYukiWindow>     m_pWindow;
  SharedPtr<IYukiGfxControl> m_pGfxController;
  SharedPtr<IYukiInpControl> m_pInputController;
  SharedPtr<IYukiLogger>     m_pLogger;
  SharedPtr<IYukiScene>      m_pCurrentScene;
  bool                       m_bAlive;

public:
  YukiApp();
  ~YukiApp() override;

  SharedPtr<IYukiScene>      GetCurrentScene() override;
  SharedPtr<IYukiGfxControl> GetGraphicsController() override;
  SharedPtr<IYukiInpControl> GetInputController() override;
  SharedPtr<IYukiWindow>     GetWindow() override;
  SharedPtr<IYukiLogger>     GetLogger() override;

  void SetCurrentScene(SharedPtr<IYukiScene> scene) override;

  void RunApp() override;
  void Create() override;
  void Awake() override;
  void Update() override;
  void Destroy() override;
};

} // namespace Yuki::Core