#pragma once

#include "YukiCore/YukiVE.hpp"
#include "YukiCore/YukiObject.hpp"
#include "Logger.hpp"

namespace Yuki::Core
{

class YUKIAPI IYukiApp;
class YUKIAPI IYukiInputManager;
class YUKIAPI IYukiGfxControl;
class YUKIAPI IYukiWindow;

class YUKIAPI IYukiApp : public IYukiObject
{
public:
  IYukiApp()          = default;
  virtual ~IYukiApp() = default;

  virtual void RunApp() = 0;

  //virtual IYukiInputManager& getInputManager() = 0;
  virtual SharedPtr<IYukiGfxControl>&    GetGraphicsController() = 0;
  virtual SharedPtr<IYukiWindow>&        GetWindow()             = 0;
  virtual SharedPtr<Debug::IYukiLogger>& GetLogger()             = 0;
};

class YUKIAPI YukiApp : IYukiApp
{
protected:
  SharedPtr<IYukiWindow>        m_pWindow;
  SharedPtr<IYukiInputManager>  m_pInputManager;
  SharedPtr<IYukiGfxControl>    m_pGfxController;
  SharedPtr<Debug::IYukiLogger> m_pLogger;
  bool                          m_bAlive;

public:
  YukiApp();
  virtual ~YukiApp() = default;

  SharedPtr<IYukiGfxControl>&    GetGraphicsController() override;
  SharedPtr<IYukiWindow>&        GetWindow() override;
  SharedPtr<Debug::IYukiLogger>& GetLogger() override;

  void RunApp() override;
  void Create() override;
  void Awake() override;
  void Update() override;
  void Destroy() override;
};


SharedPtr<IYukiApp> YUKIAPI CreateYukiApp();
SharedPtr<IYukiApp> YUKIAPI GetYukiApp();

} // namespace Yuki::Core
