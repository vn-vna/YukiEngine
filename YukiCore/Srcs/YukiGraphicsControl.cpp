#include "YukiComp/YukiLayer.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiComp/YukiMesh.hpp"
#include "YukiComp/YukiCamera.hpp"
#include "YukiComp/YukiModel.hpp"
#include "YukiUtil/YukiImage.hpp"

#include "PYukiGraphicsControl.hpp"

#include <fmt/format.h>

namespace Yuki::Core
{

using Comp::ReleaseMeshShader;
using Comp::InitializeMeshShader;

/// === TEST CODE

SharedPtr<Comp::IYukiLayer> layer;

/// === TEST CODE

String GetGraphicsCardVendorName()
{
  const GLubyte* vendor = glGetString(GL_VENDOR);
  return (const char*) vendor;
}

String GetGraphicsCardRendererName()
{
  const GLubyte* renderer = glGetString(GL_RENDERER);
  return (const char*) renderer;
}

String GetShadingLanguageVersion()
{
  const GLubyte* lvs = glGetString(GL_SHADING_LANGUAGE_VERSION);
  return (const char*) lvs;
}

void PrintGraphicProperties()
{
  GetYukiApp()->GetLogger()->PushDebugMessage(
      fmt::format("-- Graphic device information: \n\tVendor: {} \n\tRenderer: {} \n\tShading language version: {}",
          GetGraphicsCardVendorName(), GetGraphicsCardRendererName(), GetShadingLanguageVersion()));
}

YukiGfxControl::YukiGfxControl() = default;

YukiGfxControl::~YukiGfxControl() = default;

void YukiGfxControl::EnableAttribute(OpenGLAttribute attrib, bool cond)
{
  if (cond)
  {
    glEnable((GLenum) attrib);
  }
}

void YukiGfxControl::DisableAttribute(OpenGLAttribute attrib, bool cond)
{
  if (cond)
  {
    glDisable((GLenum) attrib);
  }
}

void YukiGfxControl::SetAttributeStatus(OpenGLAttribute attrib, bool status)
{
  if (status)
  {
    glEnable((GLenum) attrib);
  }
  else
  {
    glDisable((GLenum) attrib);
  }
}


void YukiGfxControl::Create()
{
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
  {
    THROW_YUKI_ERROR(GladLoadGLLoaderError);
  }
  // Default shader for mesh rendering
  InitializeMeshShader();

  layer = Comp::CreateYukiLayer();
  layer->Create();
}

void YukiGfxControl::Awake() { PrintGraphicProperties(); }

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
  layer->Destroy();
  // Release the default shader for mesh rendering
  ReleaseMeshShader();
}

SharedPtr<IYukiGfxControl> CreateGraphicsController()
{
  return CreateInterfaceInstance<IYukiGfxControl, YukiGfxControl>();
}

} // namespace Yuki::Core
