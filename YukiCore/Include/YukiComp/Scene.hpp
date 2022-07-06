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

using Core::ISharedObject;

class IScene : virtual public ISharedObject
{
public:
  virtual void AddEntity(SPTemplateEntity entity) = 0;
  virtual void SetCamera(SPICamera pCamera)        = 0;

  virtual SPICamera                               GetCamera()            = 0;
  virtual UnorderedMap<String, SPTemplateEntity>& GetEntitiesManager()   = 0;
  virtual SPTemplateEntity                        GetEntity(String name) = 0;
  virtual bool                                    IsReady()              = 0;
};

SharedPtr<IScene> CreateYukiScene();

} // namespace Yuki::Comp
