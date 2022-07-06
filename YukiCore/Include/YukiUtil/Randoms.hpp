/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Objects.hpp"

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

SharedPtr<IYukiRandomMachine> GetRandomMachine();

} // namespace Yuki::Utils
