#include "PYukiScene.hpp"

#include "YukiDebug/YukiError.hpp"

namespace Yuki::Comp
{

using Debug::YukiSceneDuplicateEntityName;

YukiScene::YukiScene()
    : m_pCamera(nullptr),
      m_mEntities(),
      m_bIsReady(false)
{}

YukiScene::~YukiScene() = default;

void YukiScene::AddEntity(SharedPtr<YukiEntity> entity)
{
  if (this->GetEntity(entity->GetName()).get())
  {
    THROW_YUKI_ERROR(SceneDuplicateEntityName);
  }
  this->GetEntitiesManager().emplace(entity->GetName(), entity);
}

void YukiScene::SetCamera(SharedPtr<IYukiCamera> pCamera)
{
  m_pCamera = pCamera;
}

SharedPtr<IYukiCamera> YukiScene::GetCamera()
{
  return m_pCamera;
}

UnorderedMap<String, SharedPtr<YukiEntity>>& YukiScene::GetEntitiesManager()
{
  return m_mEntities;
}

SharedPtr<YukiEntity> YukiScene::GetEntity(String name)
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
  m_bIsReady = true;
}

bool YukiScene::IsReady()
{
  return m_bIsReady;
}

SharedPtr<IYukiScene> CreateYukiScene()
{
  return Core::CreateInterfaceInstance<IYukiScene, YukiScene>();
}

} // namespace Yuki::Comp
