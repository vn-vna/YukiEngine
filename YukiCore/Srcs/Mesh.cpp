#include "YukiComp/Mesh.hpp"
#include "YukiComp/Camera.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/Objects.hpp"
#include "YukiCore/Headers.hpp"
#include "YukiDebug/Errors.hpp"
#include "YukiUtil/Images.hpp"

#include "Private/PMesh.hpp"

// glm
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Yuki::Comp
{

using Core::CreateGLElementBuffer;
using Core::CreateGLShaderProgram;
using Core::CreateGLTexture;
using Core::CreateGLVertexArray;
using Core::CreateGLVertexBuffer;
using Core::CreateInterfaceInstance;
using Utils::Images;

AutoType g_pDefaultMeshShader = CreateGLShaderProgram("MeshShader");
AutoType g_pDefaultTexture    = CreateGLTexture(Core::TextureType::TEXTURE_2D);

YukiMeshMaterial::YukiMeshMaterial(
    SharedPtr<Images> ambientMap, SharedPtr<Images> specularMap,
    SharedPtr<Images> diffuseMap
)
    : m_pSpecMapImg(specularMap),
      m_pAmbientMapImg(ambientMap),
      m_pDiffMapImg(diffuseMap)
{}

YukiMeshMaterial::~YukiMeshMaterial() = default;

SharedPtr<IOGLTexture> YukiMeshMaterial::GetSpecularMap()
{
  return m_pSpecMap;
}

SharedPtr<IOGLTexture> YukiMeshMaterial::GetAmbientMap()
{
  return m_pAmbientMap;
}

SharedPtr<IOGLTexture> YukiMeshMaterial::GetDiffuseMap()
{
  return m_pDiffMap;
}

void YukiMeshMaterial::SetSpecularMap(SharedPtr<IOGLTexture> strength)
{
  m_pSpecMap = strength;
}

void YukiMeshMaterial::SetAmbientMap(SharedPtr<IOGLTexture> strength)
{
  m_pAmbientMap = strength;
}

void YukiMeshMaterial::SetDiffuseMap(SharedPtr<IOGLTexture> diffmap)
{
  m_pDiffMap = diffmap;
}

void YukiMeshMaterial::Create()
{
  m_pAmbientMap = m_pAmbientMapImg->Generate2DTexture();
  m_pDiffMap    = m_pDiffMapImg->Generate2DTexture();
  m_pSpecMap    = m_pSpecMapImg->Generate2DTexture();
}

void YukiMeshMaterial::Destroy()
{
  m_pAmbientMap->Release();
  m_pSpecMap->Release();
  m_pDiffMap->Release();
}

YukiMesh::YukiMesh(
    Vector<MeshVertexFormat>& vertices, MeshIndexData& indices,
    SharedPtr<Core::IOGLTexture>& texture, SharedPtr<IMaterial> material,
    const String& name
)
    : m_pShaderProgram(g_pDefaultMeshShader),
      m_pTexture(texture),
      m_Name(name),
      m_tMeshMatrix(glm::identity<Mat4F>()),
      m_tReNormalMatrix(glm::identity<Mat4F>()),
      m_aVertexFormat(std::move(vertices)),
      m_tIndexFormat({indices.topology, std::move(indices.data)}),
      m_pMaterial(material)
{
  m_pVertexBuffer  = CreateGLVertexBuffer();
  m_pElementBuffer = CreateGLElementBuffer();
  m_pVertexArray   = CreateGLVertexArray();
}

YukiMesh::~YukiMesh() = default;

SharedPtr<IOGLTexture> YukiMesh::GetMeshTexture() const
{
  return m_pTexture;
}

SharedPtr<IOGLElementBuffer> YukiMesh::GetElementBuffer() const
{
  return m_pElementBuffer;
}

SharedPtr<IOGLVertexBuffer> YukiMesh::GetVertexBuffer() const
{
  return m_pVertexBuffer;
}

SharedPtr<IOGLShaderProgram> YukiMesh::GetShaderProgram() const
{
  return m_pShaderProgram;
}

SharedPtr<IOGLVertexArray> YukiMesh::GetVertexArray() const
{
  return m_pVertexArray;
}

SharedPtr<IMaterial> YukiMesh::GetMaterial() const
{
  return m_pMaterial;
}

const Core::PrimitiveTopology& YukiMesh::GetTopology() const
{
  return m_tIndexFormat.topology;
}

const String& YukiMesh::GetName() const
{
  return m_Name;
}

const Mat4F& YukiMesh::GetMeshMatrix() const
{
  return m_tMeshMatrix;
}

const Vector<MeshVertexFormat>& YukiMesh::GetVertexData() const
{
  return m_aVertexFormat;
}

const MeshIndexData& YukiMesh::GetIndexData() const
{
  return m_tIndexFormat;
}

TransformationInfo YukiMesh::GetTransformationInfo() const
{
  Vec3F       scale;
  QuaternionF rotation;
  Vec3F       translation;
  Vec3F       skew;
  Vec4F       perspective;

  glm::decompose(
      m_tMeshMatrix, scale, rotation, translation, skew, perspective
  );

  return {scale, rotation, translation, skew};
}

void YukiMesh::Create()
{
  try
  {
    m_pShaderProgram->Require();
    m_pMaterial->Require();
    m_pVertexBuffer->Require();
    m_pElementBuffer->Require();
    m_pVertexArray->Require();

    this->GetVertexBuffer()->SetBufferData(
        (float*) m_aVertexFormat.data(),
        m_aVertexFormat.size() * sizeof(MeshVertexFormat)
    );

    this->GetElementBuffer()->SetBufferData(m_tIndexFormat.data);

    AutoType meshVAO = this->GetVertexArray();

    meshVAO->SetVertexBuffer(
        this->GetVertexBuffer(), 0, 0, sizeof(MeshVertexFormat)
    );

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
  catch (const Debug::Errors& yer)
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
    m_pShaderProgram->Release();
    m_pMaterial->Release();
    m_pVertexBuffer->Release();
    m_pElementBuffer->Release();
    m_pVertexArray->Release();
  }
  catch (const Debug::Errors& yer)
  {
    yer.PushErrorMessage();
  }
  catch (const std::runtime_error& rte)
  {
    std::cout << rte.what() << "\n";
  }
}

void YukiMesh::SetMaterial(SharedPtr<IMaterial> material)
{
  m_pMaterial = material;
}

void YukiMesh::SetMeshMatrix(const Mat4F& matrix)
{
  m_tMeshMatrix = matrix;
}

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

void YukiMesh::RenderMesh(SharedPtr<ICamera> camera) const
{
  m_pShaderProgram->BindObject();
  // m_pElementBuffer->BindObject();
  m_pVertexArray->BindObject();

  if (m_pTexture.get())
  {
    m_pTexture->BindTexture(0);
  }
  if (m_pMaterial.get())
  {
    m_pMaterial->GetAmbientMap()->BindTexture(1);
    m_pMaterial->GetSpecularMap()->BindTexture(2);
    m_pMaterial->GetDiffuseMap()->BindTexture(3);
  }

  m_pShaderProgram->UniformMatrix("U_ReNormalMatrix", m_tReNormalMatrix, true);
  m_pShaderProgram->UniformMatrix("U_ModelMatrix", m_tMeshMatrix);
  m_pShaderProgram->UniformMatrix(
      "U_ViewMatrix", camera->GetCameraViewMatrix()
  );
  m_pShaderProgram->UniformMatrix(
      "U_ProjectionMatrix", camera->GetCameraProjectionMatrix()
  );
  m_pShaderProgram->UniformVector(
      "U_ViewPosition", camera->GetCameraPosition()
  );
  // m_pShaderProgram->UniformValue("U_AmbientStrength",
  // m_pMaterial->GetAmbientStrength());
  // m_pShaderProgram->UniformValue("U_SpecularStrength",
  // m_pMaterial->GetSpecularStrength());

  // Some hard coding
  m_pShaderProgram->UniformValue("U_PointLightData[0].intensity", 1.00f);
  m_pShaderProgram->UniformVector(
      "U_LightData[0].position", Vec3F {4.00f, 1.30f, 2.00f}
  );
  m_pShaderProgram->UniformVector(
      "U_PointLightData[0].color", Vec3F {1.00f, 0.00f, 0.00f}
  );

  m_pShaderProgram->UniformValue("U_PointLightData[1].intensity", 1.00f);
  m_pShaderProgram->UniformVector(
      "U_LightData[1].position", Vec3F {3.00f, 1.30f, 2.00f}
  );
  m_pShaderProgram->UniformVector(
      "U_PointLightData[1].color", Vec3F {0.00f, 1.00f, 0.00f}
  );

  m_pShaderProgram->UniformValue("U_PointLightCount", 2);

  // Uniform sampler
  m_pShaderProgram->UniformValue("U_MeshTextures", 0);
  m_pShaderProgram->UniformValue("U_MeshAmbient", 1);
  m_pShaderProgram->UniformValue("U_MeshSpecular", 2);
  m_pShaderProgram->UniformValue("U_MeshDiffMap", 3);

  m_pElementBuffer->DrawAllElements(m_tIndexFormat.topology);
}

SharedPtr<IMesh> GenerateYukiMesh(
    Vector<MeshVertexFormat>& vertexData, MeshIndexData& indexData,
    SharedPtr<IOGLTexture> texture, SharedPtr<IMaterial> material,
    const String& meshName
)
{
  return CreateInterfaceInstance<IMesh, YukiMesh>(
      vertexData, indexData, texture, material, meshName
  );
}

SharedPtr<IMaterial> GenerateSolidMaterial(
    const Vec4F& ambient, const float specular, const float diffuse
)
{
  AutoType ambientMap  = Utils::CreateSolidColorImage(ambient);
  AutoType specularMap = Utils::CreateSolidColorImage(Vec1F {specular});
  AutoType diffuseMap  = Utils::CreateSolidColorImage(Vec1F {diffuse});

  AutoType mat = CreateInterfaceInstance<IMaterial, YukiMeshMaterial>(
      ambientMap, specularMap, diffuseMap
  );

  return mat;
}

} // namespace Yuki::Comp
