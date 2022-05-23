/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"

namespace Yuki::Utils
{

enum class ProcessorArchitecture
{
#if defined(WIN32) || defined(_WIN32)
  /// x64 architecture for intel or amd cpus
  AMD64   = PROCESSOR_ARCHITECTURE_AMD64,
  /// arm architecture
  ARM     = PROCESSOR_ARCHITECTURE_ARM,
  /// arm64 architecture
  ARM64   = PROCESSOR_ARCHITECTURE_ARM64,
  /// Intel itanium-based
  IA64    = PROCESSOR_ARCHITECTURE_IA64,
  /// x86
  X86     = PROCESSOR_ARCHITECTURE_INTEL,
  UNKNOWN = PROCESSOR_ARCHITECTURE_UNKNOWN
#elif defined(linux) || defined(__linux)
  AMD64,
  X86
#endif
};

/// Current system resource info
typedef struct StResourceActivityInfo
{
  float         avgCpuLoad;
  Vector<float> cpuLoads;
  size_t        memoryUsed;
  size_t        memoryUsedByProc;
} ResourceActivityInfo;

typedef struct StCpuInfo
{
  String                brand;
  ProcessorArchitecture architecture;
  unsigned              numberOfCores;
} CpuInformation, ProcessorInformation;

typedef struct StMemoryInfo
{
  size_t memSize;
  size_t pageSize;
} MemoryInformation;

typedef struct StSysInfo
{
  String computerName;
  String brandName;
} SysInfo;

class IYukiSystem
{
public:
  virtual const CpuInformation&       GetCpuInformation()       = 0;
  virtual const MemoryInformation&    GetMemoryInformation()    = 0;
  /// Don't call this function too quickly, if you do that, you can get unexpected result
  virtual const ResourceActivityInfo& GetResourceActivityInfo() = 0;
};

SharedPtr<IYukiSystem> GetYukiSystemController();

} // namespace Yuki::Utils
