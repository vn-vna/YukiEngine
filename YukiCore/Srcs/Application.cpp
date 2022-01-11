#include "YukiCore/YukiVE.hpp"
#include "YukiCore/Application.hpp"
#include "YukiCore/Window.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/InputCtrl.hpp"
#include "YukiCore/Error.hpp"
#include "YukiCore/Logger.hpp"

// TEST
// class TestKeyInp : public Yuki::Core::IYukiInpKeyboardCallback
// {
// public:
//   void invoke(int key, int scancode, int action, int modifiers) override
//   {
//     Yuki::StringStream sstr;
//     sstr << "Pressed ke code " << key << " action code " << action << "\n";
//     Yuki::Core::GetYukiApp()->GetLogger()->PushDebugMessage(sstr.str());
//   }
// };
//
// class TestCursorPosInp : public Yuki::Core::IYukiInpCursorCallback
// {
// public:
//   void invoke(int x, int y) override
//   {
//     Yuki::StringStream sstr;
//     sstr << "Cursor position (" << x << ";" << y << ")";
//     Yuki::Core::GetYukiApp()->GetLogger()->PushDebugMessage(sstr.str());
//   }
// };
// TEST

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
  m_pLogger          = Debug::YukiLogger::CreateYukiLogger();
  m_pWindow          = YukiWindow::CreateNewWindow();
  m_pGfxController   = YukiGfxControl::CreateYukiGfxController();
  m_pInputController = YukiInpControl::CreateNewInputControl();
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
  GetLogger()->Create();
  GetWindow()->Create();
  GetGraphicsController()->Create();
}

void YukiApp::Awake()
{
  GetWindow()->Awake();
  GetGraphicsController()->Awake();

  // TEST
  // SharedPtr<IYukiInpKeyboardCallback> callback{new TestKeyInp};
  // GetInputController()->AddKeyboardInputCallback(L"Test::TestInpKey", callback);
  // SharedPtr<IYukiInpCursorCallback> callback{new TestCursorPosInp};
  // GetInputController()->AddCursorInputCallback(L"Test::TestInpCursorPos", callback);
  // TEST
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
  GetGraphicsController()->Destroy();
  GetWindow()->Destroy();
  GetLogger()->Destroy();
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