#pragma once

#include "YukiCore/YukiVE.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Core
{

extern bool YUKIAPI g_bGLFWInited;

class YUKIAPI IYukiWindow : public IYukiObject
{
public:
  IYukiWindow()          = default;
  virtual ~IYukiWindow() = default;

  virtual void        ShowWindow()                                 = 0;
  virtual void        HideWindow()                                 = 0;
  virtual void        SetSize(const int& width, const int& height) = 0;
  virtual void        SetPosition(const int& wx, const int& wy)    = 0;
  virtual void        SetCursoPos(const int& cx, const int& cy)    = 0;
  virtual void        SetTitle(const AsciiString& title)           = 0;
  virtual void        SetTitle(const String& title)                = 0;
  virtual bool        ShouldClose()                                = 0;
  virtual HWND        GetWindowHandler()                           = 0;
  virtual GLFWwindow* GetGLFWWindow()                              = 0;
};

class YUKIAPI YukiWindow : public IYukiWindow
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
  HWND        GetWindowHandler() override;
  GLFWwindow* GetGLFWWindow() override;

  void Create() override;
  void Awake() override;
  void Update() override;
  void Render() override;
  void Destroy() override;

  static SharedPtr<IYukiWindow> CreateNewWindow();
};

} // namespace Yuki::Core