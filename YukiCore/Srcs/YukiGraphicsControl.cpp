#include "YukiCore/YukiPCH.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiComp/YukiMesh.hpp"
#include "YukiComp/YukiCamera.hpp"
#include "YukiUtil/YukiImage.hpp"

#include "PYukiGraphicsControl.hpp"


/// TEST CODE

#include <glm/gtc/matrix_transform.hpp>

Yuki::SharedPtr<Yuki::Comp::IYukiMesh>       mesh;
Yuki::SharedPtr<Yuki::Comp::IYukiMesh>       lightCube;
Yuki::SharedPtr<Yuki::Comp::IYukiCamera>     camera;
Yuki::SharedPtr<Yuki::Core::IYukiOGLTexture> tex;

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

          case GLFW_KEY_U:
            camera->CameraRotateDirection(camera->GetCameraVerticalAxis(), glm::radians(90.0f));
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

  tex = Utils::YukiImage("tex.png").Create2DTexture();

  unsigned vertexFlag  = (unsigned) VertexFlag::ENABLE_LIGHTNING | (unsigned) VertexFlag::ENABLE_EXPLICIT_VERTEX_COLOR | (unsigned) VertexFlag::ENABLE_TEXTURE;
  unsigned vertexFlag2 = (unsigned) VertexFlag::ENABLE_EXPLICIT_VERTEX_COLOR;

  std::vector<VertexData> vdata;
  vdata.push_back({{-0.50f, -0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {0.00f, 0.00f}, vertexFlag});
  vdata.push_back({{-0.50f, +0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {0.00f, 1.00f}, vertexFlag});
  vdata.push_back({{+0.50f, -0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {1.00f, 0.00f}, vertexFlag});
  vdata.push_back({{+0.50f, +0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {1.00f, 1.00f}, vertexFlag});
  vdata.push_back({{-0.50f, -0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {0.00f, 0.00f}, vertexFlag});
  vdata.push_back({{-0.50f, +0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {0.00f, 1.00f}, vertexFlag});
  vdata.push_back({{+0.50f, -0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {1.00f, 0.00f}, vertexFlag});
  vdata.push_back({{+0.50f, +0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {1.00f, 1.00f}, vertexFlag});

  std::vector<VertexData> vdata2;
  vdata2.push_back({{-0.50f, -0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag2});
  vdata2.push_back({{-0.50f, +0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag2});
  vdata2.push_back({{+0.50f, -0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag2});
  vdata2.push_back({{+0.50f, +0.50f, +0.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag2});
  vdata2.push_back({{-0.50f, -0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag2});
  vdata2.push_back({{-0.50f, +0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag2});
  vdata2.push_back({{+0.50f, -0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag2});
  vdata2.push_back({{+0.50f, +0.50f, +1.00f}, {1.00f, 1.00f, 1.00f, 1.00f}, {}, vertexFlag2});

  // clang-format off
  std::vector<unsigned> indices = {
    0, 2, 3, 0, 3, 1,
    4, 7, 6, 4, 5, 7,
    1, 3, 7, 1, 7, 5,
    0, 4, 6, 0, 6, 2,
    0, 1, 5, 0, 5, 4,
    2, 6, 7, 2, 7, 3
  };
  // clang-format on

  IndexData idata = {Core::PrimitiveTopology::TRIANGLE_LIST, indices};

  mesh      = Comp::CreateYukiMesh(vdata, idata, tex, L"MeshTest");
  lightCube = Comp::CreateYukiMesh(vdata2, idata, tex, L"LightCube");

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
  mesh->RenderMesh(glm::identity<glm::mat4>(), camera);

  lightCube->RenderMesh(
      glm::scale(glm::translate(glm::identity<glm::mat4>(), glm::vec3{1.30f, 1.30f, 2.00f}), glm::vec3{0.05f, 0.05f, 0.05f}),
      camera);
  // TEST
}

void YukiGfxControl::Destroy()
{

  // TEST
  tex->Destroy();
  mesh->Destroy();
  lightCube->Destroy();
  // TEST

  Comp::ReleaseMeshShader();
}

SharedPtr<IYukiGfxControl> CreateGraphicsController()
{
  return {(IYukiGfxControl*) new YukiGfxControl, std::default_delete<IYukiGfxControl>()};
}

} // namespace Yuki::Core