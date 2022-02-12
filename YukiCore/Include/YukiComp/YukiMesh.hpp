#pragma once

#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Comp
{

class YUKIAPI IYukiMeshMaterial
{
public:
  virtual float GetSpecularStrength() = 0;
  virtual float GetAmbientStrength()  = 0;

  virtual void SetSpecularStrength(float strength) = 0;
  virtual void SetAmbientStrength(float strength)  = 0;
};

class YUKIAPI IYukiMesh : public Core::IYukiObject
{
public:
  virtual SharedPtr<Core::IYukiOGLTexture>       GetMeshTexture()   = 0;
  virtual SharedPtr<Core::IYukiOGLElementBuffer> GetElementBuffer() = 0;
  virtual SharedPtr<Core::IYukiOGLVertexBuffer>  GetVertexBuffer()  = 0;
  virtual SharedPtr<Core::IYukiOGLShaderProgram> GetShaderProgram() = 0;
  virtual SharedPtr<Core::IYukiOGLVertexArray>   GetVertexArray()   = 0;
  virtual SharedPtr<IYukiMeshMaterial>           GetMaterial()      = 0;
  virtual const Core::PrimitiveTopology&         GetTopology()      = 0;
  virtual const String&                          GetName()          = 0;

  virtual void SetMaterial(SharedPtr<IYukiMeshMaterial> material) = 0;

  virtual void RenderMesh(const glm::mat4& model, SharedPtr<IYukiCamera> camera) = 0;
};

SharedPtr<IYukiMesh> YUKIAPI CreateYukiMesh(
    std::vector<Core::VertexData>&    vertexData,
    Core::IndexData&                  indexData,
    SharedPtr<Core::IYukiOGLTexture>& texture,
    SharedPtr<IYukiMeshMaterial>      material,
    const String&                     meshName);

SharedPtr<IYukiMeshMaterial> YUKIAPI CreateMaterial(float specular, float ambient);

void YUKIAPI InitializeMeshShader();
void YUKIAPI ReleaseMeshShader();

} // namespace Yuki::Comp