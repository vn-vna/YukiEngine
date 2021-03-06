/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiComp/Scene.hpp"
#include "YukiComp/Camera.hpp"
#include "YukiEntity/Entity.hpp"

#include "PObjects.hpp"

namespace Yuki::Comp
{

using Core::YukiSharedObject;
using Entity::TemplateEntity;

class YukiScene final : virtual public IScene,
                        virtual public YukiSharedObject
{
public:
  YukiScene();
  ~YukiScene() override;

  void AddEntity(SharedPtr<TemplateEntity> entity) override;
  void SetCamera(SharedPtr<ICamera> pCamera) override;

  SharedPtr<ICamera>                               GetCamera() override;
  UnorderedMap<String, SharedPtr<TemplateEntity>>& GetEntitiesManager() override;
  SharedPtr<TemplateEntity>                        GetEntity(String name) override;
  bool                                             IsReady() override;

  void Create() override;
  void Awake() override;
  void Render() override;
  void Update() override;
  void Destroy() override;


private:
  SharedPtr<ICamera>                              m_pCamera;
  UnorderedMap<String, SharedPtr<TemplateEntity>> m_mEntities;
  bool                                            m_bIsReady;
};

} // namespace Yuki::Comp
