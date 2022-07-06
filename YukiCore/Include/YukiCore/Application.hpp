/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/Objects.hpp"
#include "YukiComp/Scene.hpp"
#include "YukiDebug/Loggers.hpp"
#include "YukiUtil/System.hpp"

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
