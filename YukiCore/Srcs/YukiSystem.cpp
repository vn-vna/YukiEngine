/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#include "PYukiSystem.hpp"

#include <fmt/format.h>

namespace Yuki::Utils
{

using Core::CreateInterfaceInstance;

YukiSystem::YukiSystem()
    : m_tCpuInfo(),
      m_tMemInfo()
{
#if defined(WIN32) || defined(_WIN32)
  int      CPUInfo[4] = {-1};
  unsigned nExIds, i = 0;
  char     cpuBrandString[0xff];
  std::memset(cpuBrandString, 0x00, sizeof(cpuBrandString));
  // Get the information associated with each extended ID.
  __cpuid(CPUInfo, 0x80000000);
  nExIds = CPUInfo[0];
  for (i = 0x80000000; i <= nExIds; ++i)
  {
    __cpuid(CPUInfo, i);
    // Interpret CPU brand string
    if (i == 0x80000002)
      memcpy(cpuBrandString, CPUInfo, sizeof(CPUInfo));
    else if (i == 0x80000003)
      memcpy(cpuBrandString + 16, CPUInfo, sizeof(CPUInfo));
    else if (i == 0x80000004)
      memcpy(cpuBrandString + 32, CPUInfo, sizeof(CPUInfo));
  }

  m_tCpuInfo.brand = fmt::format("{}", cpuBrandString);

  SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);

  m_tCpuInfo.numberOfCores       = systemInfo.dwNumberOfProcessors;
  m_tCpuInfo.activeProcessorMask = systemInfo.dwActiveProcessorMask;
  m_tCpuInfo.archivetecture      = (ProcessorArchitecture) systemInfo.wProcessorArchitecture;
#endif
}

CpuInformation& YukiSystem::GetCpuInformation()
{
  return m_tCpuInfo;
}

MemoryInformation& YukiSystem::GetMemoryInformation()
{
  return m_tMemInfo;
}

YukiSystem::~YukiSystem() = default;

SharedPtr<IYukiSystem> GetYukiSystemController()
{
  SharedPtr<IYukiSystem> pSysCtrl = CreateInterfaceInstance<IYukiSystem, YukiSystem>();
  return pSysCtrl;
}

} // namespace Yuki::Utils