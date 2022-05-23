/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiComp/YukiModel.hpp"

namespace Yuki::Entity
{

using Comp::IYukiModel;

typedef SharedPtr<IYukiModel> ModelType;

extern SharedPtr<IYukiModel> NO_MODEL;

class YukiEntity : virtual public Core::IYukiObject
{

protected:
  ModelType m_pModel;
  Vec3F     m_tPosition;
  String    m_sName;

public:
  explicit YukiEntity(const String& name);
  virtual ~YukiEntity();

  virtual void SetModel(ModelType model) final;

  virtual String    GetName() final;
  virtual ModelType GetModel() final;
  virtual Vec3F&    GetPosition() final;

  void Create() final;
  void Awake() final;
  void Update() final;
  void Render() final;
  void Destroy() final;

  virtual void OnCreate();
  virtual void OnAwake();
  virtual void OnUpdate();
  virtual void OnRender();
  virtual void OnDestroy();
};

} // namespace Yuki::Entity
