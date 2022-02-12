#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiComp/YukiMesh.hpp"

#define YUKI_MAX_TEXTURE 128

namespace Yuki::Comp
{

class YukiMeshMaterial : public IYukiMeshMaterial
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

class YukiMesh : public IYukiMesh
{
protected:
  SharedPtr<Core::IYukiOGLElementBuffer> m_pElementBuffer;
  SharedPtr<Core::IYukiOGLVertexBuffer>  m_pVertexBuffer;
  SharedPtr<Core::IYukiOGLVertexArray>   m_pVertexArray;
  SharedPtr<Core::IYukiOGLShaderProgram> m_pShaderProgram;
  SharedPtr<Core::IYukiOGLTexture>       m_pTexture;
  SharedPtr<IYukiMeshMaterial>           m_pMaterial;
  Core::PrimitiveTopology                m_eTopology;
  String                                 m_Name;

public:
  YukiMesh(const Core::PrimitiveTopology& topology, SharedPtr<Core::IYukiOGLTexture>& texture, const String& name);
  virtual ~YukiMesh();

  SharedPtr<Core::IYukiOGLTexture>       GetMeshTexture() override;
  SharedPtr<Core::IYukiOGLElementBuffer> GetElementBuffer() override;
  SharedPtr<Core::IYukiOGLVertexBuffer>  GetVertexBuffer() override;
  SharedPtr<Core::IYukiOGLShaderProgram> GetShaderProgram() override;
  SharedPtr<Core::IYukiOGLVertexArray>   GetVertexArray() override;
  SharedPtr<IYukiMeshMaterial>           GetMaterial() override;
  const Core::PrimitiveTopology&         GetTopology() override;
  const String&                          GetName() override;
  void                                   Create() override;
  void                                   Destroy() override;

  void SetMaterial(SharedPtr<IYukiMeshMaterial> material) override;

  void RenderMesh(const glm::mat4& model, SharedPtr<IYukiCamera> camera) override;
};

} // namespace Yuki::Comp