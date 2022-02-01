#include "YukiCore/YukiPCH.hpp"

#include "PYukiMesh.hpp"

Yuki::SharedPtr<Yuki::Core::IYukiOGLShaderProgram> g_pDefaultMeshShader = Yuki::Core::CreateGLShaderProgram(L"MeshShader");

namespace Yuki::Comp
{

YukiMesh::YukiMesh(const Core::PrimitiveTopology& topology, const String& name)
    : m_pShaderProgram(g_pDefaultMeshShader),
      m_Name(name),
      m_eTopology(topology)
{
  m_pVertexBuffer  = Core::CreateGLVertexBuffer();
  m_pElementBuffer = Core::CreateGLElementBuffer();
  m_pVertexArray   = Core::CreateGLVertexArray();
}

YukiMesh::~YukiMesh() = default;

SharedPtr<Core::IYukiOGLElementBuffer> YukiMesh::GetElementBuffer()
{
  return m_pElementBuffer;
}

SharedPtr<Core::IYukiOGLVertexBuffer> YukiMesh::GetVertexBuffer()
{
  return m_pVertexBuffer;
}

SharedPtr<Core::IYukiOGLShaderProgram> YukiMesh::GetShaderProgram()
{
  return m_pShaderProgram;
}

SharedPtr<Core::IYukiOGLVertexArray> YukiMesh::GetVertexArray()
{
  return m_pVertexArray;
}

const Core::PrimitiveTopology& YukiMesh::GetTopology()
{
  return m_eTopology;
}

const String& YukiMesh::GetName()
{
  return m_Name;
}

void YukiMesh::Create()
{
  m_pVertexBuffer->Create();
  m_pElementBuffer->Create();
  m_pVertexArray->Create();
}

void YukiMesh::Destroy()
{
  m_pVertexBuffer->Destroy();
  m_pElementBuffer->Destroy();
  m_pVertexArray->Destroy();
}

void YukiMesh::RenderMesh(const glm::mat4& model, const glm::mat4& view, const glm::mat4& presentation)
{
  m_pShaderProgram->BindObject();
  m_pElementBuffer->BindObject();
  m_pVertexArray->BindObject();
  m_pShaderProgram->UniformMatrix("U_ModelMatrix", model);
  m_pShaderProgram->UniformMatrix("U_ViewMatrix", view);
  m_pShaderProgram->UniformMatrix("U_PresentationMatrix", presentation);
  m_pShaderProgram->UniformValue("U_AmbientStrength", 0.10f);

  m_pElementBuffer->DrawAllElements(m_eTopology);
}

SharedPtr<IYukiMesh> CreateYukiMesh(std::vector<Core::VertexData>& vertexData, Core::IndexData& indexData, const String& meshName)
{
  SharedPtr<IYukiMesh> mesh{(IYukiMesh*) new YukiMesh(indexData.topology, meshName)};
  mesh->Create();

  mesh->GetVertexBuffer()
      ->SetBufferData((float*) vertexData.data(), vertexData.size() * sizeof(Core::VertexData));

  mesh->GetElementBuffer()
      ->SetBufferData(indexData.data);

  AutoType meshVAO = mesh->GetVertexArray();

  meshVAO->SetVertexBuffer(mesh->GetVertexBuffer(), 0, 0, sizeof(Core::VertexFormat));
  meshVAO->EnableAttribute(0);
  meshVAO->SetAttributeFormat(0, 3, offsetof(Core::VertexFormat, position));
  meshVAO->AttributeBinding(0, 0);

  meshVAO->EnableAttribute(1);
  meshVAO->SetAttributeFormat(1, 4, offsetof(Core::VertexFormat, color));
  meshVAO->AttributeBinding(1, 0);

  meshVAO->EnableAttribute(2);
  meshVAO->SetAttributeFormat(2, 3, offsetof(Core::VertexFormat, texcoord));
  meshVAO->AttributeBinding(2, 0);

  meshVAO->EnableAttribute(3);
  meshVAO->SetAttributeFormat(3, 1, offsetof(Core::VertexFormat, texID));
  meshVAO->AttributeBinding(3, 0);
  return mesh;
}

void InitializeMeshShader()
{
  g_pDefaultMeshShader->Create();
}

void ReleaseMeshShader()
{
  g_pDefaultMeshShader->Destroy();
}

} // namespace Yuki::Comp