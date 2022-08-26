/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiComp/Light.hpp"
#include "YukiCore/Headers.hpp"
#include "YukiCore/Objects.hpp"
#include "YukiComp/Model.hpp"

namespace Yuki::Entity
{

using Comp::ILight;
using Comp::IModel;

typedef SharedPtr<IModel> ModelType;
typedef SharedPtr<ILight> LightType;

extern SharedPtr<IModel> NO_MODEL;

class TemplateEntity : virtual public Core::IObject
{
public:
  explicit TemplateEntity(const String& name);
  virtual ~TemplateEntity();

  virtual void SetModel(ModelType model) final;
  virtual void SetLight(LightType light) final;

  virtual String    GetName() final;
  virtual ModelType GetModel() final;
  virtual LightType GetLight() final;
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

protected:
  ModelType m_pModel;
  LightType m_pLight;
  Vec3F     m_tPosition;
  String    m_sName;
};

} // namespace Yuki::Entity
