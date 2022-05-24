/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiComp/YukiScene.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiUtil/YukiSystem.hpp"

namespace Yuki::Core
{

using Comp::IYukiScene;
using Debug::IYukiLogger;
using Utils::IYukiSystem;

class IYukiApp : virtual public IYukiObject
{
public:
  virtual void RunApp()    = 0;
  virtual void Reload()    = 0;
  virtual void Terminate() = 0;

  virtual SharedPtr<IYukiScene>      GetCurrentScene()       = 0;
  virtual SharedPtr<IYukiGfxControl> GetGraphicsController() = 0;
  virtual SharedPtr<IYukiInpControl> GetInputController()    = 0;
  virtual SharedPtr<IYukiWindow>     GetWindow()             = 0;
  virtual SharedPtr<IYukiLogger>     GetLogger()             = 0;
  virtual SharedPtr<IYukiThreadPool> GetWorkerPool()         = 0;
  virtual SharedPtr<IYukiSystem>     GetSystemController()   = 0;

  virtual void SetCurrentScene(SharedPtr<IYukiScene> scene) = 0;
};

SharedPtr<IYukiApp> CreateYukiApp();
SharedPtr<IYukiApp> GetYukiApp();

} // namespace Yuki::Core
