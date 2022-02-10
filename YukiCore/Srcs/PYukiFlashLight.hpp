#pragma once

#include "YukiComp/YukiLights.hpp"

namespace Yuki::Comp
{

class YukiFlashLight : public virtual IYukiFlashLight
{
protected:
  glm::vec3 m_tDirection;
  glm::vec3 m_tPosition;
  glm::vec4 m_tColor;
  float     m_nIntensity;
  float     m_nAttenuationConstant;
  float     m_nAttenuationLinear;
  float     m_nAttenuationQuadratic;
  float     m_nCutoffAngle;

public:
  YukiFlashLight();
  virtual ~YukiFlashLight() = default;

  const glm::vec4& GetColor() override;
  const float&     GetIntensity() override;
  const glm::vec3& GetPosition() override;
  const float&     GetAttenuationConstantParam() override;
  const float&     GetAttenuationLinearParam() override;
  const float&     GetAttenuationQuadraticParam() override;
  const glm::vec3& GetDirection() override;
  const float&     GetCutOffAngle() override;

  void SetCutOffAngle(const float& cutoff) override;
  void SetDirection(const glm::vec3& direction) override;
  void SetPosition(const glm::vec3& pos) override;
  void SetColor(const glm::vec4& color) override;
  void SetIntensity(const float& intensity) override;
  void SetAttenuationParam(
      const float& constant,
      const float& linear,
      const float& quadratic) override;

  friend SharedPtr<IYukiFlashLight> CreateSpotLight();
};

} // namespace Yuki::Comp