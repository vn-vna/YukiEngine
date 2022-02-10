#pragma once

#include "YukiCore/YukiObject.hpp"

#include <glm/mat4x4.hpp>

namespace Yuki::Comp
{

typedef std::map<String, SharedPtr<IYukiMesh>> MeshesPoolType;

class YUKIAPI YukiEntity : protected Core::IYukiObject
{
protected:
  MeshesPoolType m_mMeshPool;
  glm::mat4      m_TranslateMatrix;
  glm::mat4      m_ScaleMatrix;
  glm::mat4      m_RotationMatrix;
  String         m_Name;

  virtual void Create() override;
  virtual void Awake() override;
  virtual void Update() override;
  virtual void Render() override;
  virtual void Destroy() override;

public:
  YukiEntity(const String& name);
  virtual ~YukiEntity();

  virtual void OnCreate();
  virtual void OnAwake();
  virtual void OnUpdate();
  virtual void OnRender();
  virtual void OnDestroy();

  void BindMesh(const String& name, const SharedPtr<IYukiMesh>& comp);
  void UnbindMesh(const String& name);

  template <typename CompType>
  SharedPtr<CompType> GetComponent(const String& name);

  glm::mat4& GetTranslateMatrix();
  glm::mat4& GetScaleMatrix();
  glm::mat4& GetRotationMatrix();

  SharedPtr<Core::IYukiApp>        GetApp();
  SharedPtr<Core::IYukiInpControl> GetInputControl();
  SharedPtr<Core::IYukiGfxControl> GetGraphicsControl();
  SharedPtr<Core::IYukiWindow>     GetWindow();

  friend class YukiScene;
};

} // namespace Yuki::Comp

// Generic
namespace Yuki::Comp
{

template <typename CompType>
inline SharedPtr<CompType> Yuki::Comp::YukiEntity::GetComponent(const String& name)
{
  if (m_mMeshPool.find(name) == m_mMeshPool.end())
  {
    return SharedPtr<CompType>();
  }
  SharedPtr<Core::IYukiObject> obj = m_mMeshPool.at(name);
  return std::dynamic_pointer_cast<CompType>(obj);
}

} // namespace Yuki::Comp
