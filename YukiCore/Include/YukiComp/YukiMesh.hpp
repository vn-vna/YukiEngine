#pragma once

#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiGraphics.hpp"

// glm
#include <glm/gtx/quaternion.hpp>

namespace Yuki::Comp
{

using Core::IYukiOGLTexture;
using Core::IYukiOGLElementBuffer;
using Core::IYukiOGLVertexBuffer;
using Core::IYukiOGLShaderProgram;
using Core::IYukiOGLVertexArray;
using Core::PrimitiveTopology;
using Core::IndexData;
using Core::VertexFormat;

extern SharedPtr<IYukiOGLTexture> NO_TEXTURE;

typedef struct YUKIAPI StTransformationInfo
{
  Vec3F       scale;
  QuaternionF rotation;
  Vec3F       translation;
  Vec3F       skew;
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
  virtual SharedPtr<IYukiOGLTexture>       GetMeshTexture() const        = 0;
  virtual SharedPtr<IYukiOGLElementBuffer> GetElementBuffer() const      = 0;
  virtual SharedPtr<IYukiOGLVertexBuffer>  GetVertexBuffer() const       = 0;
  virtual SharedPtr<IYukiOGLShaderProgram> GetShaderProgram() const      = 0;
  virtual SharedPtr<IYukiOGLVertexArray>   GetVertexArray() const        = 0;
  virtual SharedPtr<IYukiMeshMaterial>     GetMaterial() const           = 0;
  virtual const PrimitiveTopology&         GetTopology() const           = 0;
  virtual const String&                    GetName() const               = 0;
  virtual const Mat4F&                     GetMeshMatrix() const         = 0;
  virtual const Vector<VertexFormat>&      GetVertexData() const         = 0;
  virtual const IndexData&                 GetIndexData() const          = 0;
  virtual TransformationInfo               GetTransformationInfo() const = 0;

  virtual void SetMaterial(SharedPtr<IYukiMeshMaterial> material)  = 0;
  virtual void SetMeshMatrix(const Mat4F& matrix)                  = 0;
  virtual void SetTranslation(const Vec3F& position)               = 0;
  virtual void SetRotation(const Vec3F& axis, float rotationAngle) = 0;
  virtual void SetScale(const Vec3F& scaleVector)                  = 0;
  virtual void TranslateMesh(const Vec3F& direction)               = 0;
  virtual void RotateMesh(const Vec3F& axis, float rotationAngle)  = 0;
  virtual void ScaleMesh(const Vec3F& scaleVector)                 = 0;

  virtual void RenderMesh(SharedPtr<IYukiCamera> camera) const = 0;
};

SharedPtr<IYukiMesh> YUKIAPI CreateYukiMesh(
    Vector<VertexFormat>&            vertexData,
    IndexData&                       indexData,
    SharedPtr<Core::IYukiOGLTexture> texture,
    SharedPtr<IYukiMeshMaterial>     material,
    const String&                    meshName);

SharedPtr<IYukiMeshMaterial> YUKIAPI CreateMaterial(float specular, float ambient);

void YUKIAPI InitializeMeshShader();
void YUKIAPI ReleaseMeshShader();

} // namespace Yuki::Comp