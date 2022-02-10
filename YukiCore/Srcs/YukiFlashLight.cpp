#include "YukiCore/YukiPCH.hpp"

#include "PYukiFlashLight.hpp"

#include <glm/glm.hpp>

namespace Yuki::Comp
{

YukiFlashLight::YukiFlashLight()
    : m_tDirection{0.00f, 0.00f, 1.00f},
      m_tPosition{0.00f, 0.00f, 0.00f},
      m_tColor{1.00f, 1.00f, 1.00f, 1.00f},
      m_nIntensity(1000.0f),
      m_nAttenuationConstant(0.00f),
      m_nAttenuationLinear(1.00f),
      m_nAttenuationQuadratic(0.00f),
      m_nCutoffAngle(glm::radians(30.00f))
{}

const glm::vec4& YukiFlashLight::GetColor()
{
  return m_tColor;
}

const float& YukiFlashLight::GetIntensity()
{
  return m_nIntensity;
}

const glm::vec3& YukiFlashLight::GetPosition()
{
  return m_tPosition;
}

const float& YukiFlashLight::GetAttenuationConstantParam()
{
  return m_nAttenuationConstant;
}

const float& YukiFlashLight::GetAttenuationLinearParam()
{
  return m_nAttenuationLinear;
}

const float& YukiFlashLight::GetAttenuationQuadraticParam()
{
  return m_nAttenuationQuadratic;
}

const glm::vec3& YukiFlashLight::GetDirection()
{
  return m_tDirection;
}

const float& YukiFlashLight::GetCutOffAngle()
{
  return m_nCutoffAngle;
}

void YukiFlashLight::SetCutOffAngle(const float& cutoff)
{
  m_nCutoffAngle = cutoff;
}

void YukiFlashLight::SetDirection(const glm::vec3& direction)
{
  m_tDirection = direction;
}

void YukiFlashLight::SetPosition(const glm::vec3& pos)
{
  m_tPosition = pos;
}

void YukiFlashLight::SetColor(const glm::vec4& color)
{
  m_tColor = color;
}

void YukiFlashLight::SetIntensity(const float& intensity)
{
  m_nIntensity = intensity;
}

void YukiFlashLight::SetAttenuationParam(const float& constant, const float& linear, const float& quadratic)
{
  m_nAttenuationConstant  = constant;
  m_nAttenuationLinear    = linear;
  m_nAttenuationQuadratic = quadratic;
}

SharedPtr<IYukiFlashLight> CreateSpotLight()
{
  return {(IYukiFlashLight*) new YukiFlashLight, std::default_delete<IYukiFlashLight>()};
}

} // namespace Yuki::Comp