#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiWindow.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiCore/YukiGraphics.hpp"

#define YUKI_DEFAULT_WINDOW_WIDTH  1366
#define YUKI_DEFAULT_WINDOW_HEIGHT 768
#define YUKI_DEFAULT_WINDOW_TITLE  "Window"
#define YUKI_WINDOW_SAMPLES        4

namespace Yuki::Core
{

class YukiWindow : public IYukiWindow
{
protected:
  GLFWwindow* m_pGLFWWindow;

public:
  YukiWindow();
  virtual ~YukiWindow();

  void        ShowWindow() override;
  void        HideWindow() override;
  void        SetSize(const int& width, const int& height) override;
  void        SetPosition(const int& wx, const int& wy) override;
  void        SetCursoPos(const int& cx, const int& cy) override;
  void        SetTitle(const AsciiString& title) override;
  void        SetTitle(const String& title) override;
  bool        ShouldClose() override;
  glm::vec2   GetWindowSize() override;
  GLFWwindow* GetGLFWWindow() override;

  void Create() override;
  void Awake() override;
  void Update() override;
  void Render() override;
  void Destroy() override;
};

} // namespace Yuki::Core

void funcGLFWKeyCallback(GLFWwindow* pwindow, int key, int scancode, int action, int modifiers);
void funcGLFWCursorCallback(GLFWwindow* window, double x, double y);
