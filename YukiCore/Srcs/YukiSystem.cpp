/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#include "PYukiSystem.hpp"

#include <fmt/format.h>

#define YUKI_ALL_PROCESSOR_QUERY_STRING    "\\Processor(*)\\% Processor Time"
#define YUKI_ACTIVITY_INFO_UPDATE_INTERVAL 500'000'000 // ns

namespace Yuki::Utils
{

using Core::CreateInterfaceInstance;
using Chrono::CreateTimer;

YukiSystem::YukiSystem()
    : m_tCpuInfo(),
      m_tMemInfo(),
      m_bReady(),
      m_pTimerUpdate()
{
#if defined(WIN32) || defined(_WIN32)
  this->_InitInformationsWin32();
  this->_InitPDH();
#endif

  m_pTimerUpdate = CreateTimer([this](IYukiTimer*) {
    this->_GetCpuActivity(&m_tActivityInfo);
    this->_GetMemoryActivity(&m_tActivityInfo);
  },
      YUKI_ACTIVITY_INFO_UPDATE_INTERVAL);
  m_pTimerUpdate->Start();
}

YukiSystem::~YukiSystem()
{
  m_pTimerUpdate->Terminate();
#if defined(WIN32) || defined(_WIN32)
  this->_DestroyPDH();
#endif
}

const CpuInformation& YukiSystem::GetCpuInformation()
{
  return m_tCpuInfo;
}

const MemoryInformation& YukiSystem::GetMemoryInformation()
{
  return m_tMemInfo;
}

const ResourceActivityInfo& YukiSystem::GetResourceActivityInfo()
{
  return m_tActivityInfo;
}

SharedPtr<IYukiSystem> GetYukiSystemController()
{
  SharedPtr<IYukiSystem> pSysCtrl = CreateInterfaceInstance<IYukiSystem, YukiSystem>();
  return pSysCtrl;
}

void YukiSystem::_GetMemoryActivity(ResourceActivityInfo* info)
{
#if defined(WIN32) || defined(_WIN32)
  // Get memory usaged
  MEMORYSTATUSEX memstat;
  ZeroMemory(&memstat, sizeof(memstat));
  memstat.dwLength = sizeof(memstat);
  GlobalMemoryStatusEx(&memstat);

  info->memoryUsed  = memstat.ullTotalPhys - memstat.ullAvailPhys;
  info->virtmemUsed = memstat.ullTotalVirtual - memstat.ullAvailVirtual;

  // Get memory used by this process
  PROCESS_MEMORY_COUNTERS_EX pmc;
  GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*) &pmc, sizeof(pmc));
  info->memoryUsedByProc  = pmc.WorkingSetSize;
  info->virtmemUsedByProc = pmc.PrivateUsage;
#endif
}

void YukiSystem::_GetCpuActivity(ResourceActivityInfo* info)
{
#if defined(WIN32) || defined(_WIN32)
  PDH_FMT_COUNTERVALUE_ITEM_A stat[100];
  DWORD                       bufferSz = 0;
  DWORD                       itemCount;

  PdhCollectQueryData(m_hPdhQuery);

  AutoType arret = PdhGetFormattedCounterArrayA(m_hCounterCPU, PDH_FMT_DOUBLE, &bufferSz, &itemCount, NULL);
  PdhGetFormattedCounterArrayA(m_hCounterCPU, PDH_FMT_DOUBLE, &bufferSz, &itemCount, stat);

  if (itemCount < 1)
  {
    return;
  }

  info->avgCpuLoad = (float) stat[itemCount - 1].FmtValue.doubleValue;
  info->cpuLoads.reserve(itemCount - 1);
  for (int i = 0; i < itemCount - 1; ++i)
  {
    info->cpuLoads.emplace_back((float) stat[i].FmtValue.doubleValue);
  }
#endif
}

#if defined(WIN32) || defined(_WIN32)
void YukiSystem::_InitInformationsWin32()
{
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

  MEMORYSTATUSEX memstat;
  GlobalMemoryStatusEx(&memstat);

  m_tCpuInfo.numberOfCores       = systemInfo.dwNumberOfProcessors;
  m_tCpuInfo.activeProcessorMask = systemInfo.dwActiveProcessorMask;
  m_tCpuInfo.archivetecture      = (ProcessorArchitecture) systemInfo.wProcessorArchitecture;

  m_tMemInfo.virtmemSize = memstat.dwLength;
  m_tMemInfo.pageSize    = memstat.ullTotalPageFile;
  m_tMemInfo.virtmemSize = memstat.ullTotalVirtual;
}

void YukiSystem::_InitPDH()
{
  PdhOpenQueryA(NULL, NULL, &m_hPdhQuery);
  PdhAddCounterA(m_hPdhQuery, YUKI_ALL_PROCESSOR_QUERY_STRING, NULL, &m_hCounterCPU);
  PdhCollectQueryData(m_hPdhQuery);
}

void YukiSystem::_DestroyPDH()
{
  PdhCloseQuery(m_hPdhQuery);
}
#endif

} // namespace Yuki::Utils