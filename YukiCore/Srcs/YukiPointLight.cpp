#include "YukiCore/YukiPCH.hpp"

#include "PYukiPointLight.hpp"

namespace Yuki::Comp
{

YukiPointLight::YukiPointLight()
    : m_tPosition{0.00f, 0.00f, 0.00f},
      m_tColor{1.00f, 1.00f, 1.00f, 1.00f},
      m_nIntensity(1000.0f),
      m_nAttenuationConstant(0.00f),
      m_nAttenuationLinear(1.00f),
      m_nAttenuationQuadratic(0.00f)
{}

const glm::vec4& YukiPointLight::GetColor()
{
  return m_tColor;
}

const float& YukiPointLight::GetIntensity()
{
  return m_nIntensity;
}

const glm::vec3& YukiPointLight::GetPosition()
{
  return m_tPosition;
}

const float& YukiPointLight::GetAttenuationConstantParam()
{
  return m_nAttenuationConstant;
}

const float& YukiPointLight::GetAttenuationLinearParam()
{
  return m_nAttenuationLinear;
}

const float& YukiPointLight::GetAttenuationQuadraticParam()
{
  return m_nAttenuationQuadratic;
}

void YukiPointLight::SetPosition(const glm::vec3& pos)
{
  m_tPosition = pos;
}

void YukiPointLight::SetColor(const glm::vec4& color)
{
  m_tColor = color;
}

void YukiPointLight::SetIntensity(const float& intensity)
{
  m_nIntensity = intensity;
}

void YukiPointLight::SetAttenuationParam(const float& constant, const float& linear, const float& quadratic)
{
  m_nAttenuationConstant  = constant;
  m_nAttenuationLinear    = linear;
  m_nAttenuationQuadratic = quadratic;
}

SharedPtr<IYukiPointLight> CreatePointLight()
{
  return {(IYukiPointLight*) new YukiPointLight, std::default_delete<IYukiPointLight>()};
}

} // namespace Yuki::Comp