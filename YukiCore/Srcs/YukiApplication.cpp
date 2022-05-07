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
      m_pLogger(nullptr),
      m_bWillCreate(true),
      m_bWillUpdate(false),
      m_bWillDestroy(false),
      m_bWillTerminate(false)
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
    m_bAlive = true;

    while (m_bAlive)
    {
      if (m_bWillCreate)
      {
        this->Create();
        this->Awake();
      }

      if (m_bWillUpdate)
      {
        this->Update();
      }

      if (m_bWillDestroy || m_bWillTerminate)
      {
        this->Destroy();
      }
    }
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
  GetInputController()->Create();
  GetGraphicsController()->Create();
  m_bWillCreate = false;
}

void YukiApp::Awake()
{
  GetWindow()->Awake();
  GetGraphicsController()->Awake();
  m_bWillUpdate = true;
}

void YukiApp::Update()
{
  if (!GetCurrentScene()->IsReady())
  {
    GetCurrentScene()->Create();
  }

  GetGraphicsController()->Render();
  GetWindow()->Update();

  GetCurrentScene()->Update();

  if (GetWindow()->ShouldClose())
  {
    Terminate();
  }
}

void YukiApp::Destroy()
{
  GetCurrentScene()->Destroy();
  GetGraphicsController()->Destroy();
  GetInputController()->Destroy();
  GetWindow()->Destroy();
  GetLogger()->Destroy();

  if (m_bWillTerminate)
  {
    m_bAlive = false;
  }
  else
  {
    m_bWillCreate    = true;
    m_bWillDestroy   = false;
    m_bWillTerminate = false;
  }
}

void YukiApp::SetCurrentScene(SharedPtr<IYukiScene> scene)
{
  m_pCurrentScene = scene;
}

void YukiApp::Reload()
{
  m_bWillDestroy = true;
}

void YukiApp::Terminate()
{
  m_bWillTerminate = true;
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