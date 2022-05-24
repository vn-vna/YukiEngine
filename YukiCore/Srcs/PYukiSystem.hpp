/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#include "YukiCore/Srcs/PYukiOGLTexture.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiPCH.hpp"
#include "YukiUtil/YukiSystem.hpp"
#include "YukiUtil/YukiChrono.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Utils
{

using Core::YukiObject;
using Chrono::IYukiTimer;

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

#ifdef IS_WINDOWS
  void _InitInformationsWin32();
  void _InitPDH();
  void _DestroyPDH();
#elifdef IS_LINUX
  void _InitInformationLinux();
  void _ProcessCpuInfoFile();
  void _ProcessMemInfoFile();
#endif
};

} // namespace Yuki::Utils
