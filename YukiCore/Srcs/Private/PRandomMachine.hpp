/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Objects.hpp"
#include "YukiUtil/Randoms.hpp"

namespace Yuki::Utils
{

class YukiRandomMachine : virtual public IYukiRandomMachine
{
public:
  YukiRandomMachine();
  virtual ~YukiRandomMachine();

  float GetRandomNumber(float rangeFrom, float rangeTo) override;

  RandomDevice& GetRandomDevice() override;
  MT19937&      GetRandomType() override;

private:
  RandomDevice m_RandomDevice;
  MT19937      m_MT19937;
};

} // namespace Yuki::Utils
