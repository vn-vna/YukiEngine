#include "YukiCore/YukiPCH.hpp"

#include "PYukiWindow.hpp"
#include "PYukiMesh.hpp"

/// TEST CODE

#include <glm/gtc/matrix_transform.hpp>

Yuki::SharedPtr<Yuki::Comp::IYukiMesh> mesh;

/// TEST CODE

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

  Comp::InitializeMeshShader();

  glfwSwapInterval(1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void YukiWindow::Awake()
{
  // TEST
  std::vector<VertexData> vdata;
  vdata.push_back({{-0.50f, -0.50f, +0.00f}, {0.00f, 1.00f, 0.00f, 1.00f}, {}, 0});
  vdata.push_back({{-0.50f, +0.50f, +0.00f}, {1.00f, 0.00f, 0.00f, 1.00f}, {}, 0});
  vdata.push_back({{+0.50f, -0.50f, +0.00f}, {0.00f, 0.00f, 1.00f, 1.00f}, {}, 0});
  vdata.push_back({{+0.50f, +0.50f, +0.00f}, {1.00f, 1.00f, 0.00f, 1.00f}, {}, 0});

  std::vector<unsigned> indices;
  indices.emplace_back(0);
  indices.emplace_back(1);
  indices.emplace_back(2);
  indices.emplace_back(3);

  IndexData idata = {Core::PrimitiveTopology::TRIANGLE_STRIP, indices};

  mesh = Comp::CreateYukiMesh(vdata, idata, L"MeshTest");
  // TEST

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
  glClearColor(0.00f, 0.00f, 0.00f, 1.00f); // Set clear color
  glClear(GL_COLOR_BUFFER_BIT);             // Clear

  mesh->RenderMesh(glm::identity<glm::mat4>(), glm::identity<glm::mat4>(), glm::identity<glm::mat4>());
}

void YukiWindow::Destroy()
{
  // TEST
  mesh->Destroy();
  // TEST
  Comp::ReleaseMeshShader();

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