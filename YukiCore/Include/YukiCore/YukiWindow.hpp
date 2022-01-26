#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

#include <glm/vec2.hpp>

namespace Yuki::Core
{

extern bool YUKIAPI g_bGLFWInited;

class YUKIAPI IYukiWindow : public IYukiObject
{
public:
  virtual void        ShowWindow()                                 = 0;
  virtual void        HideWindow()                                 = 0;
  virtual void        SetSize(const int& width, const int& height) = 0;
  virtual void        SetPosition(const int& wx, const int& wy)    = 0;
  virtual void        SetCursoPos(const int& cx, const int& cy)    = 0;
  virtual void        SetTitle(const AsciiString& title)           = 0;
  virtual void        SetTitle(const String& title)                = 0;
  virtual bool        ShouldClose()                                = 0;
  virtual glm::vec2   GetWindowSize()                              = 0;
  virtual GLFWwindow* GetGLFWWindow()                              = 0;
};

SharedPtr<IYukiWindow> CreateNewWindow();

} // namespace Yuki::Core