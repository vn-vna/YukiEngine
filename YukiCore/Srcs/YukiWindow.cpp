#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiWindow.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiCore/YukiError.hpp"

#define YUKI_DEFAULT_WINDOW_WIDTH  1366
#define YUKI_DEFAULT_WINDOW_HEIGHT 768
#define YUKI_DEFAULT_WINDOW_TITLE  "Window"
#define YUKI_WINDOW_SAMPLES        4

void funcGLFWKeyCallback(GLFWwindow* pwindow, int key, int scancode, int action, int modifiers)
{
  Yuki::Core::GetYukiApp()->GetInputController()->ExecuteKeyCallbacks(key, scancode, action, modifiers);
}

void funcGLFWCursorCallback(GLFWwindow* window, double x, double y)
{
  Yuki::Core::GetYukiApp()->GetInputController()->ExecuteCursorPosCallback((int) x, (int) y);
}

namespace Yuki::Core
{

bool g_bGLFWInited = false;

YukiWindow::YukiWindow()
    : m_pGLFWWindow(nullptr)
{}

YukiWindow::~YukiWindow()
{}

void YukiWindow::ShowWindow()
{
  glfwShowWindow(m_pGLFWWindow);
}

void YukiWindow::HideWindow()
{
  glfwHideWindow(m_pGLFWWindow);
}

void YukiWindow::SetSize(const int& width, const int& height)
{
  glfwSetWindowSize(m_pGLFWWindow, width, height);
}

void YukiWindow::SetPosition(const int& wx, const int& wy)
{
  glfwSetWindowPos(m_pGLFWWindow, wx, wy);
}

void YukiWindow::SetCursoPos(const int& cx, const int& cy)
{
  glfwSetCursorPos(m_pGLFWWindow, cx, cy);
}

void YukiWindow::SetTitle(const AsciiString& title)
{
  glfwSetWindowTitle(m_pGLFWWindow, title.c_str());
}

void YukiWindow::SetTitle(const String& title)
{
  AsciiStringStream ss = {};
  ss << title.c_str();
  AsciiString str = ss.str();
  glfwSetWindowTitle(m_pGLFWWindow, str.c_str());
}

bool YukiWindow::ShouldClose()
{
  return glfwWindowShouldClose(m_pGLFWWindow);
}

HWND YukiWindow::GetWindowHandler()
{
  return glfwGetWin32Window(m_pGLFWWindow);
}

GLFWwindow* YukiWindow::GetGLFWWindow()
{
  return m_pGLFWWindow;
}

void YukiWindow::Create()
{
  if (!glfwInit())
  {
    THROW_YUKI_ERROR(Yuki::Debug::YukiGLFWInitError);
  }
  g_bGLFWInited = true;

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_SAMPLES, YUKI_WINDOW_SAMPLES);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  m_pGLFWWindow = glfwCreateWindow(YUKI_DEFAULT_WINDOW_WIDTH, YUKI_DEFAULT_WINDOW_HEIGHT, YUKI_DEFAULT_WINDOW_TITLE, NULL, NULL);
  if (!m_pGLFWWindow)
  {
    THROW_YUKI_ERROR(Yuki::Debug::YukiWindowCreationError);
  }

  glfwSetKeyCallback(m_pGLFWWindow, funcGLFWKeyCallback);
  glfwSetCursorPosCallback(m_pGLFWWindow, funcGLFWCursorCallback);
}

void YukiWindow::Awake()
{
  glfwSwapInterval(1);
  ShowWindow();
}

void YukiWindow::Update()
{
  glfwSwapBuffers(m_pGLFWWindow);
  glfwPollEvents();
}

void YukiWindow::Render()
{
  // render actions
}

void YukiWindow::Destroy()
{
  if (m_pGLFWWindow)
  {
    glfwDestroyWindow(m_pGLFWWindow);
    m_pGLFWWindow = nullptr;
  }
  if (g_bGLFWInited)
  {
    glfwTerminate();
  }
}

SharedPtr<IYukiWindow> YukiWindow::CreateNewWindow()
{
  return {(IYukiWindow*) (new YukiWindow), [](IYukiWindow* p) { delete p; }};
}

} // namespace Yuki::Core