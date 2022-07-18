#include "YukiComp/Layer.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/Headers.hpp"
#include "YukiCore/Application.hpp"
#include "YukiCore/Input.hpp"
#include "YukiDebug/Errors.hpp"
#include "YukiComp/Mesh.hpp"
#include "YukiComp/Camera.hpp"
#include "YukiComp/Model.hpp"
#include "YukiUtil/Images.hpp"

#include "Private/PGraphicsControl.hpp"

#include <fmt/format.h>

namespace Yuki::Core
{

/// === TEST CODE

SharedPtr<Comp::ILayer> layer;

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
  GetYukiApp()->GetLogger()->PushDebugMessage(fmt::format(
      "-- Graphic device information: "
      "\n\tVendor: {} \n\tRenderer: "
      "{} \n\tShading language version: {}",
      GetGraphicsCardVendorName(), GetGraphicsCardRendererName(),
      GetShadingLanguageVersion()
  ));
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
  layer = Comp::CreateYukiLayer();
  layer->Require();
}

void YukiGfxControl::Awake()
{
  PrintGraphicProperties();
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
  layer->Release();
}

SharedPtr<IGraphics> CreateGraphicsController()
{
  return CreateInterfaceInstance<IGraphics, YukiGfxControl>();
}

} // namespace Yuki::Core
