#include "YukiCore/YukiPCH.hpp"

#include "PYukiApplication.hpp"

namespace Yuki::Core
{

using Debug::YukiError;
using Debug::CreateYukiLogger;

SharedPtr<IYukiApp> g_pGlobalApplication(nullptr);

YukiApp::YukiApp()
    : m_bAlive(false),
      m_pGfxController(nullptr),
      m_pInputController(nullptr),
      m_pWindow(nullptr),
      m_pLogger(nullptr)
{
  m_pLogger          = CreateYukiLogger();
  m_pWindow          = CreateNewWindow();
  m_pInputController = CreateNewInputControl();
  m_pGfxController   = CreateGraphicsController();
}

YukiApp::~YukiApp() = default;

SharedPtr<IYukiScene> YukiApp::GetCurrentScene()
{
  return m_pCurrentScene;
}

SharedPtr<IYukiGfxControl> YukiApp::GetGraphicsController()
{
  return m_pGfxController;
}

SharedPtr<IYukiInpControl> YukiApp::GetInputController()
{
  return m_pInputController;
}

SharedPtr<IYukiLogger> YukiApp::GetLogger()
{
  return m_pLogger;
}

SharedPtr<IYukiWindow> YukiApp::GetWindow()
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
  catch (const YukiError& yer)
  {
    yer.PushErrorMessage();
  }

  try
  {
    this->Destroy();
  }
  catch (const YukiError& yer)
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
  if (!GetCurrentScene()->IsReady())
  {
    GetCurrentScene()->Create();
  }
  GetWindow()->Update();
  GetGraphicsController()->Render();
  GetCurrentScene()->Update();
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
  GetCurrentScene()->Destroy();
}

void YukiApp::SetCurrentScene(SharedPtr<IYukiScene> scene)
{
  m_pCurrentScene = scene;
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