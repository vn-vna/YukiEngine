#include "YukiCore/YukiPCH.hpp"

#include "PYukiApplication.hpp"
#include "PYukiTimer.hpp"
#include "PYukiThreadPool.hpp"

namespace Yuki::Core
{

using Chrono::YukiTimer;
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
  m_pWorkerPool      = CreateThreadPool();
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

SharedPtr<IYukiThreadPool> YukiApp::GetWorkerPool()
{
  return m_pWorkerPool;
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
  this->GetLogger()->Create();

  this->GetWindow()->Create();
  this->GetGraphicsController()->Create();

  this->GetWorkerPool()->Start();
  this->GetWorkerPool()->WaitForPoolReady();

  this->GetInputController()->Create();

  m_bWillCreate = false;
}

void YukiApp::Awake()
{
  this->GetWindow()->Awake();
  this->GetGraphicsController()->Awake();
  m_bWillUpdate = true;
}

void YukiApp::Update()
{
  if (!GetCurrentScene()->IsReady())
  {
    this->GetCurrentScene()->Create();
  }

  InvokeAllThreads();
  YukiTimer::UpdateTimers();
  this->GetWorkerPool()->NotifyWorkers();
  this->GetGraphicsController()->Render();
  this->GetWindow()->Update();

  this->GetCurrentScene()->Update();

  if (this->GetWindow()->ShouldClose())
  {
    this->Terminate();
  }
}

void YukiApp::Destroy()
{
  this->GetCurrentScene()->Destroy();
  this->GetInputController()->Destroy();
  this->GetGraphicsController()->Destroy();
  this->GetWindow()->Destroy();

  this->GetWorkerPool()->Terminate();
  this->GetWorkerPool()->Join();

  this->GetLogger()->Destroy();

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