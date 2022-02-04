#pragma once

#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Comp
{

class YUKIAPI IYukiMesh : public Core::IYukiObject
{
public:
  virtual SharedPtr<Core::IYukiOGLTexture>       GetMeshTexture()   = 0;
  virtual SharedPtr<Core::IYukiOGLElementBuffer> GetElementBuffer() = 0;
  virtual SharedPtr<Core::IYukiOGLVertexBuffer>  GetVertexBuffer()  = 0;
  virtual SharedPtr<Core::IYukiOGLShaderProgram> GetShaderProgram() = 0;
  virtual SharedPtr<Core::IYukiOGLVertexArray>   GetVertexArray()   = 0;
  virtual const Core::PrimitiveTopology&         GetTopology()      = 0;
  virtual const String&                          GetName()          = 0;

  virtual void RenderMesh(
      const glm::mat4& model,
      const glm::mat4& view,
      const glm::mat4& presentation) = 0;
};

SharedPtr<IYukiMesh> YUKIAPI CreateYukiMesh(
    std::vector<Core::VertexData>&    vertexData,
    Core::IndexData&                  indexData,
    SharedPtr<Core::IYukiOGLTexture>& texture,
    const String&                     meshName);

void YUKIAPI InitializeMeshShader();
void YUKIAPI ReleaseMeshShader();

} // namespace Yuki::Comp