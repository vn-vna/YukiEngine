#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiComp/YukiMesh.hpp"

#define YUKI_MAX_TEXTURE 128

namespace Yuki::Comp
{

class YukiMesh : public virtual IYukiMesh
{
protected:
  SharedPtr<Core::IYukiOGLElementBuffer> m_pElementBuffer;
  SharedPtr<Core::IYukiOGLVertexBuffer>  m_pVertexBuffer;
  SharedPtr<Core::IYukiOGLVertexArray>   m_pVertexArray;
  SharedPtr<Core::IYukiOGLShaderProgram> m_pShaderProgram;
  SharedPtr<Core::IYukiOGLTexture>       m_pTexture;
  Core::PrimitiveTopology                m_eTopology;
  String                                 m_Name;
  int                                    m_nRequired;

public:
  YukiMesh(const Core::PrimitiveTopology& topology, SharedPtr<Core::IYukiOGLTexture>& texture, const String& name);
  virtual ~YukiMesh();

  ComponentType GetComponentType() override;

  SharedPtr<Core::IYukiOGLTexture>       GetMeshTexture() override;
  SharedPtr<Core::IYukiOGLElementBuffer> GetElementBuffer() override;
  SharedPtr<Core::IYukiOGLVertexBuffer>  GetVertexBuffer() override;
  SharedPtr<Core::IYukiOGLShaderProgram> GetShaderProgram() override;
  SharedPtr<Core::IYukiOGLVertexArray>   GetVertexArray() override;
  const Core::PrimitiveTopology&         GetTopology() override;
  const String&                          GetName() override;
  void                                   Create() override;
  void                                   Destroy() override;

  void RenderMesh(const glm::mat4& model, SharedPtr<IYukiCamera> camera) override;
};

} // namespace Yuki::Comp
