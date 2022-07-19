/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/WindowManager.hpp"

#include "PObjects.hpp"

namespace Yuki::Core
{

class YukiWindow final : virtual public IWindow,
                         virtual public YukiObject
{
public:
  YukiWindow();
  ~YukiWindow() override;

  void ShowWindow() override;
  void HideWindow() override;
  void IconfyWindow() override;
  void SetSize(int width, int height) override;
  void SetPosition(int wx, int wy) override;
  void SetCursorPos(int cx, int cy) override;
  void SetTitle(const String& title) override;

  bool        ShouldClose() override;
  Vec2F       GetWindowSize() override;
  GLFWwindow* GetGLFWWindow() override;

  void Create() override;
  void Awake() override;
  void Update() override;
  void Destroy() override;

private:
  GLFWwindow* m_pGLFWWindow;
};

} // namespace Yuki::Core

void initAndCheckGLFW();
void funcGLFWKeyCallback(
    GLFWwindow* pWindow, int key, int scancode, int action, int modifiers
);
