#include "YukiCore/YukiPCH.hpp"
#include "YukiComp/YukiCamera.hpp"

#include "PYukiMesh.hpp"

Yuki::SharedPtr<Yuki::Core::IYukiOGLShaderProgram> g_pDefaultMeshShader = Yuki::Core::CreateGLShaderProgram(L"MeshShader");

namespace Yuki::Comp
{

YukiMeshMaterial::YukiMeshMaterial(float specular, float ambient)
    : m_nSpecularStrength(specular), m_nAmbientStrength(ambient)
{}

float YukiMeshMaterial::GetSpecularStrength()
{
  return m_nSpecularStrength;
}

float YukiMeshMaterial::GetAmbientStrength()
{
  return m_nAmbientStrength;
}

void YukiMeshMaterial::SetSpecularStrength(float strength)
{
  m_nSpecularStrength = strength;
}

void YukiMeshMaterial::SetAmbientStrength(float strength)
{
  m_nAmbientStrength = strength;
}

YukiMesh::YukiMesh(const Core::PrimitiveTopology& topology, SharedPtr<Core::IYukiOGLTexture>& textureList, const String& name)
    : m_pShaderProgram(g_pDefaultMeshShader),
      m_pTexture(textureList),
      m_Name(name),
      m_eTopology(topology)
{
  m_pVertexBuffer  = Core::CreateGLVertexBuffer();
  m_pElementBuffer = Core::CreateGLElementBuffer();
  m_pVertexArray   = Core::CreateGLVertexArray();
}

YukiMesh::~YukiMesh() = default;

SharedPtr<Core::IYukiOGLTexture> YukiMesh::GetMeshTexture()
{
  return m_pTexture;
}

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

SharedPtr<IYukiMeshMaterial> YukiMesh::GetMaterial()
{
  return m_pMaterial;
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

void YukiMesh::SetMaterial(SharedPtr<IYukiMeshMaterial> material)
{
  m_pMaterial = material;
}

void YukiMesh::RenderMesh(const glm::mat4& model, SharedPtr<IYukiCamera> camera)
{
  m_pShaderProgram->BindObject();
  m_pElementBuffer->BindObject();
  m_pVertexArray->BindObject();
  m_pTexture->BindTexture(0);

  m_pShaderProgram->UniformMatrix("U_ModelMatrix", model);
  m_pShaderProgram->UniformMatrix("U_ViewMatrix", camera->GetCameraViewMatrix());
  m_pShaderProgram->UniformMatrix("U_ProjectionMatrix", camera->GetCameraProjectionMatrix());
  m_pShaderProgram->UniformVector("U_ViewPosition", camera->GetCameraPosition());
  m_pShaderProgram->UniformValue("U_AmbientStrength", m_pMaterial->GetAmbientStrength());
  m_pShaderProgram->UniformValue("U_SpecularStrength", m_pMaterial->GetSpecularStrength());

  // Some hard coding
  m_pShaderProgram->UniformValue("U_LightIntensity", 1.00f);
  m_pShaderProgram->UniformVector("U_LightPos", glm::vec3{1.30f, 1.30f, 2.00f});
  m_pShaderProgram->UniformVector("U_LightColor", glm::vec4{1.00f, 1.00f, 1.00f, 1.00f});
  m_pShaderProgram->UniformValue("U_MeshTextures", 0);

  m_pElementBuffer->DrawAllElements(m_eTopology);
}

SharedPtr<IYukiMesh> CreateYukiMesh(
    std::vector<Core::VertexData>&    vertexData,
    Core::IndexData&                  indexData,
    SharedPtr<Core::IYukiOGLTexture>& texture,
    SharedPtr<IYukiMeshMaterial>      material,
    const String&                     meshName)
{
  SharedPtr<IYukiMesh> mesh{(IYukiMesh*) new YukiMesh(indexData.topology, texture, meshName)};
  mesh->Create();

  mesh->SetMaterial(material);

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
  meshVAO->SetAttributeFormat(1, 3, offsetof(Core::VertexFormat, normal));
  meshVAO->AttributeBinding(1, 0);

  meshVAO->EnableAttribute(2);
  meshVAO->SetAttributeFormat(2, 2, offsetof(Core::VertexFormat, texcoord));
  meshVAO->AttributeBinding(2, 0);

  return mesh;
}

SharedPtr<IYukiMeshMaterial> CreateMaterial(float specular, float ambient)
{
  return {(IYukiMeshMaterial*) new YukiMeshMaterial(specular, ambient), std::default_delete<IYukiMeshMaterial>()};
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