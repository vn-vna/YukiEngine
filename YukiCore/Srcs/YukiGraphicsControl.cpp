#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiComp/YukiMesh.hpp"
#include "YukiComp/YukiCamera.hpp"
#include "YukiComp/YukiModel.hpp"
#include "YukiUtil/YukiImage.hpp"

#include "PYukiGraphicsControl.hpp"

/// TEST CODE

#include <glm/gtc/matrix_transform.hpp>

Yuki::SharedPtr<Yuki::Comp::IYukiCamera> camera;
Yuki::SharedPtr<Yuki::Comp::IYukiModel>  model;
Yuki::SharedPtr<Yuki::Comp::IYukiModel>  lightSphere;
Yuki::SharedPtr<Yuki::Comp::IYukiModel>  sphere;

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
}

void YukiGfxControl::Awake()
{

  // TEST

  camera = Comp::CreateYukiCamera();
  camera->SetFieldOfView(glm::radians(60.0f));

  model       = Comp::LoadModel("model.fbx");
  sphere      = Comp::LoadModel("sphere.fbx");
  lightSphere = Comp::LoadModel("light.fbx");

  model->Create();
  sphere->Create();
  lightSphere->Create();

  AutoType spheremesh = sphere->GetMesh("Sphere");
  if (spheremesh.get())
  {
    spheremesh->TranslateMesh({-2.30f, 2.30f, 3.00f});
  }

  AutoType lsphereMesh = lightSphere->GetMesh("Sphere");
  if (lsphereMesh.get())
  {
    lsphereMesh->TranslateMesh({-1.30f, 1.30f, 2.00f});
    lsphereMesh->ScaleMesh({0.02f, 0.02f, 0.02f});
  }

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

  {
    AutoType key1Stat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_1);
    if (key1Stat.state != KeyState::RELEASE)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    AutoType key2Stat = GetYukiApp()->GetInputController()->GetKeyStatus(KeyCode::KEY_2);
    if (key2Stat.state != KeyState::RELEASE)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
  }

  camera->Update();

  // TEST

  // TEST
  model->Render(camera);
  sphere->Render(camera);
  lightSphere->Render(camera);

  AutoType diamond = model->GetMesh("Diamond.001");
  if (diamond.get())
  {
    diamond->RotateMesh({0.0f, 0.0f, 1.0f}, glm::radians(1.0f));
  }

  AutoType spheremesh = sphere->GetMesh("Sphere");
  if (spheremesh.get())
  {
    spheremesh->RotateMesh({0.0f, 0.0f, 1.0f}, glm::radians(1.0f));
  }
  //  TEST
}

void YukiGfxControl::Destroy()
{
  // TEST
  if (lightSphere.get())
  {
    lightSphere->Destroy();
  }
  if (model.get())
  {
    model->Destroy();
  }
  if (sphere.get())
  {
    sphere->Destroy();
  }
  // TEST

  Comp::ReleaseMeshShader();
}

SharedPtr<IYukiGfxControl> CreateGraphicsController()
{
  return CreateInterfaceInstance<IYukiGfxControl, YukiGfxControl>();
}

} // namespace Yuki::Core