/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiComp/Camera.hpp"
#include "YukiCore/Headers.hpp"
#include "YukiCore/Objects.hpp"
#include "YukiEntity/Entity.hpp"

namespace Yuki::Comp
{

using Comp::ICamera;
using Core::ISharedObject;
using Entity::TemplateEntity;

class IScene : virtual public ISharedObject
{
public:
  virtual void AddEntity(SharedPtr<TemplateEntity> entity) = 0;
  virtual void SetCamera(SharedPtr<ICamera> pCamera)       = 0;

  virtual SharedPtr<ICamera> GetCamera() = 0;
  virtual UnorderedMap<String, SharedPtr<TemplateEntity>>&
                                    GetEntitiesManager()   = 0;
  virtual SharedPtr<TemplateEntity> GetEntity(String name) = 0;
  virtual bool                      IsReady()              = 0;
};

SharedPtr<IScene> CreateYukiScene();

} // namespace Yuki::Comp
