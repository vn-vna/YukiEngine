/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#include "YukiCore/YukiObject.hpp"
#include "YukiUtil/YukiSystem.hpp"

namespace Yuki::Utils
{

class YukiSystem : virtual public IYukiSystem
{
private:
  CpuInformation    m_tCpuInfo;
  MemoryInformation m_tMemInfo;

public:
  YukiSystem();
  virtual ~YukiSystem();

  CpuInformation&    GetCpuInformation() override;
  MemoryInformation& GetMemoryInformation() override;
};

} // namespace Yuki::Utils