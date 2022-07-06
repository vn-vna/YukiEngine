/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Graphics.hpp"

#include "PObjects.hpp"

namespace Yuki::Core
{

class YukiGfxControl final : virtual public IYukiGfxControl,
                             virtual public YukiObject
{
public:
  YukiGfxControl();
  ~YukiGfxControl() override;

  void EnableAttribute(OpenGLAttribute attrib, bool cond = true) override;
  void DisableAttribute(OpenGLAttribute attrib, bool cond = true) override;
  void SetAttributeStatus(OpenGLAttribute attrib, bool status) override;

  void Create() override;
  void Awake() override;
  void Render() override;
  void Destroy() override;
};

} // namespace Yuki::Core
