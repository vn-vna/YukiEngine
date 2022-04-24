#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

#include <glm/vec2.hpp>

namespace Yuki::Core
{

extern bool YUKIAPI g_bGLFWInited;

class YUKIAPI IYukiWindow : virtual public IYukiObject
{
public:
  virtual void        ShowWindow()                   = 0;
  virtual void        HideWindow()                   = 0;
  virtual void        SetSize(int width, int height) = 0;
  virtual void        SetPosition(int wx, int wy)    = 0;
  virtual void        SetCursorPos(int cx, int cy)   = 0;
  virtual void        SetTitle(const String& title)  = 0;
  virtual bool        ShouldClose()                  = 0;
  virtual Vec2F       GetWindowSize()                = 0;
  virtual GLFWwindow* GetGLFWWindow()                = 0;
};

SharedPtr<IYukiWindow> CreateNewWindow();

} // namespace Yuki::Core