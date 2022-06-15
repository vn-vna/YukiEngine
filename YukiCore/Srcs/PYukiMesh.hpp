/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiComp/YukiMesh.hpp"
#include "YukiUtil/YukiImage.hpp"

#include "PYukiObject.hpp"

#define YUKI_MAX_TEXTURE 128

namespace Yuki::Comp
{

using Core::IYukiOGLElementBuffer;
using Core::IYukiOGLShaderProgram;
using Core::IYukiOGLTexture;
using Core::IYukiOGLVertexArray;
using Core::IYukiOGLVertexBuffer;
using Core::PrimitiveTopology;
using Core::YukiSharedObject;
using Utils::YukiImage;

class YukiMeshMaterial final : virtual public IYukiMeshMaterial,
                               virtual public YukiSharedObject
{
public:
  YukiMeshMaterial(SharedPtr<YukiImage> ambientMap,
                   SharedPtr<YukiImage> specularMap,
                   SharedPtr<YukiImage> diffuseMap);
  ~YukiMeshMaterial() override;

  SharedPtr<IYukiOGLTexture> GetSpecularMap() override;
  SharedPtr<IYukiOGLTexture> GetAmbientMap() override;
  SharedPtr<IYukiOGLTexture> GetDiffuseMap() override;

  void SetSpecularMap(SharedPtr<IYukiOGLTexture> specmap) override;
  void SetAmbientMap(SharedPtr<IYukiOGLTexture> ambmap) override;
  void SetDiffuseMap(SharedPtr<IYukiOGLTexture> diffmap) override;

  void Create() override;
  void Destroy() override;

private:
  SharedPtr<IYukiOGLTexture> m_pSpecMap;
  SharedPtr<IYukiOGLTexture> m_pAmbientMap;
  SharedPtr<IYukiOGLTexture> m_pDiffMap;

  SharedPtr<YukiImage> m_pSpecMapImg;
  SharedPtr<YukiImage> m_pAmbientMapImg;
  SharedPtr<YukiImage> m_pDiffMapImg;
};

class YukiMesh : virtual public IYukiMesh,
                 virtual public YukiSharedObject
{
public:
  YukiMesh(Vector<MeshVertexFormat>& vertices, MeshIndexData& indices,
           SharedPtr<IYukiOGLTexture>&  texture,
           SharedPtr<IYukiMeshMaterial> material, const String& name);
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
  const Vector<MeshVertexFormat>&  GetVertexData() const override;
  const MeshIndexData&             GetIndexData() const override;
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

private:
  SharedPtr<IYukiOGLElementBuffer> m_pElementBuffer;
  SharedPtr<IYukiOGLVertexBuffer>  m_pVertexBuffer;
  SharedPtr<IYukiOGLVertexArray>   m_pVertexArray;
  SharedPtr<IYukiOGLShaderProgram> m_pShaderProgram;
  SharedPtr<IYukiOGLTexture>       m_pTexture;
  SharedPtr<IYukiMeshMaterial>     m_pMaterial;
  Vector<MeshVertexFormat>         m_aVertexFormat;
  MeshIndexData                    m_tIndexFormat;
  Mat4F                            m_tMeshMatrix;
  Mat4F                            m_tReNormalMatrix;
  String                           m_Name;
};

} // namespace Yuki::Comp
