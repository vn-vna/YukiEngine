#include "YukiCore/YukiPCH.hpp"

#include "YukiCore/YukiApplication.hpp"
#include "YukiEntities/Entity.hpp"
#include "YukiDebug/YukiError.hpp"

#define INTERFACE_FUNC_CALL(func)                \
  if (m_mComponentsPool.empty())                 \
  {                                              \
    return;                                      \
  }                                              \
  for (const AutoType& comp : m_mComponentsPool) \
  {                                              \
    AutoType& ptr = comp.second;                 \
    if (!ptr.get())                              \
    {                                            \
      continue;                                  \
    }                                            \
    ptr->func##();                               \
  }

namespace Yuki::Entities
{
Entity::Entity(const String& name)
    : m_mComponentsPool(),
      m_RotationMatrix(1.00f),
      m_ScaleMatrix(1.00f),
      m_TranslateMatrix(1.00f),
      m_Name(name)
{}

Entity::~Entity() = default;

void Entity::OnCreate()
{}

void Entity::OnAwake()
{}

void Entity::OnUpdate()
{}

void Entity::OnRender()
{}

void Entity::OnDestroy()
{}

void Entity::AddComponent(const String& name, SharedPtr<Core::IYukiObject> comp)
{
  if (m_mComponentsPool.find(name) != m_mComponentsPool.end())
  {
    THROW_YUKI_ERROR(Debug::YukiEntityAddComponentExistsError);
  }
  m_mComponentsPool.insert({name, comp});
}

void Entity::RemoveComponent(const String& name)
{
  if (m_mComponentsPool.find(name) == m_mComponentsPool.end())
  {
    THROW_YUKI_ERROR(Debug::YukiEntityRemoveComponentNExistsError);
  }
  m_mComponentsPool.erase(name);
}

glm::mat4& Entity::GetTranslateMatrix()
{
  return m_TranslateMatrix;
}

glm::mat4& Entity::GetScaleMatrix()
{
  return m_ScaleMatrix;
}

glm::mat4& Entity::GetRotationMatrix()
{
  return m_RotationMatrix;
}

SharedPtr<Core::IYukiApp> Entity::GetApp()
{
  return Core::GetYukiApp();
}

SharedPtr<Core::IYukiInpControl> Entity::GetInputControl()
{
  return GetApp()->GetInputController();
}

SharedPtr<Core::IYukiGfxControl> Entity::GetGraphicsControl()
{
  return GetApp()->GetGraphicsController();
}

SharedPtr<Core::IYukiWindow> Entity::GetWindow()
{
  return GetApp()->GetWindow();
}

void Entity::Create()
{
  OnCreate();
  INTERFACE_FUNC_CALL(Create);
}

void Entity::Awake()
{
  OnAwake();
  INTERFACE_FUNC_CALL(Awake);
}

void Entity::Update()
{
  OnUpdate();
  INTERFACE_FUNC_CALL(Update);
}

void Entity::Render()
{
  OnRender();
  INTERFACE_FUNC_CALL(Render);
}

void Entity::Destroy()
{
  OnDestroy();
  INTERFACE_FUNC_CALL(Destroy);
}

} // namespace Yuki::Entities