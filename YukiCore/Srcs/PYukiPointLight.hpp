#pragma once

#include "YukiComp/YukiLights.hpp"

namespace Yuki::Comp
{

class YukiPointLight : public virtual IYukiPointLight
{
protected:
  glm::vec3 m_tPosition;
  glm::vec4 m_tColor;
  float     m_nIntensity;
  float     m_nAttenuationConstant;
  float     m_nAttenuationLinear;
  float     m_nAttenuationQuadratic;

public:
  YukiPointLight();
  virtual ~YukiPointLight() = default;

  const glm::vec4& GetColor() override;
  const float&     GetIntensity() override;
  const glm::vec3& GetPosition() override;
  const float&     GetAttenuationConstantParam() override;
  const float&     GetAttenuationLinearParam() override;
  const float&     GetAttenuationQuadraticParam() override;

  void SetPosition(const glm::vec3& pos) override;
  void SetColor(const glm::vec4& color) override;
  void SetIntensity(const float& intensity) override;

  void SetAttenuationParam(
      const float& constant,
      const float& linear,
      const float& quadratic);

  friend SharedPtr<IYukiPointLight> CreatePointLight();
};

} // namespace Yuki::Comp
