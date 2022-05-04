/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiGraphics.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

class YukiGfxControl final : virtual public IYukiGfxControl,
                             virtual public YukiObject
{
public:
  YukiGfxControl();
  ~YukiGfxControl() override;

  void Create() override;
  void Awake() override;
  void Render() override;
  void Destroy() override;
};

} // namespace Yuki::Core