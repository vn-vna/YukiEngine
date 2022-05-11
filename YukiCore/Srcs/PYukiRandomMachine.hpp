#pragma once

#include <YukiCore/YukiObject.hpp>
#include <YukiUtil/YukiRandomMachine.hpp>

namespace Yuki::Utils
{

class YukiRandomMachine : virtual public IYukiRandomMachine
{
protected:
  RandomDevice m_RandomDevice;
  MT19937      m_MT19937;

public:
  YukiRandomMachine();
  virtual ~YukiRandomMachine();

  float GetRandomNumber(float rangeFrom, float rangeTo) override;

  RandomDevice& GetRandomDevice() override;
  MT19937&      GetRandomType() override;
};

} // namespace Yuki::Utils