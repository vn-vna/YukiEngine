#include "YukiCore/Headers.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/Application.hpp"
#include "YukiCore/Input.hpp"
#include "YukiComp/Mesh.hpp"
#include "YukiComp/Camera.hpp"
#include "YukiDebug/Errors.hpp"

#include "Private/PWindow.hpp"

void initAndCheckGLFW()
{
  if (!glfwInit())
  {
    THROW_YUKI_ERROR(GLFWInitError);
  }
}

void funcGLFWKeyCallback(
    GLFWwindow* pWindow, int key, int scancode, int action, int modifiers
)
{
  Yuki::Core::GetYukiApp()->GetInputController()->ExecuteKeyCallbacks(
      key, scancode, action, modifiers
  );
}

namespace Yuki::Core
{

bool g_bGLFWInited = false;

YukiWindow::YukiWindow()
    : m_pGLFWWindow(nullptr)
{}

YukiWindow::~YukiWindow() = default;

void YukiWindow::ShowWindow()
{
  glfwShowWindow(m_pGLFWWindow);
}

void YukiWindow::HideWindow()
{
  glfwHideWindow(m_pGLFWWindow);
}

void YukiWindow::IconfyWindow()
{
  glfwIconifyWindow(m_pGLFWWindow);
}

void YukiWindow::SetSize(int width, int height)
{
  glfwSetWindowSize(m_pGLFWWindow, width, height);
}

void YukiWindow::SetPosition(int wx, int wy)
{
  glfwSetWindowPos(m_pGLFWWindow, wx, wy);
}

void YukiWindow::SetCursorPos(int cx, int cy)
{
  int wx, wy;
  glfwGetWindowPos(m_pGLFWWindow, &wx, &wy);
  glfwSetCursorPos(m_pGLFWWindow, wx + cx, wy + cy);
}

void YukiWindow::SetTitle(const String& title)
{
  glfwSetWindowTitle(m_pGLFWWindow, title.c_str());
}

bool YukiWindow::ShouldClose()
{
  return glfwWindowShouldClose(m_pGLFWWindow);
}

Vec2F YukiWindow::GetWindowSize()
{
  int w, h;
  glfwGetWindowSize(m_pGLFWWindow, &w, &h);
  return {w, h};
}

GLFWwindow* YukiWindow::GetGLFWWindow()
{
  return m_pGLFWWindow;
}

void YukiWindow::Create()
{
  if (!g_bGLFWInited)
  {
    initAndCheckGLFW();
  }
  g_bGLFWInited = true;

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_SAMPLES, YUKI_WINDOW_SAMPLES);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_pGLFWWindow = glfwCreateWindow(
      YUKI_DEFAULT_WINDOW_WIDTH, YUKI_DEFAULT_WINDOW_HEIGHT,
      YUKI_DEFAULT_WINDOW_TITLE, NULL, NULL
  );
  if (!m_pGLFWWindow)
  {
    THROW_YUKI_ERROR(WindowCreationError);
  }

  glfwSetKeyCallback(m_pGLFWWindow, funcGLFWKeyCallback);

  glfwMakeContextCurrent(m_pGLFWWindow);

  glfwSwapInterval(1);
}

void YukiWindow::Awake()
{
  ShowWindow();
}

void YukiWindow::Update()
{
  double   cursorX, cursorY;
  AutoType pInput = GetYukiApp()->GetInputController();
  glfwGetCursorPos(this->m_pGLFWWindow, &cursorX, &cursorY);
  pInput->ExecuteCursorPosCallback(cursorX, cursorY);
  glfwSwapBuffers(m_pGLFWWindow);
  glfwPollEvents();
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
    g_bGLFWInited = false;
  }
}

SharedPtr<IWindow> CreateNewWindow()
{
  return std::dynamic_pointer_cast<IWindow>(std::make_shared<YukiWindow>());
}

} // namespace Yuki::Core
