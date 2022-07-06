/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/Objects.hpp"
#include "YukiComp/Model.hpp"

namespace Yuki::Entity
{

using Comp::IYukiModel;

typedef SharedPtr<IYukiModel> ModelType;

extern SharedPtr<IYukiModel> NO_MODEL;

class TemplateEntity : virtual public Core::IYukiObject
{

protected:
  ModelType m_pModel;
  Vec3F     m_tPosition;
  String    m_sName;

public:
  explicit TemplateEntity(const String& name);
  virtual ~TemplateEntity();

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
