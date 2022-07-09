/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#include "POGLTexture.hpp"
#include "YukiCore/Objects.hpp"
#include "YukiCore/Headers.hpp"
#include "YukiUtil/System.hpp"
#include "YukiUtil/Chrono.hpp"

#include "PObjects.hpp"

namespace Yuki::Utils
{

using Chrono::IYukiTimer;
using Core::YukiObject;

class YukiSystem : virtual public IYukiSystem,
                   virtual public YukiObject
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

  void Create() override;
  void Destroy() override;

private:
  void _GetMemoryActivity(ResourceActivityInfo* info);
  void _GetCpuActivity(ResourceActivityInfo* info);

#if defined(IS_WINDOWS)
  void _InitInformationsWin32();
  void _InitPDH();
  void _DestroyPDH();
#elif defined(IS_LINUX)
  void _InitInformationLinux();
  void _ProcessCpuInfoFile();
  void _ProcessMemInfoFile();
#endif
};

} // namespace Yuki::Utils
