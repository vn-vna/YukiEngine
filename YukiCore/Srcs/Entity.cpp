#include "YukiCore/YukiApplication.hpp"
#include "YukiEntity/Entity.hpp"

namespace Yuki::Entity
{

using Core::GetYukiApp;

SharedPtr<IYukiModel> NO_MODEL = SharedPtr<IYukiModel>(nullptr);

TemplateEntity::TemplateEntity(const String& name)
    : m_sName(name), m_tPosition(Vec3F{0.00f, 0.00f, 0.00f}), m_pModel(NO_MODEL)
{}

TemplateEntity::~TemplateEntity() = default;

void TemplateEntity::SetModel(ModelType model) { m_pModel = model; }

String TemplateEntity::GetName() { return m_sName; }

ModelType TemplateEntity::GetModel() { return m_pModel; }

Vec3F& TemplateEntity::GetPosition() { return m_tPosition; }

void TemplateEntity::Create()
{
  this->OnCreate();
  if (m_pModel.get())
  {
    m_pModel->Create();
  }
}

void TemplateEntity::Awake() { this->OnAwake(); }

void TemplateEntity::Render()
{
  this->OnRender();
  AutoType crrScene  = GetYukiApp()->GetCurrentScene();
  AutoType crrCamera = crrScene->GetCamera();
  if (m_pModel.get())
  {
    m_pModel->Render(crrCamera);
  }
}

void TemplateEntity::Update() { this->OnUpdate(); }

void TemplateEntity::Destroy() { this->OnDestroy(); }

void TemplateEntity::OnCreate()
{
  // Override this
}

void TemplateEntity::OnAwake()
{
  // Override this
}

void TemplateEntity::OnRender()
{
  // Override this
}

void TemplateEntity::OnUpdate()
{
  // Override this
}

void TemplateEntity::OnDestroy()
{
  // Override this
}

} // namespace Yuki::Entity
