#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
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

  tex = Utils::YukiImage("tex.png").Create2DTexture();



  std::vector<VertexData> cube;
  cube.push_back({{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {}});
  cube.push_back({{+0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {}});
  cube.push_back({{+0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {}});
  cube.push_back({{+0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {}});
  cube.push_back({{-0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {}});
  cube.push_back({{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {}});

  cube.push_back({{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, +1.0f}, {}});
  cube.push_back({{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, +1.0f}, {}});
  cube.push_back({{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, +1.0f}, {}});
  cube.push_back({{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, +1.0f}, {}});
  cube.push_back({{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, +1.0f}, {}});
  cube.push_back({{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, +1.0f}, {}});

  cube.push_back({{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {}});
  cube.push_back({{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {}});
  cube.push_back({{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {}});
  cube.push_back({{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {}});
  cube.push_back({{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {}});
  cube.push_back({{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {}});

  cube.push_back({{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {}});
  cube.push_back({{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {}});
  cube.push_back({{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {}});
  cube.push_back({{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {}});
  cube.push_back({{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {}});
  cube.push_back({{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {}});

  cube.push_back({{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {}});
  cube.push_back({{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {}});
  cube.push_back({{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {}});
  cube.push_back({{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {}});
  cube.push_back({{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {}});
  cube.push_back({{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {}});

  cube.push_back({{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {}});
  cube.push_back({{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {}});
  cube.push_back({{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {}});
  cube.push_back({{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {}});
  cube.push_back({{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {}});
  cube.push_back({{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {}});

  std::vector<VertexData> light_cube;
  light_cube.push_back({{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, +1.0f}, {}});
  light_cube.push_back({{+0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, +1.0f}, {}});
  light_cube.push_back({{+0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, +1.0f}, {}});
  light_cube.push_back({{+0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, +1.0f}, {}});
  light_cube.push_back({{-0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, +1.0f}, {}});
  light_cube.push_back({{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, +1.0f}, {}});

  light_cube.push_back({{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f, -1.0f}, {}});
  light_cube.push_back({{+0.5f, -0.5f, +0.5f}, {0.0f, 0.0f, -1.0f}, {}});
  light_cube.push_back({{+0.5f, +0.5f, +0.5f}, {0.0f, 0.0f, -1.0f}, {}});
  light_cube.push_back({{+0.5f, +0.5f, +0.5f}, {0.0f, 0.0f, -1.0f}, {}});
  light_cube.push_back({{-0.5f, +0.5f, +0.5f}, {0.0f, 0.0f, -1.0f}, {}});
  light_cube.push_back({{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f, -1.0f}, {}});

  light_cube.push_back({{-0.5f, +0.5f, +0.5f}, {+1.0f, 0.0f, 0.0f}, {}});
  light_cube.push_back({{-0.5f, +0.5f, -0.5f}, {+1.0f, 0.0f, 0.0f}, {}});
  light_cube.push_back({{-0.5f, -0.5f, -0.5f}, {+1.0f, 0.0f, 0.0f}, {}});
  light_cube.push_back({{-0.5f, -0.5f, -0.5f}, {+1.0f, 0.0f, 0.0f}, {}});
  light_cube.push_back({{-0.5f, -0.5f, +0.5f}, {+1.0f, 0.0f, 0.0f}, {}});
  light_cube.push_back({{-0.5f, +0.5f, +0.5f}, {+1.0f, 0.0f, 0.0f}, {}});

  light_cube.push_back({{+0.5f, +0.5f, +0.5f}, {-1.0f, 0.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, +0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, -0.5f, +0.5f}, {-1.0f, 0.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, +0.5f, +0.5f}, {-1.0f, 0.0f, 0.0f}, {}});

  light_cube.push_back({{-0.5f, -0.5f, -0.5f}, {0.0f, +1.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, -0.5f, -0.5f}, {0.0f, +1.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, -0.5f, +0.5f}, {0.0f, +1.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, -0.5f, +0.5f}, {0.0f, +1.0f, 0.0f}, {}});
  light_cube.push_back({{-0.5f, -0.5f, +0.5f}, {0.0f, +1.0f, 0.0f}, {}});
  light_cube.push_back({{-0.5f, -0.5f, -0.5f}, {0.0f, +1.0f, 0.0f}, {}});

  light_cube.push_back({{-0.5f, +0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, +0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, +0.5f, +0.5f}, {0.0f, -1.0f, 0.0f}, {}});
  light_cube.push_back({{+0.5f, +0.5f, +0.5f}, {0.0f, -1.0f, 0.0f}, {}});
  light_cube.push_back({{-0.5f, +0.5f, +0.5f}, {0.0f, -1.0f, 0.0f}, {}});
  light_cube.push_back({{-0.5f, +0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {}});

  // clang-format off
  std::vector<unsigned> indices = {
     0,  1,  2,  3,  4,  5,
     6,  7,  8,  9, 10, 11,
    12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35
  };
  // clang-format on

  IndexData idata = {Core::PrimitiveTopology::TRIANGLE_LIST, indices};

  mesh      = Comp::CreateYukiMesh(cube, idata, tex, L"MeshTest");
  lightCube = Comp::CreateYukiMesh(light_cube, idata, tex, L"LightCube");

  // TEST
}

void YukiGfxControl::Render()
{
  // Clear screen;
  glBindFramebuffer(GL_FRAMEBUFFER, 0); // Use Default FrameBuffer
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.00f, 0.00f, 0.00f, 1.00f);           // Set clear color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear frame buffer

  // TEST
  {
    AutoType keyAStat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_A);
    if (keyAStat.state != KeyState::RELEASE)
    {
      camera->SetCameraPosition(camera->GetCameraPosition() - camera->GetCameraHorizontalAxis() * 0.03f);
    }
    AutoType keyDStat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_D);
    if (keyDStat.state != KeyState::RELEASE)
    {
      camera->SetCameraPosition(camera->GetCameraPosition() + camera->GetCameraHorizontalAxis() * 0.03f);
    }
    AutoType keyWStat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_W);
    if (keyWStat.state != KeyState::RELEASE)
    {
      camera->SetCameraPosition(camera->GetCameraPosition() + camera->GetCameraVerticalAxis() * 0.03f);
    }
    AutoType keySStat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_S);
    if (keySStat.state != KeyState::RELEASE)
    {
      camera->SetCameraPosition(camera->GetCameraPosition() - camera->GetCameraVerticalAxis() * 0.03f);
    }
  }
  {
    AutoType keyUpStat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_UP);
    if (keyUpStat.state != KeyState::RELEASE)
    {
      camera->CameraRotateDirection(camera->GetCameraHorizontalAxis(), glm::radians(30.00f) * 0.03f);
    }
    AutoType keyDownStat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_DOWN);
    if (keyDownStat.state != KeyState::RELEASE)
    {
      camera->CameraRotateDirection(camera->GetCameraHorizontalAxis(), glm::radians(-30.00f) * 0.03f);
    }
    AutoType keyLeftStat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_LEFT);
    if (keyLeftStat.state != KeyState::RELEASE)
    {
      camera->CameraRotateDirection(camera->GetCameraTopAxis(), glm::radians(30.00f) * 0.03f);
    }
    AutoType keyRightStat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_RIGHT);
    if (keyRightStat.state != KeyState::RELEASE)
    {
      camera->CameraRotateDirection(camera->GetCameraTopAxis(), glm::radians(-30.00f) * 0.03f);
    }
  }
  {
    AutoType keyQStat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_Q);
    if (keyQStat.state != KeyState::RELEASE)
    {
      camera->SetCameraPosition(camera->GetCameraPosition() + camera->GetCameraTopAxis() * 0.03f);
    }
    AutoType keyEStat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_E);
    if (keyEStat.state != KeyState::RELEASE)
    {
      camera->SetCameraPosition(camera->GetCameraPosition() - camera->GetCameraTopAxis() * 0.03f);
    }
  }

  camera->Update();

  // TEST

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