#include "YukiComp/YukiMesh.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiPCH.hpp"
#include "YukiComp/YukiCamera.hpp"
#include "YukiDebug/YukiError.hpp"

#include "PYukiMesh.hpp"

// glm
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>


namespace Yuki::Comp
{

AutoType g_pDefaultMeshShader = Yuki::Core::CreateGLShaderProgram("MeshShader");
AutoType g_pDefaultTexture    = Yuki::Core::CreateGLTexture(Core::TextureType::TEXTURE_2D);

YukiMeshMaterial::YukiMeshMaterial(float specular, float ambient)
    : m_nSpecularStrength(specular), m_nAmbientStrength(ambient)
{}

YukiMeshMaterial::~YukiMeshMaterial() = default;

float YukiMeshMaterial::GetSpecularStrength() { return m_nSpecularStrength; }

float YukiMeshMaterial::GetAmbientStrength() { return m_nAmbientStrength; }

void YukiMeshMaterial::SetSpecularStrength(float strength) { m_nSpecularStrength = strength; }

void YukiMeshMaterial::SetAmbientStrength(float strength) { m_nAmbientStrength = strength; }

YukiMesh::YukiMesh(Vector<MeshVertexFormat>& vertices, MeshIndexData& indices,
    SharedPtr<Core::IYukiOGLTexture>& texture, SharedPtr<IYukiMeshMaterial> material, const String& name)
    : m_pShaderProgram(g_pDefaultMeshShader), m_pTexture(texture), m_Name(name), m_tMeshMatrix(glm::identity<Mat4F>()),
      m_tReNormalMatrix(glm::identity<Mat4F>()), m_aVertexFormat(std::move(vertices)),
      m_tIndexFormat({indices.topology, std::move(indices.data)}), m_pMaterial(material)
{
  m_pVertexBuffer  = Core::CreateGLVertexBuffer();
  m_pElementBuffer = Core::CreateGLElementBuffer();
  m_pVertexArray   = Core::CreateGLVertexArray();
}

YukiMesh::~YukiMesh() = default;

SharedPtr<IYukiOGLTexture> YukiMesh::GetMeshTexture() const { return m_pTexture; }

SharedPtr<IYukiOGLElementBuffer> YukiMesh::GetElementBuffer() const { return m_pElementBuffer; }

SharedPtr<IYukiOGLVertexBuffer> YukiMesh::GetVertexBuffer() const { return m_pVertexBuffer; }

SharedPtr<IYukiOGLShaderProgram> YukiMesh::GetShaderProgram() const { return m_pShaderProgram; }

SharedPtr<IYukiOGLVertexArray> YukiMesh::GetVertexArray() const { return m_pVertexArray; }

SharedPtr<IYukiMeshMaterial> YukiMesh::GetMaterial() const { return m_pMaterial; }

const Core::PrimitiveTopology& YukiMesh::GetTopology() const { return m_tIndexFormat.topology; }

const String& YukiMesh::GetName() const { return m_Name; }

const Mat4F& YukiMesh::GetMeshMatrix() const { return m_tMeshMatrix; }

const Vector<MeshVertexFormat>& YukiMesh::GetVertexData() const { return m_aVertexFormat; }

const MeshIndexData& YukiMesh::GetIndexData() const { return m_tIndexFormat; }

TransformationInfo YukiMesh::GetTransformationInfo() const
{
  Vec3F     scale;
  glm::quat rotation;
  Vec3F     translation;
  Vec3F     skew;
  Vec4F     perspective;

  glm::decompose(m_tMeshMatrix, scale, rotation, translation, skew, perspective);

  return {scale, rotation, translation, skew};
}

void YukiMesh::Create()
{
  try
  {
    m_pVertexBuffer->Create();
    m_pElementBuffer->Create();
    m_pVertexArray->Create();

    this->GetVertexBuffer()->SetBufferData(
        (float*) m_aVertexFormat.data(), m_aVertexFormat.size() * sizeof(MeshVertexFormat));

    this->GetElementBuffer()->SetBufferData(m_tIndexFormat.data);

    AutoType meshVAO = this->GetVertexArray();

    meshVAO->SetVertexBuffer(this->GetVertexBuffer(), 0, 0, sizeof(MeshVertexFormat));

    meshVAO->EnableAttribute(0);
    meshVAO->SetAttributeFormat(3, 0, offsetof(MeshVertexFormat, position));
    meshVAO->AttributeBinding(0, 0);

    meshVAO->EnableAttribute(1);
    meshVAO->SetAttributeFormat(3, 1, offsetof(MeshVertexFormat, normal));
    meshVAO->AttributeBinding(1, 0);

    meshVAO->EnableAttribute(2);
    meshVAO->SetAttributeFormat(2, 2, offsetof(MeshVertexFormat, texcoord));
    meshVAO->AttributeBinding(2, 0);

    meshVAO->SetElementBuffer(this->GetElementBuffer());
  }
  catch (const Debug::YukiError& yer)
  {
    yer.PushErrorMessage();
  }
  catch (const std::runtime_error& rte)
  {
    std::cout << rte.what() << "\n";
  }
}

void YukiMesh::Destroy()
{
  try
  {
    m_pVertexBuffer->Destroy();
    m_pElementBuffer->Destroy();
    m_pVertexArray->Destroy();
  }
  catch (const Debug::YukiError& yer)
  {
    yer.PushErrorMessage();
  }
  catch (const std::runtime_error& rte)
  {
    std::cout << rte.what() << "\n";
  }
}

void YukiMesh::SetMaterial(SharedPtr<IYukiMeshMaterial> material) { m_pMaterial = material; }

void YukiMesh::SetMeshMatrix(const Mat4F& matrix) { m_tMeshMatrix = matrix; }

void YukiMesh::SetTranslation(const Vec3F& position)
{
  AutoType transformationInfo = this->GetTransformationInfo();
  this->TranslateMesh(-transformationInfo.translation);
  this->TranslateMesh(position);
}

void YukiMesh::SetRotation(const Vec3F& axis, float rotationAngle)
{
  AutoType transformationInfo = this->GetTransformationInfo();
  float    crrAngle           = glm::angle(transformationInfo.rotation);
  Vec3F    crrAxis            = glm::axis(transformationInfo.rotation);
  this->RotateMesh(crrAxis, -crrAngle);
  this->RotateMesh(axis, rotationAngle);
}

void YukiMesh::SetScale(const Vec3F& scaleVector)
{
  AutoType transformationInfo = this->GetTransformationInfo();
  this->ScaleMesh(scaleVector / transformationInfo.scale);
}

void YukiMesh::TranslateMesh(const Vec3F& direction)
{
  m_tMeshMatrix     = glm::translate(m_tMeshMatrix, direction);
  m_tReNormalMatrix = glm::inverse(m_tMeshMatrix);
}

void YukiMesh::RotateMesh(const Vec3F& axis, float rotationAngle)
{
  m_tMeshMatrix     = glm::rotate(m_tMeshMatrix, rotationAngle, axis);
  m_tReNormalMatrix = glm::inverse(m_tMeshMatrix);
}

void YukiMesh::ScaleMesh(const Vec3F& scaleVector)
{
  m_tMeshMatrix     = glm::scale(m_tMeshMatrix, scaleVector);
  m_tReNormalMatrix = glm::inverse(m_tMeshMatrix);
}

void YukiMesh::RenderMesh(SharedPtr<IYukiCamera> camera) const
{
  m_pShaderProgram->BindObject();
  // m_pElementBuffer->BindObject();
  m_pVertexArray->BindObject();

  if (m_pTexture.get())
  {
    m_pTexture->BindTexture(0);
  }

  m_pShaderProgram->UniformMatrix("U_ReNormalMatrix", m_tReNormalMatrix, true);
  m_pShaderProgram->UniformMatrix("U_ModelMatrix", m_tMeshMatrix);
  m_pShaderProgram->UniformMatrix("U_ViewMatrix", camera->GetCameraViewMatrix());
  m_pShaderProgram->UniformMatrix("U_ProjectionMatrix", camera->GetCameraProjectionMatrix());
  m_pShaderProgram->UniformVector("U_ViewPosition", camera->GetCameraPosition());
  m_pShaderProgram->UniformValue("U_AmbientStrength", m_pMaterial->GetAmbientStrength());
  m_pShaderProgram->UniformValue("U_SpecularStrength", m_pMaterial->GetSpecularStrength());

  // Some hard coding
  m_pShaderProgram->UniformValue("U_LightIntensity", 1.00f);
  m_pShaderProgram->UniformVector("U_LightPos", Vec3F{-1.30f, 1.30f, 2.00f});
  m_pShaderProgram->UniformVector("U_LightColor", Vec4F{1.00f, 1.00f, 1.00f, 1.00f});
  m_pShaderProgram->UniformValue("U_MeshTextures", 0);

  m_pElementBuffer->DrawAllElements(m_tIndexFormat.topology);
}

SharedPtr<IYukiMesh> CreateYukiMesh(Vector<MeshVertexFormat>& vertexData, MeshIndexData& indexData,
    SharedPtr<Core::IYukiOGLTexture> texture, SharedPtr<IYukiMeshMaterial> material, const String& meshName)
{
  return Core::CreateInterfaceInstance<IYukiMesh, YukiMesh>(vertexData, indexData, texture, material, meshName);
}

SharedPtr<IYukiMeshMaterial> CreateMaterial(float specular, float ambient)
{
  return Core::CreateInterfaceInstance<IYukiMeshMaterial, YukiMeshMaterial>(specular, ambient);
}

void InitializeMeshShader() { g_pDefaultMeshShader->Create(); }

void init_default_2d_texture() {}

void InitializeMeshDefaultTextures() {}

void ReleaseMeshShader() { g_pDefaultMeshShader->Destroy(); }

} // namespace Yuki::Comp
