#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiComp/YukiMesh.hpp"
#include "YukiComp/YukiCamera.hpp"
#include "YukiComp/YukiModel.hpp"
#include "YukiUtil/YukiImage.hpp"

#include "PYukiGraphicsControl.hpp"


namespace Yuki::Core
{

using Comp::ReleaseMeshShader;
using Comp::InitializeMeshShader;
using Debug::YukiGladLoadGLLoaderError;

YukiGfxControl::YukiGfxControl() = default;

YukiGfxControl::~YukiGfxControl() = default;

void YukiGfxControl::Create()
{
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
  {
    THROW_YUKI_ERROR(GladLoadGLLoaderError);
  }
  // Default shader for mesh rendering
  InitializeMeshShader();
}

void YukiGfxControl::Awake()
{
}

void YukiGfxControl::Render()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);               // Use Default FrameBuffer
  glEnable(GL_DEPTH_TEST);                            // Enable depth test
  glDepthFunc(GL_LESS);                               // Set depth func
  glClearColor(0.00f, 0.00f, 0.00f, 1.00f);           // Set clear color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear frame buffer

  AutoType currentScene = GetYukiApp()->GetCurrentScene();
  currentScene->Render();
}

void YukiGfxControl::Destroy()
{
  // Release the default shader for mesh rendering
  ReleaseMeshShader();
}

SharedPtr<IYukiGfxControl> CreateGraphicsController()
{
  return CreateInterfaceInstance<IYukiGfxControl, YukiGfxControl>();
}

} // namespace Yuki::Core