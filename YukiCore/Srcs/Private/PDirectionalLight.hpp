#include <YukiComp/Light.hpp>

#include "PLight.hpp"

namespace Yuki::Comp
{

class DirectionalLight : virtual public IDirectionalLight,
                         virtual public Light
{
public:
  DirectionalLight();
  ~DirectionalLight() override;

  Vec3F& GetDirection() override;
  float  GetIntensity() override;

  void SetDirection(const Vec3F& dir) override;
  void SetIntensity(float intensity) override;
};

} // namespace Yuki::Comp
