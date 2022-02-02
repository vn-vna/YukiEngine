#include "YukiCore/YukiPCH.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiComp/YukiMesh.hpp"
#include "YukiComp/YukiCamera.hpp"

#include "PYukiGraphicsControl.hpp"


/// TEST CODE

#include <glm/gtc/matrix_transform.hpp>

Yuki::SharedPtr<Yuki::Comp::IYukiMesh>   mesh;
Yuki::SharedPtr<Yuki::Comp::IYukiCamera> camera;

/// TEST CODE

namespace Yuki::Core
{

YukiGfxControl::YukiGfxControl()
{}

YukiGfxControl::~YukiGfxControl() = default;

void YukiGfxControl::Create()
{
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
  {
    THROW_YUKI_ERROR(Debug::YukiGladLoadGLLoaderError);
  }

  Comp::InitializeMeshShader();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void YukiGfxControl::Awake()
{

  // TEST
  camera = Comp::CreateYukiCamera();
  camera->SetFieldOfView(glm::radians(60.0f));

  camera->SetCameraKeyCallback(
      [&](const int& key, const int& scancode, const int& action, const int& modifiers) {
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
          switch (key)
          {
          case GLFW_KEY_A:
            camera->SetCameraPosition(camera->GetCameraPosition() - 0.10f * camera->GetCameraHorizontalAxis());
            break;
          case GLFW_KEY_D:
            camera->SetCameraPosition(camera->GetCameraPosition() + 0.10f * camera->GetCameraHorizontalAxis());
            break;
          case GLFW_KEY_W:
            camera->SetCameraPosition(camera->GetCameraPosition() + 0.10f * camera->GetCameraVerticalAxis());
            break;
          case GLFW_KEY_S:
            camera->SetCameraPosition(camera->GetCameraPosition() - 0.10f * camera->GetCameraVerticalAxis());
            break;
          case GLFW_KEY_Q:
            camera->SetCameraPosition(camera->GetCameraPosition() + 0.10f * camera->GetCameraTopAxis());
            break;
          case GLFW_KEY_E:
            camera->SetCameraPosition(camera->GetCameraPosition() - 0.10f * camera->GetCameraTopAxis());
            break;

          case GLFW_KEY_M:
            camera->CameraRotateViewport(glm::radians(1.00f));
            break;
          case GLFW_KEY_N:
            camera->CameraRotateViewport(glm::radians(-1.00f));
            break;

          case GLFW_KEY_Z:
            camera->SetFieldOfView(camera->GetFieldOfView() + glm::radians(5.0f));
            break;
          case GLFW_KEY_X:
            camera->SetFieldOfView(camera->GetFieldOfView() - glm::radians(5.0f));
            break;

          case GLFW_KEY_UP:
            camera->CameraRotateDirection(camera->GetCameraHorizontalAxis(), glm::radians(+1.00f));
            break;
          case GLFW_KEY_DOWN:
            camera->CameraRotateDirection(camera->GetCameraHorizontalAxis(), glm::radians(-1.00f));
            break;
          case GLFW_KEY_LEFT:
            camera->CameraRotateDirection(camera->GetCameraTopAxis(), glm::radians(+1.00f));
            break;
          case GLFW_KEY_RIGHT:
            camera->CameraRotateDirection(camera->GetCameraTopAxis(), glm::radians(-1.00f));
            break;

          default:
            break;
          }
        }
      });

  unsigned vertexFlag = 0 | (unsigned) VertexFlag::ENABLE_LIGHTNING;

  std::vector<VertexData> vdata;
  vdata.push_back({{-0.50f, -0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag});
  vdata.push_back({{-0.50f, +0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag});
  vdata.push_back({{+0.50f, -0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag});
  vdata.push_back({{+0.50f, +0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag});
  vdata.push_back({{-0.50f, -0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag});
  vdata.push_back({{-0.50f, +0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag});
  vdata.push_back({{+0.50f, -0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag});
  vdata.push_back({{+0.50f, +0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag});

  // clang-format off
  std::vector<unsigned> indices = {
    0, 3, 1, 0, 3, 2,
    4, 7, 5, 4, 7, 6,
    0, 5, 1, 0, 5, 4,
    2, 7, 3, 2, 7, 6,
    1, 7, 5, 1, 7, 3,
    0, 6, 4, 0, 6, 2
  };
  // clang-format on

  IndexData idata = {Core::PrimitiveTopology::TRIANGLE_LIST, indices};

  mesh = Comp::CreateYukiMesh(vdata, idata, L"MeshTest");
  // TEST
}

void YukiGfxControl::Render()
{
  camera->Update();

  // Clear screen;
  glBindFramebuffer(GL_FRAMEBUFFER, 0); // Use Default FrameBuffer
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.00f, 0.00f, 0.00f, 1.00f);           // Set clear color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear frame buffer

  // TEST
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  mesh->RenderMesh(glm::identity<glm::mat4>(), camera->GetCameraViewMatrix(), camera->GetCameraProjectionMatrix());
  mesh->RenderMesh(
      glm::scale(glm::translate(glm::identity<glm::mat4>(), glm::vec3(3.02f, 3.02f, 3.02f)), glm::vec3(0.10f, 0.10f, 0.10f)),
      camera->GetCameraViewMatrix(), camera->GetCameraProjectionMatrix());
  // TEST
}

void YukiGfxControl::Destroy()
{

  // TEST
  mesh->Destroy();
  // TEST

  Comp::ReleaseMeshShader();
}

SharedPtr<IYukiGfxControl> CreateGraphicsController()
{
  return {(IYukiGfxControl*) new YukiGfxControl, std::default_delete<IYukiGfxControl>()};
}

} // namespace Yuki::Core