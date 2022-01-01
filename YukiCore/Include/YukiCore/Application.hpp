#pragma once

#include "YukiCore/YukiVE.hpp"
#include "YukiCore/YukiObject.hpp"

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
  virtual SharedPtr<IYukiGfxControl>& GetGraphicsController() = 0;
  virtual SharedPtr<IYukiWindow>&     GetWindow()             = 0;
};

class YUKIAPI YukiApp : IYukiApp
{
protected:
  SharedPtr<IYukiWindow>       m_pWindow;
  SharedPtr<IYukiInputManager> m_pInputManager;
  SharedPtr<IYukiGfxControl>   m_pGfxController;
  bool                         m_bAlive;

public:
  YukiApp();
  virtual ~YukiApp() = default;

  virtual SharedPtr<IYukiGfxControl>& GetGraphicsController() override;
  virtual SharedPtr<IYukiWindow>&     GetWindow() override;

  virtual void RunApp() override;
  virtual void Create() override;
  virtual void Awake() override;
  virtual void Update() override;
  virtual void Destroy() override;
};


SharedPtr<IYukiApp> YUKIAPI CreateYukiApp();
SharedPtr<IYukiApp> YUKIAPI GetYukiApp();

} // namespace Yuki::Core
