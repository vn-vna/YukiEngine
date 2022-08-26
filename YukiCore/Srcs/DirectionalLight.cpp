#include "Private/PDirectionalLight.hpp"

#include "Private/PLight.hpp"

namespace Yuki::Comp
{

DirectionalLight::DirectionalLight()
    : Light::Light()
{}

DirectionalLight::~DirectionalLight() = default;

#pragma region GETTER_SETTERS

Vec3F& DirectionalLight::GetDirection()
{
  return this->m_tLightData.directional.direction;
}

float DirectionalLight::GetIntensity()
{
  return this->m_tLightData.directional.intensity;
}

void DirectionalLight::SetDirection(const Vec3F& dir)
{
  this->m_tLightData.directional.direction = dir;
}

void DirectionalLight::SetIntensity(float intensity)
{
  this->m_tLightData.directional.intensity = intensity;
}

#pragma endregion

} // namespace Yuki::Comp