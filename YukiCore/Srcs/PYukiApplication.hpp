#pragma once
#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiWindow.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiDebug/YukiLogger.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

class YUKIAPI YukiApp : virtual public IYukiApp,
                        virtual public YukiObject
{
protected:
  SharedPtr<IYukiWindow>        m_pWindow;
  SharedPtr<IYukiGfxControl>    m_pGfxController;
  SharedPtr<IYukiInpControl>    m_pInputController;
  SharedPtr<Debug::IYukiLogger> m_pLogger;
  bool                          m_bAlive;

public:
  YukiApp();
  virtual ~YukiApp() = default;

  SharedPtr<IYukiGfxControl>&    GetGraphicsController() override;
  SharedPtr<IYukiInpControl>&    GetInputController() override;
  SharedPtr<IYukiWindow>&        GetWindow() override;
  SharedPtr<Debug::IYukiLogger>& GetLogger() override;

  void RunApp() override;
  void Create() override;
  void Awake() override;
  void Update() override;
  void Destroy() override;
};

} // namespace Yuki::Core