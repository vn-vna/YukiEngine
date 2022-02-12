#pragma once

#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Core
{

class YukiGfxControl : public IYukiGfxControl
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