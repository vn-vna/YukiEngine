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
  /// x64 archivetecture for intel or amd cpus
  AMD64   = PROCESSOR_ARCHITECTURE_AMD64,
  /// arm archivetecture
  ARM     = PROCESSOR_ARCHITECTURE_ARM,
  /// arm64 archivetecture
  ARM64   = PROCESSOR_ARCHITECTURE_ARM64,
  /// Intel itanium-based
  IA64    = PROCESSOR_ARCHITECTURE_IA64,
  /// x86
  X86     = PROCESSOR_ARCHITECTURE_INTEL,
  UNKNOWN = PROCESSOR_ARCHITECTURE_UNKNOWN
};

/// Current system resource info
typedef struct StResourceActivityInfo
{
  float         avgCpuLoad;
  Vector<float> cpuLoads;
  size_t        memoryUsed;
  size_t        memoryUsedByProc;
  size_t        virtmemUsed;
  size_t        virtmemUsedByProc;
} ResourceActivityInfo;

typedef struct StCpuInfo
{
  String                brand;
  ProcessorArchitecture archivetecture;
  unsigned              numberOfCores;
  size_t                activeProcessorMask;
} CpuInformation, ProcessorInformation;

typedef struct StMemoryInfo
{
  size_t virtmemSize;
  size_t memSize;
  size_t pageSize;
} MemoryInformation;

typedef struct StSysinfo
{
  String computerName;
  String brandName;
};

class YUKIAPI IYukiSystem
{
public:
  virtual const CpuInformation&      GetCpuInformation()       = 0;
  virtual const MemoryInformation&   GetMemoryInformation()    = 0;
  /// Don't call this function too quickly, if you do that, you can get unexpected result
  virtual const ResourceActivityInfo& GetResourceActivityInfo() = 0;
};

SharedPtr<IYukiSystem> YUKIAPI GetYukiSystemController();

} // namespace Yuki::Utils