#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiComp/YukiMesh.hpp"

#include "PYukiObject.hpp"

#define YUKI_MAX_TEXTURE 128

namespace Yuki::Comp
{

class YukiMeshMaterial : virtual public IYukiMeshMaterial,
                         virtual public Core::YukiObject
{
protected:
  float m_nSpecularStrength;
  float m_nAmbientStrength;

public:
  YukiMeshMaterial(float specular, float ambient);
  virtual ~YukiMeshMaterial() = default;

  float GetSpecularStrength() override;
  float GetAmbientStrength() override;

  void SetSpecularStrength(float strength) override;
  void SetAmbientStrength(float strength) override;
};

class YukiMesh : virtual public IYukiMesh,
                 virtual public Core::YukiObject
{
protected:
  SharedPtr<Core::IYukiOGLElementBuffer> m_pElementBuffer;
  SharedPtr<Core::IYukiOGLVertexBuffer>  m_pVertexBuffer;
  SharedPtr<Core::IYukiOGLVertexArray>   m_pVertexArray;
  SharedPtr<Core::IYukiOGLShaderProgram> m_pShaderProgram;
  SharedPtr<Core::IYukiOGLTexture>       m_pTexture;
  SharedPtr<IYukiMeshMaterial>           m_pMaterial;
  Vector<Core::VertexFormat>             m_aVertexFormat;
  Core::IndexData                        m_tIndexFormat;
  glm::mat4                              m_tMeshMatrix;
  glm::mat4                              m_tReNormalMatrix;
  String                                 m_Name;

public:
  YukiMesh(
      Vector<Core::VertexFormat>&       vertices,
      Core::IndexData&                  indices,
      SharedPtr<Core::IYukiOGLTexture>& texture,
      SharedPtr<IYukiMeshMaterial>      material,
      const String&                     name);
  virtual ~YukiMesh();

  SharedPtr<Core::IYukiOGLTexture>       GetMeshTexture() const override;
  SharedPtr<Core::IYukiOGLElementBuffer> GetElementBuffer() const override;
  SharedPtr<Core::IYukiOGLVertexBuffer>  GetVertexBuffer() const override;
  SharedPtr<Core::IYukiOGLShaderProgram> GetShaderProgram() const override;
  SharedPtr<Core::IYukiOGLVertexArray>   GetVertexArray() const override;
  SharedPtr<IYukiMeshMaterial>           GetMaterial() const override;
  const Core::PrimitiveTopology&         GetTopology() const override;
  const String&                          GetName() const override;
  const glm::mat4&                       GetMeshMatrix() const override;
  const Vector<Core::VertexData>&        GetVertexData() const override;
  const Core::IndexData&                 GetIndexData() const override;
  TransformationInfo                     GetTransformationInfo() const override;

  void Create() override;
  void Destroy() override;

  void SetMaterial(SharedPtr<IYukiMeshMaterial> material) override;
  void SetMeshMatrix(const glm::mat4& matrix) override;
  void SetTranslation(const glm::vec3& position) override;
  void SetRotation(const glm::vec3& axis, float rotationAngle) override;
  void SetScale(const glm::vec3& scaleVector) override;
  void TranslateMesh(const glm::vec3& direction) override;
  void RotateMesh(const glm::vec3& axis, float rotationAngle) override;
  void ScaleMesh(const glm::vec3& scaleVector) override;

  void RenderMesh(SharedPtr<IYukiCamera> camera) const override;
};

} // namespace Yuki::Comp