#include "Private/PScene.hpp"

#include "YukiCore/Graphics.hpp"
#include "YukiCore/Headers.hpp"
#include "YukiDebug/Errors.hpp"

namespace Yuki::Comp
{
using Core::CreateGLShaderProgram;

AutoType g_pDefaultMeshShader = CreateGLShaderProgram("MeshShader");

YukiScene::YukiScene()
    : m_pCamera(nullptr),
      m_mEntities(),
      m_bIsReady(false),
      m_pShaderProgram(g_pDefaultMeshShader)
{}

YukiScene::~YukiScene() = default;

void YukiScene::AddEntity(SharedPtr<TemplateEntity> entity)
{
  if (this->GetEntity(entity->GetName()).get())
  {
    THROW_YUKI_ERROR(SceneDuplicateEntityName);
  }
  this->GetEntitiesManager().emplace(entity->GetName(), entity);
}

void YukiScene::SetCamera(SharedPtr<ICamera> pCamera)
{
  m_pCamera = pCamera;
}

void YukiScene::SetMeshRenderShader(SharedPtr<IOGLShaderProgram> pShader)
{
  this->m_pShaderProgram = pShader;
}

SharedPtr<ICamera> YukiScene::GetCamera()
{
  return m_pCamera;
}

UnorderedMap<String, SharedPtr<TemplateEntity>>& YukiScene::GetEntitiesManager()
{
  return m_mEntities;
}

SharedPtr<TemplateEntity> YukiScene::GetEntity(String name)
{
  AutoType result = this->GetEntitiesManager().find(name);
  if (result == this->GetEntitiesManager().end())
  {
    return {nullptr};
  }
  return result->second;
}

SharedPtr<IOGLShaderProgram> YukiScene::GetMeshRenderShader()
{
  return m_pShaderProgram;
}

void YukiScene::Create()
{
  m_pShaderProgram->Require();
  m_pCamera->Create();
  for (const AutoType& entity : m_mEntities)
  {
    if (entity.second.get())
    {
      entity.second->Create();
    }
  }
  m_bIsReady = true;
}

void YukiScene::Awake()
{
  m_pCamera->Awake();
  for (const AutoType& entity : m_mEntities)
  {
    if (entity.second.get())
    {
      entity.second->Awake();
    }
  }
}

void YukiScene::Render()
{
  this->_AqquireUniform();
  // Render entities
  for (const AutoType& entity : m_mEntities)
  {
    if (entity.second.get())
    {
      entity.second->Render();
    }
  }
}

void YukiScene::Update()
{
  m_pCamera->Update();
  for (const AutoType& entity : m_mEntities)
  {
    if (entity.second.get())
    {
      entity.second->Update();
    }
  }
}

void YukiScene::Destroy()
{
  for (const AutoType& entity : m_mEntities)
  {
    if (entity.second.get())
    {
      entity.second->Destroy();
    }
  }
  m_pShaderProgram->Release();
  m_bIsReady = false;
}

void YukiScene::_AqquireUniform()
{
  m_pShaderProgram->BindObject();
  // Some hard coding
  m_pShaderProgram->UniformValue("U_PointLightData[0].intensity", 1.00f);
  m_pShaderProgram->UniformVector(
      "U_PointLightData[0].position", Vec3F {4.00f, 1.30f, 2.00f}
  );
  m_pShaderProgram->UniformVector(
      "U_PointLightData[0].color", Vec3F {1.00f, 0.00f, 0.00f}
  );

  m_pShaderProgram->UniformValue("U_PointLightData[1].intensity", 1.00f);
  m_pShaderProgram->UniformVector(
      "U_PointLightData[1].position", Vec3F {-3.00f, -1.30f, -2.00f}
  );
  m_pShaderProgram->UniformVector(
      "U_PointLightData[1].color", Vec3F {0.00f, 1.00f, 0.00f}
  );

  m_pShaderProgram->UniformValue("U_PointLightCount", 2);
}

bool YukiScene::IsReady()
{
  return m_bIsReady;
}

SharedPtr<IScene> CreateYukiScene()
{
  return Core::CreateInterfaceInstance<IScene, YukiScene>();
}

} // namespace Yuki::Comp
