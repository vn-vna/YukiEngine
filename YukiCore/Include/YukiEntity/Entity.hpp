#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiComp/YukiModel.hpp"

namespace Yuki::Entity
{

using Comp::IYukiModel;
using ModelType = SharedPtr<IYukiModel>;
// using ModelManagerType = UnorderedMap<String, SharedPtr<IYukiModel>>;

extern SharedPtr<IYukiModel> NO_MODEL;

class YUKIAPI YukiEntity : virtual public Core::IYukiObject
{

protected:
  ModelType m_pModel;
  Vec3F     m_tPosition;
  String    m_sName;

public:
  YukiEntity(const String& name);
  virtual ~YukiEntity();

  virtual void SetModel(ModelType model) final;

  virtual String    GetName() final;
  virtual ModelType GetModel() final;
  virtual Vec3F&    GetPosition() final;

  void Create() override final;
  void Awake() override final;
  void Update() override final;
  void Render() override final;
  void Destroy() override final;

  virtual void OnCreate();
  virtual void OnAwake();
  virtual void OnUpdate();
  virtual void OnRender();
  virtual void OnDestroy();
};

} // namespace Yuki::Entity
