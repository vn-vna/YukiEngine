/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#include "PYukiSystem.hpp"

#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiPCH.hpp"
#include "YukiUtil/YukiSystem.hpp"
#include "YukiUtil/YukiUtilities.hpp"

#include <fmt/format.h>

#if defined(linux) || defined(__linux) || defined(__linux__)
#  include <linux/sysinfo.h>
#  include <sys/sysinfo.h>
#  include <sys/types.h>
#endif

#define YUKI_ALL_PROCESSOR_QUERY_STRING    "\\Processor(*)\\% Processor Time"
#define YUKI_ACTIVITY_INFO_UPDATE_INTERVAL 500'000'000 // ns

namespace Yuki::Utils
{

using Core::CreateInterfaceInstance;
using Chrono::CreateTimer;

typedef struct StParsedCpuInfo
{
  int      nId;
  String   sVendor;
  uint32_t nFamilyId;
  uint32_t nModelId;
  String   sCpuName;
  uint32_t nStepping;
  uint32_t nMicroCode;
  float    nClockSpd;
  size_t   szCacheSize;
  String   sCacheSizeUnit;
  uint32_t nPhysicalCoreId;
  uint32_t nSiblings;
  uint32_t nCoreId;
  uint32_t nCoresCount;
  uint32_t nApicId;
  uint32_t nInitialApicID;
  bool     bFpu;
  bool     bFpuException;
  uint32_t nCpuIdLevel;
  bool     bWp;
  String   sFlags;
  String   sBugs;
  float    nBogoMips;
  struct
  {
    int phys;
    int virt;
  } addrSz;
} ParsedCpuInfo;

typedef struct StMemoryMeasure
{
  unsigned value;
  String   unit;
} MemoryMeasure;

typedef struct StParsedMemoryInfo
{
  MemoryMeasure tMemTotal;
  MemoryMeasure tMemFree;
  MemoryMeasure tMemAvailable;
  MemoryMeasure tSwapTotal;
  MemoryMeasure tSwapFree;
} ParsedMemoryInfo;

typedef struct StLastCpuStatus
{
  uint64_t lastTotalUser;
  uint64_t lastTotalUserLow;
  uint64_t lastTotalSys;
  uint64_t lastTotalIdle;
} LastCpuStatus;

YukiSystem::YukiSystem()
    : m_tCpuInfo(),
      m_tMemInfo(),
      m_bReady(),
      m_pTimerUpdate(),
      m_tActivityInfo()
{
  // Initialize information of system, cpus, memories
#if defined(WIN32) || defined(_WIN32)
  this->_InitInformationsWin32();
  this->_InitPDH();
#endif
#if defined(linux) || defined(__linux) || defined(__linux__)
  this->_InitInformationLinux();
#endif

  m_tActivityInfo.cpuLoads.resize(this->m_tCpuInfo.numberOfCores);

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

  info->memoryUsed = memstat.ullTotalPhys - memstat.ullAvailPhys;

  // Get memory used by this process
  PROCESS_MEMORY_COUNTERS_EX pmc;
  GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*) &pmc, sizeof(pmc));
  info->memoryUsedByProc = pmc.WorkingSetSize;
