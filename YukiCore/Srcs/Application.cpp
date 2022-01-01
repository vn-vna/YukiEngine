#include "YukiCore/YukiVE.hpp"
#include "YukiCore/Application.hpp"
#include "YukiCore/Window.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/Error.hpp"

namespace Yuki::Core
{

SharedPtr<IYukiApp> g_pGlobalApplication(nullptr);

YukiApp::YukiApp()
    : m_bAlive(false),
      m_pGfxController(nullptr),
      m_pInputManager(nullptr),
      m_pWindow(nullptr)
{
#ifndef NDEBUG
  //OutputDebugStringW(L"[YUKI CONFIGURATION REPORT] Application is running in DEBUG MODE\n");
  std::cout << "[YUKI CONFIGURATION REPORT] Application is running in DEBUG MODE\n";
#else
  std::cout << "[YUKI CONFIGURATION REPORT] Application is running in RELASE MODE\n";
#endif // NDEBUG

  m_pWindow        = YukiWindow::CreateNewWindow();
  m_pGfxController = YukiGfxControl::CreateYukiGfxController();
}

SharedPtr<IYukiGfxControl>& YukiApp::GetGraphicsController()
{
  return m_pGfxController;
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
    std::wcerr << yer.getErrorMessage() << std::endl;
  }

  try
  {
    Destroy();
  }
  catch (const Yuki::Debug::YukiError& yer)
  {
    std::wcerr << yer.getErrorMessage() << std::endl;
  }
}

void YukiApp::Create()
{
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
  GetGraphicsController()->Render();
  GetGraphicsController()->Update();
  GetWindow()->Update();
  if (GetWindow()->ShouldClose())
  {
    m_bAlive = false;
  }
}

void YukiApp::Destroy()
{
  GetWindow()->Destroy();
}

SharedPtr<IYukiApp> CreateYukiApp()
{
  g_pGlobalApplication.reset(reinterpret_cast<IYukiApp*>(new YukiApp()));
  return g_pGlobalApplication;
}

SharedPtr<IYukiApp> GetYukiApp()
{
  return g_pGlobalApplication;
}

} // namespace Yuki::Core