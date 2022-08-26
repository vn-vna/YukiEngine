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

#include "PObjects.hpp"

namespace Yuki::Comp
{

using Core::YukiSharedObject;

class Light : virtual public ILight,
              virtual public YukiSharedObject
{
public:
  Light();
  ~Light() override;

  float*     GetDataPtr() override;
  LightData& GetData() override;
  Vec3F&     GetColor() override;

  void SetColor(const Vec3F& color) override;

protected:
  void* GetRawDataPtr();

  LightData m_tLightData;
};

} // namespace Yuki::Comp
