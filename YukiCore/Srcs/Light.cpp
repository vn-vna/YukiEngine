#include "Private/PLight.hpp"

#include "YukiComp/Light.hpp"

namespace Yuki::Comp
{

Light::Light()
    : m_tLightData {}
{}

Light::~Light() = default;

float* Light::GetDataPtr()
{
  return static_cast<float*>(this->GetRawDataPtr());
}

void* Light::GetRawDataPtr()
{
  return static_cast<void*>(&this->m_tLightData);
}

LightData& Light::GetData()
{
  return this->m_tLightData;
}

Vec3F& Light::GetColor()
{
  return this->m_tLightData.color;
}

void Light::SetColor(const Vec3F& color)
{
  this->m_tLightData.color = color;
}

} // namespace Yuki::Comp