#elif defined(linux) || defined(__linux) || defined(__linux__)
  struct sysinfo si;
  sysinfo(&si);

  m_tActivityInfo.memoryUsed = (si.totalram - si.freeram) * si.mem_unit;

  FILE* file = fopen("/proc/self/status", "r");
  char  line[128];
  while (fgets(line, 128, file) != NULL)
  {
    if (strncmp(line, "VmRSS:", 6) == 0)
    {
      int         i = strlen(line);
      const char* p = line;
      while (*p < '0' || *p > '9')
        p++;
      line[i - 3] = '\0';

      m_tActivityInfo.memoryUsedByProc = atoi(p);
      break;
    }
  }
  fclose(file);

  m_tActivityInfo.memoryUsedByProc *= si.mem_unit;
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
#elif defined(linux) || defined(__linux) || defined(__linux__)

  // Zero index is average cpu load value
  static bool                  isInited   = false;
  static uint32_t              statArrLen = this->GetCpuInformation().numberOfCores + 1;
  static Vector<LastCpuStatus> lastStatus(statArrLen, LastCpuStatus{});

  FILE* file;
  int   cpuid;


  file = std::fopen("/proc/stat", "r");

  // Initialize value if it has not been initialized
  cpuid = 0;
  if (!isInited)
  {
    while (cpuid < statArrLen && !std::feof(file))
    {
      std::fscanf(file, "%*s %lu %lu %lu %lu",
          &lastStatus[cpuid].lastTotalUser,
          &lastStatus[cpuid].lastTotalUserLow,
          &lastStatus[cpuid].lastTotalSys,
          &lastStatus[cpuid].lastTotalIdle);

      ++cpuid;
    }

    isInited = true;
  }

  cpuid = 0;
  while (cpuid < statArrLen && !std::feof(file))
  {
    float    percent;
    uint64_t totalUser    = 0,
             totalUserLow = 0,
             totalSys     = 0,
             totalIdle    = 0,
             total        = 0;

    std::fscanf(file, "%*s %lu %lu %lu %lu",
        &totalUser,
        &totalUserLow,
        &totalSys,
        &totalIdle);

    // Overflow detection. Just skip this value.
    bool dataFailed = totalUser < lastStatus[cpuid].lastTotalUser ||
                      totalUserLow < lastStatus[cpuid].lastTotalUserLow ||
                      totalSys < lastStatus[cpuid].lastTotalSys ||
                      totalIdle < lastStatus[cpuid].lastTotalIdle;

    if (dataFailed)
    {
      percent = -1.0;
    }
    else
    {
      total = (totalUser - lastStatus[cpuid].lastTotalUser) +
              (totalUserLow - lastStatus[cpuid].lastTotalUserLow) +
              (totalSys - lastStatus[cpuid].lastTotalSys);
      percent = total;
      total += totalIdle - lastStatus[cpuid].lastTotalIdle;
      percent /= total;
      percent *= 100;
    }

    lastStatus[cpuid].lastTotalUser    = totalUser;
    lastStatus[cpuid].lastTotalUserLow = totalUserLow;
    lastStatus[cpuid].lastTotalSys     = totalSys;
    lastStatus[cpuid].lastTotalIdle    = totalIdle;

    if (!cpuid)
    {
      m_tActivityInfo.avgCpuLoad = percent;
    }
    else
    {
      m_tActivityInfo.cpuLoads[cpuid - 1] = percent;
    }

    ++cpuid;
  }


  fclose(file);
#endif
}

#if defined(WIN32) || defined(_WIN32)

void parse_cpu_info(CpuInformation& info)
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

  info.brand = fmt::format("{}", cpuBrandString);

  SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);

  info.numberOfCores = systemInfo.dwNumberOfProcessors;
  info.architecture  = (ProcessorArchitecture) systemInfo.wProcessorArchitecture;
}

void parse_mem_info(MemoryInformation& info)
{

  MEMORYSTATUSEX memstat;
  GlobalMemoryStatusEx(&memstat);

  info.memSize  = memstat.dwLength;
  info.pageSize = memstat.ullTotalPageFile;
}

