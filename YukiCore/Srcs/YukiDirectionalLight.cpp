#include "YukiCore/YukiPCH.hpp"

#include "PYukiDirectionalLight.hpp"

namespace Yuki::Comp
{

YukiDirectionalLight::YukiDirectionalLight()
    : m_tDirection{0.00f, 0.00f, 1.00f},
      m_tColor{1.00f, 1.00f, 1.00f, 1.00f},
      m_nIntensity(1000.0f)
{}

const glm::vec4& YukiDirectionalLight::GetColor()
{
  return m_tColor;
}

const float& YukiDirectionalLight::GetIntensity()
{
  return m_nIntensity;
}

const glm::vec3& YukiDirectionalLight::GetDirection()
{
  return m_tDirection;
}

void YukiDirectionalLight::SetDirection(const glm::vec3& direction)
{
  m_tDirection = direction;
}

void YukiDirectionalLight::SetColor(const glm::vec4& color)
{
  m_tColor = color;
}

void YukiDirectionalLight::SetIntensity(const float& intensity)
{
  m_nIntensity = intensity;
}

SharedPtr<IYukiDirectionalLight> CreateDirectionalLight()
{
  return {(IYukiDirectionalLight*) new YukiDirectionalLight, std::default_delete<IYukiDirectionalLight>()};
}


} // namespace Yuki::Comp