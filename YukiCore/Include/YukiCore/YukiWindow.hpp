/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

#include <glm/vec2.hpp>

#define YUKI_DEFAULT_WINDOW_WIDTH  1366
#define YUKI_DEFAULT_WINDOW_HEIGHT 768
#define YUKI_DEFAULT_WINDOW_TITLE  "Window"
#define YUKI_WINDOW_SAMPLES        4

namespace Yuki::Core
{

class IYukiWindow : virtual public IYukiObject
{
public:
  virtual void        ShowWindow()                   = 0;
  virtual void        HideWindow()                   = 0;
  virtual void        IconfyWindow()                 = 0;
  virtual void        SetSize(int width, int height) = 0;
  virtual void        SetPosition(int wx, int wy)    = 0;
  virtual void        SetCursorPos(int cx, int cy)   = 0;
  virtual void        SetTitle(const String& title)  = 0;
  virtual bool        ShouldClose()                  = 0;
  virtual Vec2F       GetWindowSize()                = 0;
  virtual GLFWwindow* GetGLFWWindow()                = 0;
};

class IYukiOffScreenContext : virtual public IYukiObject
{
};

SharedPtr<IYukiWindow> CreateNewWindow();

} // namespace Yuki::Core
