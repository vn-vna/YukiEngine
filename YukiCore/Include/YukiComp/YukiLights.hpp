#pragma once

#include "YukiComp/YukiComponent.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Yuki::Comp
{

SharedPtr<IYukiDirectionalLight> YUKIAPI CreateDirectionalLight();
SharedPtr<IYukiPointLight> YUKIAPI       CreatePointLight();
SharedPtr<IYukiFlashLight> YUKIAPI       CreateSpotLight();

#pragma region AUX INTERFACES

class IColoredLight
{
public:
  virtual const glm::vec4& GetColor()                           = 0;
  virtual const float&     GetIntensity()                       = 0;
  virtual void             SetColor(const glm::vec4& color)     = 0;
  virtual void             SetIntensity(const float& intensity) = 0;
};

class IPositionatedLight
{
public:
  virtual const glm::vec3& GetPosition()                     = 0;
  virtual void             SetPosition(const glm::vec3& pos) = 0;
};

class IAttenuatedLight
{
public:
  virtual const float& GetAttenuationConstantParam()  = 0;
  virtual const float& GetAttenuationLinearParam()    = 0;
  virtual const float& GetAttenuationQuadraticParam() = 0;

  virtual void SetAttenuationParam(
      const float& constant,
      const float& linear,
      const float& quadratic) = 0;
};

class IDirectionalLight
{
public:
  virtual const glm::vec3& GetDirection()                     = 0;
  virtual void             SetDirection(const glm::vec3& pos) = 0;
};

class ICutOffLight
{
public:
  virtual const float& GetCutOffAngle()                    = 0;
  virtual void         SetCutOffAngle(const float& cutoff) = 0;
};

#pragma endregion

class YUKIAPI IYukiDirectionalLight : public IColoredLight,
                                      public IDirectionalLight
{};

class YUKIAPI IYukiPointLight : public IColoredLight,
                                public IPositionatedLight,
                                public IAttenuatedLight
{};

class YUKIAPI IYukiFlashLight : public IColoredLight,
                                public IPositionatedLight,
                                public IAttenuatedLight,
                                public IDirectionalLight,
                                public ICutOffLight
{};

} // namespace Yuki::Comp
