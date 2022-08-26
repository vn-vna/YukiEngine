#include "Private/PPointLight.hpp"

namespace Yuki::Comp
{

PointLight::PointLight()
    : Light::Light {}
{}

PointLight::~PointLight() = default;

#pragma region GETTER_SETTERS

Vec3F& PointLight::GetPosition()
{
  return this->m_tLightData.point.position;
}

float PointLight::GetIntensity()
{
  return this->m_tLightData.point.intensity;
}

float PointLight::GetConstParam()
{
  return this->m_tLightData.point.constant;
}

float PointLight::GetLinearParam()
{
  return this->m_tLightData.point.linear;
}

float PointLight::GetQuadraticParam()
{
  return this->m_tLightData.point.intensity;
}

void PointLight::SetPosition(const Vec3F& pos)
{
  this->m_tLightData.point.position = pos;
}

void PointLight::SetIntensity(float intensity)
{
  this->m_tLightData.point.intensity = intensity;
}

void PointLight::SetConstParam(float param)
{
  this->m_tLightData.point.constant = param;
}

void PointLight::SetLinearParam(float param)
{
  this->m_tLightData.point.linear = param;
}

void PointLight::SetQuadraticParam(float param)
{
  this->m_tLightData.point.quadratic = param;
}

#pragma endregion

} // namespace Yuki::Comp