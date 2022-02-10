#pragma once

#include "YukiCore/YukiGraphics.hpp"
#include "YukiComp/YukiComponent.hpp"

namespace Yuki::Comp
{

SharedPtr<IYukiMesh> YUKIAPI CreateYukiMesh(
    std::vector<Core::VertexData>&    vertexData,
    Core::IndexData&                  indexData,
    SharedPtr<Core::IYukiOGLTexture>& texture,
    const String&                     meshName);

std::vector<SharedPtr<IYukiMesh>> YUKIAPI LoadMeshesFromFile(const AsciiString& fileName);

class YUKIAPI IYukiMesh : public IYukiComp
{
public:
  virtual SharedPtr<Core::IYukiOGLTexture>       GetMeshTexture()   = 0;
  virtual SharedPtr<Core::IYukiOGLElementBuffer> GetElementBuffer() = 0;
  virtual SharedPtr<Core::IYukiOGLVertexBuffer>  GetVertexBuffer()  = 0;
  virtual SharedPtr<Core::IYukiOGLShaderProgram> GetShaderProgram() = 0;
  virtual SharedPtr<Core::IYukiOGLVertexArray>   GetVertexArray()   = 0;
  virtual const Core::PrimitiveTopology&         GetTopology()      = 0;
  virtual const String&                          GetName()          = 0;

  virtual void RenderMesh(const glm::mat4& model, SharedPtr<IYukiCamera> camera) = 0;


  friend SharedPtr<IYukiMesh> CreateYukiMesh(
      std::vector<Core::VertexData>&    vertexData,
      Core::IndexData&                  indexData,
      SharedPtr<Core::IYukiOGLTexture>& texture,
      const String&                     meshName);

  friend std::vector<SharedPtr<IYukiMesh>> LoadMeshesFromFile(const AsciiString& fileName);
};

} // namespace Yuki::Comp
