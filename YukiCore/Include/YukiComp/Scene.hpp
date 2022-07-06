/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiComp/Camera.hpp"
#include "YukiCore/Objects.hpp"

namespace Yuki::Comp
{

using Core::IYukiSharedObject;
using Entity::TemplateEntity;

class IYukiScene : virtual public IYukiSharedObject
{
public:
  virtual void AddEntity(SharedPtr<TemplateEntity> entity) = 0;
  virtual void SetCamera(SharedPtr<IYukiCamera> pCamera)   = 0;

  virtual SharedPtr<IYukiCamera> GetCamera() = 0;
  virtual UnorderedMap<String, SharedPtr<TemplateEntity>>&
                                    GetEntitiesManager()   = 0;
  virtual SharedPtr<TemplateEntity> GetEntity(String name) = 0;
  virtual bool                      IsReady()              = 0;
};

SharedPtr<IYukiScene> CreateYukiScene();

} // namespace Yuki::Comp
