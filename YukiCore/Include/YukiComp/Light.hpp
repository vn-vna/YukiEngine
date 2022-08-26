/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include <YukiCore/Headers.hpp>
#include <YukiCore/Objects.hpp>

#define LIGHTTYPE_DIRECTIONAL 0x00
#define LIGHTTYPE_POINTLIGHT  0x01
#define LIGHTTYPE_SPOTLIGHT   0x02

namespace Yuki::Comp
{

using Core::ISharedObject;

typedef struct StLightData
{
  int lightType;

  Vec3F color;

  union
  {
    struct
    {

      Vec3F direction;

      float intensity;

    } directional;

    struct
    {

      Vec3F position;

      float intensity;
      float constant;
      float linear;
      float quadratic;

    } point;

    struct
    {

      Vec3F direction;
      Vec3F position;

      float intensity;
      float constant;
      float linear;
      float quadratic;
      float cutoff;

    } flashlight;
  };
} LightData;

class ILight : virtual public ISharedObject
{
public:
  virtual float*     GetDataPtr() = 0;
  virtual LightData& GetData()    = 0;
  virtual Vec3F&     GetColor()   = 0;

  virtual void SetColor(const Vec3F& color) = 0;
};

class IPointLight : virtual public ILight
{
public:
  virtual Vec3F& GetPosition()       = 0;
  virtual float  GetIntensity()      = 0;
  virtual float  GetConstParam()     = 0;
  virtual float  GetLinearParam()    = 0;
  virtual float  GetQuadraticParam() = 0;

  virtual void SetPosition(const Vec3F& pos)  = 0;
  virtual void SetIntensity(float intensity)  = 0;
  virtual void SetConstParam(float param)     = 0;
  virtual void SetLinearParam(float param)    = 0;
  virtual void SetQuadraticParam(float param) = 0;
};

class IDirectionalLight : virtual public ILight
{
public:
  virtual Vec3F& GetDirection() = 0;
  virtual float  GetIntensity() = 0;

  virtual void SetDirection(const Vec3F& dir) = 0;
  virtual void SetIntensity(float intensity)  = 0;
};

class IFlashLight : virtual public ILight
{
public:
  virtual Vec3F& GetPosition()       = 0;
  virtual Vec3F& GetDirection()      = 0;
  virtual float  GetIntensity()      = 0;
  virtual float  GetConstParam()     = 0;
  virtual float  GetLinearParam()    = 0;
  virtual float  GetQuadraticParam() = 0;

  virtual void SetPosition(const Vec3F& pos)  = 0;
  virtual void SetDirection(const Vec3F& dir) = 0;
  virtual void SetIntensity(float intensity)  = 0;
  virtual void SetConstParam(float param)     = 0;
  virtual void SetLinearParam(float param)    = 0;
  virtual void SetQuadraticParam(float param) = 0;
};

} // namespace Yuki::Comp