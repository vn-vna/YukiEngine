#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiComp/YukiMesh.hpp"

#include "PYukiObject.hpp"

#define YUKI_MAX_TEXTURE 128

namespace Yuki::Comp
{

using Core::YukiObject;
using Core::IYukiOGLElementBuffer;
using Core::IYukiOGLVertexArray;
using Core::IYukiOGLVertexBuffer;
using Core::IYukiOGLVertexBuffer;
using Core::IYukiOGLShaderProgram;
using Core::IYukiOGLTexture;
using Core::VertexFormat;
using Core::IndexData;
using Core::PrimitiveTopology;

class YukiMeshMaterial final : virtual public IYukiMeshMaterial,
                               virtual public YukiObject
{
protected:
  float m_nSpecularStrength;
  float m_nAmbientStrength;

public:
  YukiMeshMaterial(float specular, float ambient);
  ~YukiMeshMaterial() override;

  float GetSpecularStrength() override;
  float GetAmbientStrength() override;

  void SetSpecularStrength(float strength) override;
  void SetAmbientStrength(float strength) override;
};

class YukiMesh : virtual public IYukiMesh,
                 virtual public Core::YukiObject
{
protected:
  SharedPtr<IYukiOGLElementBuffer> m_pElementBuffer;
  SharedPtr<IYukiOGLVertexBuffer>  m_pVertexBuffer;
  SharedPtr<IYukiOGLVertexArray>   m_pVertexArray;
  SharedPtr<IYukiOGLShaderProgram> m_pShaderProgram;
  SharedPtr<IYukiOGLTexture>       m_pTexture;
  SharedPtr<IYukiMeshMaterial>     m_pMaterial;
  Vector<VertexFormat>             m_aVertexFormat;
  IndexData                        m_tIndexFormat;
  Mat4F                            m_tMeshMatrix;
  Mat4F                            m_tReNormalMatrix;
  String                           m_Name;

public:
  YukiMesh(
      Vector<VertexFormat>&        vertices,
      IndexData&                   indices,
      SharedPtr<IYukiOGLTexture>&  texture,
      SharedPtr<IYukiMeshMaterial> material,
      const String&                name);
  virtual ~YukiMesh();

  SharedPtr<IYukiOGLTexture>       GetMeshTexture() const override;
  SharedPtr<IYukiOGLElementBuffer> GetElementBuffer() const override;
  SharedPtr<IYukiOGLVertexBuffer>  GetVertexBuffer() const override;
  SharedPtr<IYukiOGLShaderProgram> GetShaderProgram() const override;
  SharedPtr<IYukiOGLVertexArray>   GetVertexArray() const override;
  SharedPtr<IYukiMeshMaterial>     GetMaterial() const override;
  const PrimitiveTopology&         GetTopology() const override;
  const String&                    GetName() const override;
  const Mat4F&                     GetMeshMatrix() const override;
  const Vector<VertexFormat>&      GetVertexData() const override;
  const IndexData&                 GetIndexData() const override;
  TransformationInfo               GetTransformationInfo() const override;

  void Create() override;
  void Destroy() override;

  void SetMaterial(SharedPtr<IYukiMeshMaterial> material) override;
  void SetMeshMatrix(const Mat4F& matrix) override;
  void SetTranslation(const Vec3F& position) override;
  void SetRotation(const Vec3F& axis, float rotationAngle) override;
  void SetScale(const Vec3F& scaleVector) override;
  void TranslateMesh(const Vec3F& direction) override;
  void RotateMesh(const Vec3F& axis, float rotationAngle) override;
  void ScaleMesh(const Vec3F& scaleVector) override;

  void RenderMesh(SharedPtr<IYukiCamera> camera) const override;
};

} // namespace Yuki::Comp