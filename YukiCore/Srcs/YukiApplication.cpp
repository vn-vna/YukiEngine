#include "YukiCore/YukiPCH.hpp"

#include "PYukiApplication.hpp"

namespace Yuki::Core
{

SharedPtr<IYukiApp> g_pGlobalApplication(nullptr);

YukiApp::YukiApp()
    : m_bAlive(false),
      m_pGfxController(nullptr),
      m_pInputController(nullptr),
      m_pWindow(nullptr),
      m_pLogger(nullptr)
{
  m_pLogger          = Debug::CreateYukiLogger();
  m_pWindow          = CreateNewWindow();
  m_pInputController = CreateNewInputControl();
  m_pGfxController   = CreateGraphicsController();
}

SharedPtr<IYukiGfxControl>& YukiApp::GetGraphicsController()
{
  return m_pGfxController;
}

SharedPtr<IYukiInpControl>& YukiApp::GetInputController()
{
  return m_pInputController;
}

SharedPtr<Debug::IYukiLogger>& YukiApp::GetLogger()
{
  return m_pLogger;
}

SharedPtr<IYukiWindow>& YukiApp::GetWindow()
{
  return m_pWindow;
}

void YukiApp::RunApp()
{
  try
  {
    this->Create();
    this->Awake();
    m_bAlive = true;
    while (m_bAlive)
    {
      this->Update();
    }
  }
  catch (const Yuki::Debug::YukiError& yer)
  {
    yer.PushErrorMessage();
  }

  try
  {
    this->Destroy();
  }
  catch (const Yuki::Debug::YukiError& yer)
  {
    yer.PushErrorMessage();
  }
}

void YukiApp::Create()
{
  GetLogger()->Create();
  GetWindow()->Create();
  GetGraphicsController()->Create();
}

void YukiApp::Awake()
{
  GetWindow()->Awake();
  GetGraphicsController()->Awake();
}

void YukiApp::Update()
{
  GetWindow()->Update();
  GetGraphicsController()->Render();
  if (GetWindow()->ShouldClose())
  {
    m_bAlive = false;
  }
}

void YukiApp::Destroy()
{
  GetGraphicsController()->Destroy();
  GetWindow()->Destroy();
  GetLogger()->Destroy();
}

SharedPtr<IYukiApp> CreateYukiApp()
{
  g_pGlobalApplication = CreateInterfaceInstance<IYukiApp, YukiApp>();
  return g_pGlobalApplication;
}

SharedPtr<IYukiApp> GetYukiApp()
{
  return g_pGlobalApplication;
}

} // namespace Yuki::Core