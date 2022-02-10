#include "YukiCore/YukiPCH.hpp"
#include "YukiComp/YukiCamera.hpp"
#include "YukiDebug/YukiError.hpp"

#include "PYukiMesh.hpp"

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

constexpr const unsigned ASSIMP_LOAD_FLAG = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;

Yuki::SharedPtr<Yuki::Core::IYukiOGLShaderProgram>
    g_pDefaultMeshShader = Yuki::Core::CreateGLShaderProgram(L"MeshShader");

namespace Yuki::Comp
{

YukiMesh::YukiMesh(const Core::PrimitiveTopology& topology, SharedPtr<Core::IYukiOGLTexture>& textureList, const String& name)
    : m_pShaderProgram(g_pDefaultMeshShader),
      m_pTexture(textureList),
      m_Name(name),
      m_eTopology(topology),
      m_nRequired(0)
{
  m_pVertexBuffer  = Core::CreateGLVertexBuffer();
  m_pElementBuffer = Core::CreateGLElementBuffer();
  m_pVertexArray   = Core::CreateGLVertexArray();
}

YukiMesh::~YukiMesh() = default;

ComponentType YukiMesh::GetComponentType()
{
  return ComponentType::MESH;
}

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
  if (m_nRequired <= 0)
  {
    m_pVertexBuffer->Create();
    m_pElementBuffer->Create();
    m_pVertexArray->Create();
    m_pShaderProgram->Create();
    m_nRequired = 1;
  }
  else
  {
    ++m_nRequired;
  }
}

void YukiMesh::Destroy()
{
  --m_nRequired;
  if (m_nRequired == 0)
  {
    m_pVertexBuffer->Destroy();
    m_pElementBuffer->Destroy();
    m_pVertexArray->Destroy();
    m_pShaderProgram->Destroy();
  }
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

  // Some hard coding
  m_pShaderProgram->UniformValue("U_AmbientStrength", 0.01f);
  m_pShaderProgram->UniformValue("U_LightIntensity", 0.10f);
  m_pShaderProgram->UniformValue("U_SpecularStrength", 0.50f);
  m_pShaderProgram->UniformVector("U_LightPos", glm::vec3{1.30f, 1.30f, 2.00f});
  m_pShaderProgram->UniformVector("U_LightColor", glm::vec4{1.00f, 1.00f, 1.00f, 1.00f});
  m_pShaderProgram->UniformValue("U_MeshTextures", 0);

  m_pElementBuffer->DrawAllElements(m_eTopology);
}

SharedPtr<IYukiMesh> CreateYukiMesh(
    std::vector<Core::VertexData>&    vertexData,
    Core::IndexData&                  indexData,
    SharedPtr<Core::IYukiOGLTexture>& texture,
    const String&                     meshName)
{
  SharedPtr<IYukiMesh> mesh{(IYukiMesh*) new YukiMesh(indexData.topology, texture, meshName)};
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

std::vector<SharedPtr<IYukiMesh>> LoadMeshesFromFile(const AsciiString& fileName)
{
  Assimp::Importer importer;
  const aiScene*   pScene = importer.ReadFile(fileName, ASSIMP_LOAD_FLAG);

  if (!pScene)
  {
    THROW_YUKI_ERROR(Debug::YukiAssimpLoadModelFailed);
  }

  std::vector<SharedPtr<IYukiMesh>> aMeshes(pScene->mNumMeshes);

  return std::vector<SharedPtr<IYukiMesh>>();
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
