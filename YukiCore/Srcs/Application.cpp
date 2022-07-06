#include "YukiComp/Scene.hpp"
#include "YukiCore/Headers.hpp"
#include "YukiDebug/Errors.hpp"
#include "YukiUtil/System.hpp"

#include "Private/PApplication.hpp"
#include "Private/PTimer.hpp"
#include "Private/PThreadPool.hpp"

namespace Yuki::Core
{

using Chrono::YukiTimer;
using Debug::CreateYukiLogger;
using Debug::Errors;
using Utils::CreateYukiSystemControl;
using Utils::IYukiSystem;

SharedPtr<IYukiApp> g_pGlobalApplication(nullptr);

YukiApp::YukiApp()
    : m_bAlive(false),
      m_bWillCreate(true),
      m_bWillUpdate(false),
      m_bWillDestroy(false),
      m_bWillTerminate(false),
      m_pCurrentScene(nullptr)
{
  m_pLogger          = CreateYukiLogger();
  m_pWindow          = CreateNewWindow();
  m_pInputController = CreateNewInputControl();
  m_pGfxController   = CreateGraphicsController();
  m_pWorkerPool      = CreateThreadPool();
  m_pSysCtrl         = CreateYukiSystemControl();
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

SharedPtr<IYukiSystem> YukiApp::GetSystemController()
{
  return m_pSysCtrl;
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
  catch (const Errors& yer)
  {
    yer.PushErrorMessage();
  }
}

void YukiApp::Create()
{
  m_pLogger->Create();

  m_pWindow->Create();
  m_pGfxController->Create();

  m_pWorkerPool->Start();
  m_pWorkerPool->WaitForPoolReady();
  m_pSysCtrl->Create();

  m_pInputController->Create();

  m_bWillCreate = false;
}

void YukiApp::Awake()
{
  m_pWindow->Awake();
  m_pGfxController->Awake();
  m_pCurrentScene->Awake();
  m_bWillUpdate = true;
}

void YukiApp::Update()
{
  if (!m_pCurrentScene->IsReady())
  {
    m_pCurrentScene->Create();
  }

  InvokeAllThreads();
  YukiTimer::UpdateTimers();
  m_pWorkerPool->NotifyWorkers();
  m_pGfxController->Render();
  m_pWindow->Update();

  m_pCurrentScene->Update();

  if (m_pWindow->ShouldClose())
  {
    this->Terminate();
  }
}

void YukiApp::Destroy()
{
  m_pCurrentScene->Destroy();
  m_pInputController->Destroy();
  m_pGfxController->Destroy();
  m_pWindow->Destroy();

  m_pWorkerPool->Terminate();
  m_pWorkerPool->Join();

  m_pLogger->Destroy();

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
  if (g_pGlobalApplication.get())
  {
    THROW_YUKI_ERROR(AppCreated);
  }
  g_pGlobalApplication = CreateInterfaceInstance<IYukiApp, YukiApp>();
  return g_pGlobalApplication;
}

SharedPtr<IYukiApp> GetYukiApp()
{
  return g_pGlobalApplication;
}

} // namespace Yuki::Core
