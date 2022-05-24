#include "YukiCore/YukiApplication.hpp"
#include "YukiEntity/Entity.hpp"

namespace Yuki::Entity
{

using Core::GetYukiApp;

SharedPtr<IYukiModel> NO_MODEL = SharedPtr<IYukiModel>(nullptr);

YukiEntity::YukiEntity(const String& name)
    : m_sName(name),
      m_tPosition(Vec3F{0.00f, 0.00f, 0.00f}),
      m_pModel(NO_MODEL)
{}

YukiEntity::~YukiEntity() = default;

void YukiEntity::SetModel(ModelType model)
{
  m_pModel = model;
}

String YukiEntity::GetName()
{
  return m_sName;
}

ModelType YukiEntity::GetModel()
{
  return m_pModel;
}

Vec3F& YukiEntity::GetPosition()
{
  return m_tPosition;
}

void YukiEntity::Create()
{
  this->OnCreate();
  if (m_pModel.get())
  {
    m_pModel->Create();
  }
}

void YukiEntity::Awake()
{
  this->OnAwake();
}

void YukiEntity::Render()
{
  this->OnRender();
  AutoType crrScene  = GetYukiApp()->GetCurrentScene();
  AutoType crrCamera = crrScene->GetCamera();
  if (m_pModel.get())
  {
    m_pModel->Render(crrCamera);
  }
}

void YukiEntity::Update()
{
  this->OnUpdate();
}

void YukiEntity::Destroy()
{
  this->OnDestroy();
}

void YukiEntity::OnCreate()
{
  // Override this
}

void YukiEntity::OnAwake()
{
  // Override this
}

void YukiEntity::OnRender()
{
  // Override this
}

void YukiEntity::OnUpdate()
{
  // Override this
}

void YukiEntity::OnDestroy()
{
  // Override this
}

} // namespace Yuki::Entity
