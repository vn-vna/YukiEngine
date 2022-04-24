#pragma once

#include "YukiComp/YukiCamera.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Comp
{

using Entity::YukiEntity;

class YUKIAPI IYukiScene : virtual public Core::IYukiObject
{
public:
  virtual void AddEntity(SharedPtr<YukiEntity> entity)   = 0;
  virtual void SetCamera(SharedPtr<IYukiCamera> pCamera) = 0;

  virtual SharedPtr<IYukiCamera>                       GetCamera()            = 0;
  virtual UnorderedMap<String, SharedPtr<YukiEntity>>& GetEntitiesManager()   = 0;
  virtual SharedPtr<YukiEntity>                        GetEntity(String name) = 0;
  virtual bool                                         IsReady()              = 0;
};

SharedPtr<IYukiScene> YUKIAPI CreateYukiScene();

} // namespace Yuki::Comp
