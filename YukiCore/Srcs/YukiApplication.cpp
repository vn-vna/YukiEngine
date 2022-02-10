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
      m_pLogger(nullptr),
      m_bCreated(false)
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
    Create();
    Awake();
    m_bAlive = true;
    while (m_bAlive)
    {
      Update();
    }
  }
  catch (const Yuki::Debug::YukiError& yer)
  {
    GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }

  try
  {
    Destroy();
  }
  catch (const Yuki::Debug::YukiError& yer)
  {
    GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void YukiApp::Create()
{
  if (m_bCreated)
  {
    THROW_YUKI_ERROR(Debug::YukiApplicationRecreationError);
  }
  GetLogger()->Create();
  GetWindow()->Create();
  GetGraphicsController()->Create();
  m_bCreated = true;
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
  if (!m_bCreated)
  {
    THROW_YUKI_ERROR(Debug::YukiApplicationNotCreatedError);
  }
  GetGraphicsController()->Destroy();
  GetWindow()->Destroy();
  GetLogger()->Destroy();
  m_bCreated = false;
}

SharedPtr<IYukiApp> CreateYukiApp()
{
  if (g_pGlobalApplication.get())
  {
    THROW_YUKI_ERROR(Debug::YukiApplicationInstanceExistsError);
  }
  g_pGlobalApplication.reset((IYukiApp*) new YukiApp());
  return g_pGlobalApplication;
}

SharedPtr<IYukiApp> GetYukiApp()
{
  return g_pGlobalApplication;
}

} // namespace Yuki::Core