#include "Private/PScene.hpp"

#include "YukiDebug/Errors.hpp"

namespace Yuki::Comp
{

YukiScene::YukiScene()
    : m_pCamera(nullptr),
      m_mEntities(),
      m_bIsReady(false)
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

void YukiScene::Create()
{
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
  m_bIsReady = false;
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