void YukiSystem::_InitInformationsWin32()
{
  parse_cpu_info(m_tCpuInfo);
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

#if defined(linux) || defined(__linux) || defined(__linux__)

void YukiSystem::_InitInformationLinux()
{
  this->_ProcessCpuInfoFile();
  this->_ProcessMemInfoFile();
}

void parse_line_to_tokens(String& line, Vector<String>& tokens)
{
  char* token = std::strtok(const_cast<char*>(line.c_str()), "\t:");
  while (token)
  {
    tokens.emplace_back(token);
    TrimString(tokens[tokens.size() - 1]);
    token = std::strtok(nullptr, "\t:");
  }
}

void parse_cpuinfo_tokens(ParsedCpuInfo& info, Vector<String>& propLine)
{
  if (propLine[0] == "processor")
  {
    info.nId = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "vendor_id")
  {
    info.sVendor = propLine[1];
    return;
  }

  if (propLine[0] == "cpu family")
  {
    info.nFamilyId = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "model")
  {
    info.nModelId = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "model name")
  {
    info.sCpuName = propLine[1];
    return;
  }

  if (propLine[0] == "stepping")
  {
    info.nStepping = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "microcode")
  {
    sscanf(propLine[1].c_str(), "%x", &info.nMicroCode);
    return;
  }

  if (propLine[0] == "cpu MHz")
  {
    info.nClockSpd = std::stof(propLine[1]);
    return;
  }

  if (propLine[0] == "cache size")
  {
    StringStream ss{propLine[1], std::ios::in};
    ss >> info.szCacheSize >> info.sCacheSizeUnit;
    return;
  }

  if (propLine[0] == "physical id")
  {
    info.nPhysicalCoreId = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "siblings")
  {
    info.nSiblings = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "core id")
  {
    info.nCoreId = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "cpu cores")
  {
    info.nCoresCount = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "apicid")
  {
    info.nApicId = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "initial apicid")
  {
    info.nInitialApicID = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "fpu")
  {
    info.bFpu = propLine[1] == "yes";
    return;
  }

  if (propLine[0] == "fpu exception")
  {
    info.bFpuException = propLine[1] == "yes";
    return;
  }

  if (propLine[0] == "cpuid level")
  {
    info.nCpuIdLevel = std::stol(propLine[1]);
    return;
  }

  if (propLine[0] == "wp")
  {
    info.bWp = propLine[1] == "yes";
    return;
  }

  if (propLine[0] == "flags")
  {
    info.sFlags = propLine[1];
    return;
  }

  if (propLine[0] == "bugs")
  {
    info.sBugs = propLine[1];
    return;
  }

  if (propLine[0] == "bogomips")
  {
    info.nBogoMips = std::stof(propLine[1]);
    return;
  }

  if (propLine[0] == "address sizes")
  {
    std::sscanf(propLine[1].c_str(), "%u %*s %*s %u %*s %*s", &info.addrSz.phys, &info.addrSz.virt);
  }
}

void parse_cpuinfo_toarray(
    Vector<ParsedCpuInfo>& infos,
    unsigned&              physCoreCount,
    unsigned&              logicalCoreCount)
{
  bool willCreateInfo = true;

  InputFileStream istream;
  istream.open("/proc/cpuinfo", std::ios::in);

  if (!istream.is_open() || !istream.good())
  {
    Core::GetYukiApp()
        ->GetLogger()
        ->PushErrorMessage("File \"/proc/cpuinfo\" Can't be opened, skipping read information");
    return;
  }

  while (!istream.eof())
  {
    if (willCreateInfo)
    {
      infos.emplace_back();
      willCreateInfo = false;
    }
    AutoType& crrInfo = infos[infos.size() - 1];
    String    line;
    std::getline(istream, line);

    Vector<String> tokens;
    tokens.reserve(2);

    parse_line_to_tokens(line, tokens);

    if (tokens.size() < 2)
    {
      willCreateInfo = true;
      continue;
    }

    parse_cpuinfo_tokens(crrInfo, tokens);
  }

  logicalCoreCount = infos.size();

  istream.close();
}

void YukiSystem::_ProcessCpuInfoFile()
{
  // Get cpu infos
  Vector<ParsedCpuInfo> infos;
  unsigned              physCoreCount    = 0;
  unsigned              logicalCoreCount = 0;
  parse_cpuinfo_toarray(infos, physCoreCount, logicalCoreCount);

  m_tCpuInfo.brand         = infos[0].sCpuName;
  m_tCpuInfo.numberOfCores = logicalCoreCount;

  AutoType findAmd64Flags = infos[0].sFlags.find("lm");
  m_tCpuInfo.architecture = (findAmd64Flags != std::string::npos
                                 ? ProcessorArchitecture::AMD64
                                 : ProcessorArchitecture::X86);
}

void YukiSystem::_ProcessMemInfoFile()
{
  struct sysinfo si;
  sysinfo(&si);

  m_tMemInfo.memSize  = si.totalram * si.mem_unit;
  m_tMemInfo.pageSize = si.totalswap * si.mem_unit;
}

#endif

} // namespace Yuki::Utils
