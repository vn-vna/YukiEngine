#pragma once

#include "YukiCore/YukiGraphics.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

class YukiGfxControl : virtual public IYukiGfxControl,
                       virtual public YukiObject
{
public:
  YukiGfxControl();
  virtual ~YukiGfxControl();

  void Create() override;
  void Awake() override;
  void Render() override;
  void Destroy() override;
};

} // namespace Yuki::Core