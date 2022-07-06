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

using Comp::IScene;
using Debug::ILogger;
using Utils::IYukiSystem;

class IApplication : virtual public IObject
{
public:
  virtual void RunApp()    = 0;
  virtual void Reload()    = 0;
  virtual void Terminate() = 0;

  virtual SharedPtr<IScene>      GetCurrentScene()       = 0;
  virtual SharedPtr<IGraphics>   GetGraphicsController() = 0;
  virtual SharedPtr<IInput>      GetInputController()    = 0;
  virtual SharedPtr<IWindow>     GetWindow()             = 0;
  virtual SharedPtr<ILogger>     GetLogger()             = 0;
  virtual SharedPtr<IThreadPool> GetWorkerPool()         = 0;
  virtual SharedPtr<IYukiSystem> GetSystemController()   = 0;

  virtual void SetCurrentScene(SharedPtr<IScene> scene) = 0;
};

SharedPtr<IApplication> CreateYukiApp();
SharedPtr<IApplication> GetYukiApp();

} // namespace Yuki::Core
