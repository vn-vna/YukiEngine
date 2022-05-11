#pragma once

#include <random>

namespace Yuki::Utils
{

using RandomDevice = std::random_device;
using MT19937      = std::mt19937;

template <typename T>
using UniformRealDistribution = std::uniform_real_distribution<T>;

typedef UniformRealDistribution<float> UniformRealDistributionF;

class IYukiRandomMachine
{
public:
  virtual float GetRandomNumber(float rangeFrom = 0.00f, float rangeTo = 1.00f) = 0;

  virtual RandomDevice& GetRandomDevice() = 0;
  virtual MT19937&      GetRandomType()   = 0;
};

SharedPtr<IYukiRandomMachine> YUKIAPI GetRandomMachine();

} // namespace Yuki::Utils