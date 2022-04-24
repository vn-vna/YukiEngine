#pragma once

#include "YukiComp/YukiScene.hpp"
#include "YukiComp/YukiCamera.hpp"
#include "YukiEntity/Entity.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Comp
{

using Core::YukiObject;
using Entity::YukiEntity;

class YukiScene final : virtual public IYukiScene,
                        virtual public YukiObject
{
protected:
  SharedPtr<IYukiCamera>                      m_pCamera;
  UnorderedMap<String, SharedPtr<YukiEntity>> m_mEntities;
  bool                                        m_bIsReady;

public:
  YukiScene();
  ~YukiScene() override;

  void AddEntity(SharedPtr<YukiEntity> entity) override;
  void SetCamera(SharedPtr<IYukiCamera> pCamera) override;

  SharedPtr<IYukiCamera>                       GetCamera() override;
  UnorderedMap<String, SharedPtr<YukiEntity>>& GetEntitiesManager() override;
  SharedPtr<YukiEntity>                        GetEntity(String name) override;
  bool                                         IsReady() override;

  void Create() override;
  void Awake() override;
  void Render() override;
  void Update() override;
  void Destroy() override;
};

} // namespace Yuki::Comp