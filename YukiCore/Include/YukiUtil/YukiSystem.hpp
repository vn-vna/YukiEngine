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
  // x64 archivetecture for intel or amd cpus
  AMD64   = PROCESSOR_ARCHITECTURE_AMD64,
  // arm archivetecture
  ARM     = PROCESSOR_ARCHITECTURE_ARM,
  // arm64 archivetecture
  ARM64   = PROCESSOR_ARCHITECTURE_ARM64,
  // Intel itanium-based
  IA64    = PROCESSOR_ARCHITECTURE_IA64,
  // x86
  X86     = PROCESSOR_ARCHITECTURE_INTEL,
  UNKNOWN = PROCESSOR_ARCHITECTURE_UNKNOWN
};

typedef struct StCpuInfo
{
  String                brand;
  ProcessorArchitecture archivetecture;
  unsigned              numberOfCores;
  unsigned long long    activeProcessorMask;
} CpuInformation, ProcessorInformation;

typedef struct StMemoryInfo
{
  String brand;
  size_t memSize;
  size_t pageSize;
  void*  minimumApplicationAddress;
  void*  lpMaximumApplicationAddress;
} MemoryInformation;

typedef struct StSysinfo
{
  String computerName;
  String brandName;
};

class YUKIAPI IYukiSystem
{
public:
  virtual CpuInformation&    GetCpuInformation()    = 0;
  virtual MemoryInformation& GetMemoryInformation() = 0;
};

SharedPtr<IYukiSystem> YUKIAPI GetYukiSystemController();

} // namespace Yuki::Utils