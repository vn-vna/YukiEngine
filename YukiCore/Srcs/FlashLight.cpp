#include "YukiComp/Light.hpp"

#include "Private/PFlashLight.hpp"
#include "Private/PLight.hpp"

namespace Yuki::Comp
{

FlashLight::FlashLight()
    : Light::Light {}
{}

FlashLight::~FlashLight() = default;

Vec3F& FlashLight::GetDirection()
{
  return this->m_tLightData.flashlight.direction;
}

#pragma region GETTER_SETTERS

float FlashLight::GetIntensity()
{
  return this->m_tLightData.flashlight.intensity;
}

Vec3F& FlashLight::GetPosition()
{
  return this->m_tLightData.flashlight.position;
}

float FlashLight::GetConstParam()
{
  return this->m_tLightData.flashlight.constant;
}

float FlashLight::GetLinearParam()
{
  return this->m_tLightData.flashlight.linear;
}

float FlashLight::GetQuadraticParam()
{
  return this->m_tLightData.flashlight.intensity;
}

void FlashLight::SetPosition(const Vec3F& pos)
{
  this->m_tLightData.flashlight.position = pos;
}

void FlashLight::SetIntensity(float intensity)
{
  this->m_tLightData.flashlight.intensity = intensity;
}

void FlashLight::SetConstParam(float param)
{
  this->m_tLightData.flashlight.constant = param;
}

void FlashLight::SetLinearParam(float param)
{
  this->m_tLightData.flashlight.linear = param;
}

void FlashLight::SetQuadraticParam(float param)
{
  this->m_tLightData.flashlight.quadratic = param;
}

void FlashLight::SetDirection(const Vec3F& dir)
{
  this->m_tLightData.flashlight.direction = dir;
}

#pragma endregion

} // namespace Yuki::Comp