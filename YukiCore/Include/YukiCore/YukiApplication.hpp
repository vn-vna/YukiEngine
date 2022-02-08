#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiDebug/YukiLogger.hpp"

namespace Yuki::Core
{

SharedPtr<IYukiApp> YUKIAPI CreateYukiApp();
SharedPtr<IYukiApp> YUKIAPI GetYukiApp();

class YUKIAPI IYukiApp : public IYukiObject
{
public:
  virtual void RunApp() = 0;

  //virtual IYukiInputManager& getInputManager() = 0;
  virtual SharedPtr<IYukiGfxControl>&    GetGraphicsController() = 0;
  virtual SharedPtr<IYukiInpControl>&    GetInputController()    = 0;
  virtual SharedPtr<IYukiWindow>&        GetWindow()             = 0;
  virtual SharedPtr<Debug::IYukiLogger>& GetLogger()             = 0;
};

} // namespace Yuki::Core
