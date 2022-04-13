#pragma once

#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiGraphics.hpp"

// glm
#include <glm/gtx/quaternion.hpp>

namespace Yuki::Comp
{

extern SharedPtr<Core::IYukiOGLTexture> NO_TEXTURE;

typedef struct YUKIAPI StTransformationInfo
{
  glm::vec3 scale;
  glm::quat rotation;
  glm::vec3 translation;
  glm::vec3 skew;
} TransformationInfo;

class YUKIAPI IYukiMeshMaterial
{
public:
  virtual float GetSpecularStrength() = 0;
  virtual float GetAmbientStrength()  = 0;

  virtual void SetSpecularStrength(float strength) = 0;
  virtual void SetAmbientStrength(float strength)  = 0;
};

class YUKIAPI IYukiMesh : virtual public Core::IYukiObject
{
public:
  virtual SharedPtr<Core::IYukiOGLTexture>       GetMeshTexture() const        = 0;
  virtual SharedPtr<Core::IYukiOGLElementBuffer> GetElementBuffer() const      = 0;
  virtual SharedPtr<Core::IYukiOGLVertexBuffer>  GetVertexBuffer() const       = 0;
  virtual SharedPtr<Core::IYukiOGLShaderProgram> GetShaderProgram() const      = 0;
  virtual SharedPtr<Core::IYukiOGLVertexArray>   GetVertexArray() const        = 0;
  virtual SharedPtr<IYukiMeshMaterial>           GetMaterial() const           = 0;
  virtual const Core::PrimitiveTopology&         GetTopology() const           = 0;
  virtual const String&                          GetName() const               = 0;
  virtual const glm::mat4&                       GetMeshMatrix() const         = 0;
  virtual const Vector<Core::VertexFormat>& GetVertexData() const         = 0;
  virtual const Core::IndexData&                 GetIndexData() const          = 0;
  virtual TransformationInfo                     GetTransformationInfo() const = 0;

  virtual void SetMaterial(SharedPtr<IYukiMeshMaterial> material)      = 0;
  virtual void SetMeshMatrix(const glm::mat4& matrix)                  = 0;
  virtual void SetTranslation(const glm::vec3& position)               = 0;
  virtual void SetRotation(const glm::vec3& axis, float rotationAngle) = 0;
  virtual void SetScale(const glm::vec3& scaleVector)                  = 0;
  virtual void TranslateMesh(const glm::vec3& direction)               = 0;
  virtual void RotateMesh(const glm::vec3& axis, float rotationAngle)  = 0;
  virtual void ScaleMesh(const glm::vec3& scaleVector)                 = 0;

  virtual void RenderMesh(SharedPtr<IYukiCamera> camera) const = 0;
};

SharedPtr<IYukiMesh> YUKIAPI CreateYukiMesh(
    Vector<Core::VertexData>&    vertexData,
    Core::IndexData&                  indexData,
    SharedPtr<Core::IYukiOGLTexture>& texture,
    SharedPtr<IYukiMeshMaterial>&     material,
    const String&                     meshName);

SharedPtr<IYukiMeshMaterial> YUKIAPI CreateMaterial(float specular, float ambient);

void YUKIAPI InitializeMeshShader();
void YUKIAPI ReleaseMeshShader();

} // namespace Yuki::Comp