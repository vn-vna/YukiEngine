#pragma once

#include "YukiCore/YukiObject.hpp"

#include <glm/mat4x4.hpp>

namespace Yuki::Entities
{

typedef std::map<String, SharedPtr<Comp::IYukiComp>> ComponentsPoolType;

class YUKIAPI Entity : protected Core::IYukiObject
{
protected:
  ComponentsPoolType m_mComponentsPool;
  glm::mat4          m_TranslateMatrix;
  glm::mat4          m_ScaleMatrix;
  glm::mat4          m_RotationMatrix;
  String             m_Name;

  virtual void Create() override;
  virtual void Awake() override;
  virtual void Update() override;
  virtual void Render() override;
  virtual void Destroy() override;

public:
  Entity(const String& name);
  virtual ~Entity();

  virtual void OnCreate();
  virtual void OnAwake();
  virtual void OnUpdate();
  virtual void OnRender();
  virtual void OnDestroy();

  virtual void AddComponent(const String& name, SharedPtr<Comp::IYukiComp> comp);
  virtual void RemoveComponent(const String& name);

  template <typename CompType>
  SharedPtr<CompType> GetComponent(const String& name);

  virtual glm::mat4& GetTranslateMatrix();
  virtual glm::mat4& GetScaleMatrix();
  virtual glm::mat4& GetRotationMatrix();

  virtual SharedPtr<Core::IYukiApp>        GetApp();
  virtual SharedPtr<Core::IYukiInpControl> GetInputControl();
  virtual SharedPtr<Core::IYukiGfxControl> GetGraphicsControl();
  virtual SharedPtr<Core::IYukiWindow>     GetWindow();

  friend class Scene;
};

} // namespace Yuki::Entities

// Generic
namespace Yuki::Entities
{

template <typename CompType>
inline SharedPtr<CompType> Yuki::Entities::Entity::GetComponent(const String& name)
{
  if (m_mComponentsPool.find(name) == m_mComponentsPool.end())
  {
    return SharedPtr<CompType>();
  }
  SharedPtr<Core::IYukiObject> obj = m_mComponentsPool.at(name);
  return std::dynamic_pointer_cast<CompType>(obj);
}

} // namespace Yuki::Entities