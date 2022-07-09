#include "Private/PRandomMachine.hpp"

namespace Yuki::Utils
{

YukiRandomMachine::YukiRandomMachine()
    : m_RandomDevice(),
      m_MT19937(m_RandomDevice())
{}

YukiRandomMachine::~YukiRandomMachine() = default;

float YukiRandomMachine::GetRandomNumber(float rangeFrom, float rangeTo)
{
  UniformRealDistributionF dist(rangeFrom, rangeTo);
  return dist(m_MT19937);
}

RandomDevice& YukiRandomMachine::GetRandomDevice()
{
  return m_RandomDevice;
}

MT19937& YukiRandomMachine::GetRandomType()
{
  return m_MT19937;
}

SharedPtr<IYukiRandomMachine> GetRandomMachine()
{
  static SharedPtr<IYukiRandomMachine> machine =
      Core::CreateInterfaceInstance<IYukiRandomMachine, YukiRandomMachine>();
  return machine;
}

} // namespace Yuki::Utils
