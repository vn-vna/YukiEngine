/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#include "YukiCore/YukiObject.hpp"
#include "YukiUtil/YukiSystem.hpp"
#include "YukiUtil/YukiChrono.hpp"

#if defined(WIN32) | defined(_WIN32)
#  include <Pdh.h>
#  include <Psapi.h>
#endif

namespace Yuki::Utils
{

using Chrono::IYukiTimer;

class YukiSystem : virtual public IYukiSystem
{
private:
#if defined(WIN32) || defined(_WIN32)
  PDH_HQUERY   m_hPdhQuery;
  PDH_HCOUNTER m_hCounterCPU;
#endif
  CpuInformation        m_tCpuInfo;
  MemoryInformation     m_tMemInfo;
  ResourceActivityInfo  m_tActivityInfo;
  SharedPtr<IYukiTimer> m_pTimerUpdate;
  bool                  m_bReady;

public:
  YukiSystem();
  virtual ~YukiSystem();

  const CpuInformation&       GetCpuInformation() override;
  const MemoryInformation&    GetMemoryInformation() override;
  const ResourceActivityInfo& GetResourceActivityInfo() override;

private:
  void _GetMemoryActivity(ResourceActivityInfo* info);
  void _GetCpuActivity(ResourceActivityInfo* info);

#if defined(WIN32) || defined(_WIN32)
  void _InitInformationsWin32();
  void _InitPDH();
  void _DestroyPDH();
#endif
};

} // namespace Yuki::Utils