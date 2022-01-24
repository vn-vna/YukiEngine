#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiWindow.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"

#define YUKI_DEFAULT_WINDOW_WIDTH  1366
#define YUKI_DEFAULT_WINDOW_HEIGHT 768
#define YUKI_DEFAULT_WINDOW_TITLE  "Window"
#define YUKI_WINDOW_SAMPLES        4

#pragma region DETAILED_HEADERS

void funcGLFWKeyCallback(GLFWwindow* pwindow, int key, int scancode, int action, int modifiers);
void funcGLFWCursorCallback(GLFWwindow* window, double x, double y);

namespace Yuki::Core
{

class YukiWindow : public IYukiWindow
{
protected:
  GLFWwindow* m_pGLFWWindow;

public:
  YukiWindow();
  virtual ~YukiWindow();

  void        ShowWindow() override;
  void        HideWindow() override;
  void        SetSize(const int& width, const int& height) override;
  void        SetPosition(const int& wx, const int& wy) override;
  void        SetCursoPos(const int& cx, const int& cy) override;
  void        SetTitle(const AsciiString& title) override;
  void        SetTitle(const String& title) override;
  bool        ShouldClose() override;
  glm::vec2   GetWindowSize() override;
  GLFWwindow* GetGLFWWindow() override;

  void Create() override;
  void Awake() override;
  void Update() override;
  void Render() override;
  void Destroy() override;
};

} // namespace Yuki::Core

#pragma endregion

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

glm::vec2 YukiWindow::GetWindowSize()
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
    if (!glfwInit())
    {
      THROW_YUKI_ERROR(Yuki::Debug::YukiGLFWInitError);
    }
  }
  g_bGLFWInited = true;

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_SAMPLES, YUKI_WINDOW_SAMPLES);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_pGLFWWindow = glfwCreateWindow(YUKI_DEFAULT_WINDOW_WIDTH, YUKI_DEFAULT_WINDOW_HEIGHT, YUKI_DEFAULT_WINDOW_TITLE, NULL, NULL);
  if (!m_pGLFWWindow)
  {
    THROW_YUKI_ERROR(Yuki::Debug::YukiWindowCreationError);
  }

  glfwMakeContextCurrent(m_pGLFWWindow);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
  {
    THROW_YUKI_ERROR(Debug::YukiGladLoadGLLoaderError);
  }

  glfwSetKeyCallback(m_pGLFWWindow, funcGLFWKeyCallback);
  glfwSetCursorPosCallback(m_pGLFWWindow, funcGLFWCursorCallback);
}

void YukiWindow::Awake()
{
  glfwSwapInterval(1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  ShowWindow();
}

void YukiWindow::Update()
{
  Render();
  glfwSwapBuffers(m_pGLFWWindow);
  glfwPollEvents();
}

void YukiWindow::Render()
{
  // Clear screen
  glBindFramebuffer(GL_FRAMEBUFFER, 0);     // Use Default FB
  glClearColor(0.00f, 0.00f, 1.00f, 1.00f); // Set clear color
  glClear(GL_COLOR_BUFFER_BIT);             // Clear screen
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

SharedPtr<IYukiWindow> CreateNewWindow()
{
  return {(IYukiWindow*) (new YukiWindow), [](IYukiWindow* p) { delete p; }};
}

} // namespace Yuki::Core