/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiComp/Mesh.hpp"
#include "YukiCore/Objects.hpp"
#include "YukiUtil/Images.hpp"

#include "PObjects.hpp"

#define YUKI_MAX_TEXTURE 128

namespace Yuki::Comp
{

using Core::IOGLTexture;
using Core::PrimitiveTopology;
using Core::YukiSharedObject;
using Utils::Images;

class YukiMeshMaterial final : virtual public IMaterial,
                               virtual public YukiSharedObject
{
public:
  YukiMeshMaterial(SharedPtr<Images> ambientMap, SharedPtr<Images> specularMap,
                   SharedPtr<Images> diffuseMap);
  ~YukiMeshMaterial() override;

  SharedPtr<IOGLTexture> GetSpecularMap() override;
  SharedPtr<IOGLTexture> GetAmbientMap() override;
  SharedPtr<IOGLTexture> GetDiffuseMap() override;

  void SetSpecularMap(SharedPtr<IOGLTexture> specmap) override;
  void SetAmbientMap(SharedPtr<IOGLTexture> ambmap) override;
  void SetDiffuseMap(SharedPtr<IOGLTexture> diffmap) override;

  void Create() override;
  void Destroy() override;

private:
  SharedPtr<IOGLTexture> m_pSpecMap;
  SharedPtr<IOGLTexture> m_pAmbientMap;
  SharedPtr<IOGLTexture> m_pDiffMap;

  SharedPtr<Images> m_pSpecMapImg;
  SharedPtr<Images> m_pAmbientMapImg;
  SharedPtr<Images> m_pDiffMapImg;
};

class YukiMesh : virtual public IMesh,
                 virtual public YukiSharedObject
{
public:
  YukiMesh(Vector<MeshVertexFormat>& vertices, MeshIndexData& indices, SPIOGLTexture& texture,
           SPIMaterial material, const String& name);
  virtual ~YukiMesh();

  SPIOGLTexture                   GetMeshTexture() const override;
  SPIOGLElementBuffer             GetElementBuffer() const override;
  SPIOGLVertexBuffer              GetVertexBuffer() const override;
  SPIOGLShaderProgram             GetShaderProgram() const override;
  SPIOGLVertexArray               GetVertexArray() const override;
  SPIMaterial                     GetMaterial() const override;
  const PrimitiveTopology&        GetTopology() const override;
  const String&                   GetName() const override;
  const Mat4F&                    GetMeshMatrix() const override;
  const Vector<MeshVertexFormat>& GetVertexData() const override;
  const MeshIndexData&            GetIndexData() const override;
  TransformationInfo              GetTransformationInfo() const override;

  void Create() override;
  void Destroy() override;

  void SetMaterial(SharedPtr<IMaterial> material) override;
  void SetMeshMatrix(const Mat4F& matrix) override;
  void SetTranslation(const Vec3F& position) override;
  void SetRotation(const Vec3F& axis, float rotationAngle) override;
  void SetScale(const Vec3F& scaleVector) override;
  void TranslateMesh(const Vec3F& direction) override;
  void RotateMesh(const Vec3F& axis, float rotationAngle) override;
  void ScaleMesh(const Vec3F& scaleVector) override;

  void RenderMesh(SharedPtr<ICamera> camera) const override;

private:
  SPIOGLElementBuffer      m_pElementBuffer;
  SPIOGLVertexBuffer       m_pVertexBuffer;
  SPIOGLVertexArray        m_pVertexArray;
  SPIOGLShaderProgram      m_pShaderProgram;
  SPIOGLTexture            m_pTexture;
  SPIMaterial              m_pMaterial;
  Vector<MeshVertexFormat> m_aVertexFormat;
  MeshIndexData            m_tIndexFormat;
  Mat4F                    m_tMeshMatrix;
  Mat4F                    m_tReNormalMatrix;
  String                   m_Name;
};

} // namespace Yuki::Comp
