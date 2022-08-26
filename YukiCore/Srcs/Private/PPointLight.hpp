#pragma once

#include <YukiComp/Light.hpp>

#include "PLight.hpp"

namespace Yuki::Comp
{

class PointLight : virtual public IPointLight,
                   virtual public Light
{
public:
  PointLight();
  ~PointLight() override;

  Vec3F& GetPosition() override;
  float  GetIntensity() override;
  float  GetConstParam() override;
  float  GetLinearParam() override;
  float  GetQuadraticParam() override;

  void SetPosition(const Vec3F& pos) override;
  void SetIntensity(float intensity) override;
  void SetConstParam(float param) override;
  void SetLinearParam(float param) override;
  void SetQuadraticParam(float param) override;
};

} // namespace Yuki::Comp