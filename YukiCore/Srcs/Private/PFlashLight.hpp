#include <YukiComp/Light.hpp>

#include "PLight.hpp"

namespace Yuki::Comp
{

class FlashLight : virtual public IFlashLight,
                   virtual public Light
{
public:
  FlashLight();
  ~FlashLight() override;

  Vec3F& GetPosition() override;
  Vec3F& GetDirection() override;
  float  GetIntensity() override;
  float  GetConstParam() override;
  float  GetLinearParam() override;
  float  GetQuadraticParam() override;

  void SetPosition(const Vec3F& pos) override;
  void SetDirection(const Vec3F& dir) override;
  void SetIntensity(float intensity) override;
  void SetConstParam(float param) override;
  void SetLinearParam(float param) override;
  void SetQuadraticParam(float param) override;
};

} // namespace Yuki::Comp
