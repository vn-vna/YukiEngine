#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiComp/YukiMesh.hpp"

namespace Yuki::Comp
{

class YukiMesh : public IYukiMesh
{
protected:
  SharedPtr<Core::IYukiOGLElementBuffer> m_pElementBuffer;
  SharedPtr<Core::IYukiOGLVertexBuffer>  m_pVertexBuffer;
  SharedPtr<Core::IYukiOGLVertexArray>   m_pVertexArray;
  SharedPtr<Core::IYukiOGLShaderProgram> m_pShaderProgram;
  Core::PrimitiveTopology                m_eTopology;
  String                                 m_Name;

public:
  YukiMesh(const Core::PrimitiveTopology& topology, const String& name);
  virtual ~YukiMesh();

  SharedPtr<Core::IYukiOGLElementBuffer> GetElementBuffer() override;
  SharedPtr<Core::IYukiOGLVertexBuffer>  GetVertexBuffer() override;
  SharedPtr<Core::IYukiOGLShaderProgram> GetShaderProgram() override;
  SharedPtr<Core::IYukiOGLVertexArray>   GetVertexArray() override;
  const Core::PrimitiveTopology&         GetTopology() override;
  const String&                          GetName() override;
  void                                   Create() override;
  void                                   Destroy() override;

  void RenderMesh(
      const glm::mat4& model,
      const glm::mat4& view,
      const glm::mat4& presentation) override;
};

} // namespace Yuki::Comp