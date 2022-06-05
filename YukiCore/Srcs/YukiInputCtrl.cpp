#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiWindow.hpp"

#include "PYukiInputControl.hpp"

namespace Yuki::Core
{

YukiInpControl::YukiInpControl()
    : m_mpKeyCallbacksPool(), m_mpCursorCallbacksPool(), m_tCrrMouseStatus(), m_tPrevMouseStatus(), m_tKeyStatuses(),
      m_tLockMouse(), m_bMouseHide(false), m_pCursor(nullptr)
{}

YukiInpControl::~YukiInpControl() = default;

void YukiInpControl::AddCursorInputCallback(const String& name, const YukiInpCursorCallback& pcallback)
{
  if (m_mpCursorCallbacksPool.find(name) != m_mpCursorCallbacksPool.end())
  {
    THROW_YUKI_ERROR(InpCtrlInsertCallbackExistsError);
  }
  m_mpCursorCallbacksPool.emplace(name, pcallback);
}

void YukiInpControl::RemoveCursorInputCallback(const String& name)
{
  if (m_mpCursorCallbacksPool.find(name) == m_mpCursorCallbacksPool.end())
  {
    THROW_YUKI_ERROR(InpCtrlRemoveCallbackNExistsError);
  }
  m_mpCursorCallbacksPool.erase(name);
}

void YukiInpControl::RemoveKeyboardInputCallback(const String& name)
{
  if (m_mpKeyCallbacksPool.find(name) == m_mpKeyCallbacksPool.end())
  {
    THROW_YUKI_ERROR(InpCtrlRemoveCallbackNExistsError);
  }
  m_mpKeyCallbacksPool.erase(name);
}

void YukiInpControl::AddKeyboardInputCallback(const String& name, const YukiInpKeyboardCallback& pcallback)
{
  if (m_mpKeyCallbacksPool.find(name) != m_mpKeyCallbacksPool.end())
  {
    THROW_YUKI_ERROR(InpCtrlInsertCallbackExistsError);
  }
  m_mpKeyCallbacksPool.emplace(name, pcallback);
}

void YukiInpControl::ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers)
{
  // Default callback
  if (key > (int) KeyCode::KEY_LAST)
  {
    THROW_YUKI_ERROR(InpCtrlKeyCodeInvalidError);
  }
  m_tKeyStatuses[key].state     = (KeyState) action;
  m_tKeyStatuses[key].modifiers = modifiers;
  m_tKeyStatuses[key].scancode  = scancode;

  if (m_mpKeyCallbacksPool.empty())
  {
    return;
  }
  for (const auto& callback : m_mpKeyCallbacksPool)
  {
    if (!callback.second)
    {
      THROW_YUKI_ERROR(InpCtrlInvokeUndefinedCallbackError);
    }
    callback.second(key, scancode, action, modifiers);
  }
}

void YukiInpControl::ExecuteCursorPosCallback(int x, int y)
{
  // Default callback
  m_tPrevMouseStatus = {m_tCrrMouseStatus.x, m_tCrrMouseStatus.y};
  m_tCrrMouseStatus  = {x, y, (float) x - m_tPrevMouseStatus.x, (float) y - m_tPrevMouseStatus.y};

  if (m_tLockMouse.lock)
  {
    Core::GetYukiApp()->GetWindow()->SetCursorPos(m_tLockMouse.lx, m_tLockMouse.ly);
  }

  if (m_mpCursorCallbacksPool.empty())
  {
    return;
  }
  for (const auto& callback : m_mpCursorCallbacksPool)
  {
    if (!callback.second)
    {
      THROW_YUKI_ERROR(InpCtrlInvokeUndefinedCallbackError);
    }
    callback.second(x, y);
  }
}

void YukiInpControl::SetCursorStandardStyle(const StandardCursorType& type)
{
  AutoType pPrevCursor = m_pCursor;
  AutoType pGLFWWindow = GetYukiApp()->GetWindow()->GetGLFWWindow();

  m_pCursor = glfwCreateStandardCursor((int) type);

  glfwSetCursor(pGLFWWindow, m_pCursor);

  if (pPrevCursor)
  {
    glfwDestroyCursor(pPrevCursor);
  }
}

void YukiInpControl::LockMouse(int x, int y) { m_tLockMouse = {x, y, true}; }

void YukiInpControl::UnlockMouse() { m_tLockMouse.lock = false; }

void YukiInpControl::HideMouse()
{
  if (!m_bMouseHide) {}
}

void YukiInpControl::UnhideMouse() {}

StKeyStatus& YukiInpControl::GetKeyStatus(const KeyCode& keyCode) { return m_tKeyStatuses[(int) keyCode]; }

MouseStatus& YukiInpControl::GetMouseStatus() { return m_tCrrMouseStatus; }

Vec2F YukiInpControl::GetMousePosition() { return {m_tCrrMouseStatus.x, m_tCrrMouseStatus.y}; }

Vec2F YukiInpControl::GetMouseVelocity() { return {m_tCrrMouseStatus.vx, m_tCrrMouseStatus.vy}; }

int YukiInpControl::GetKeyHorizontalAxis()
{
  if (GetKeyStatus(KeyCode::KEY_A).state != KeyState::RELEASE ||
      GetKeyStatus(KeyCode::KEY_LEFT).state != KeyState::RELEASE)
  {
    return -1;
  }
  if (GetKeyStatus(KeyCode::KEY_D).state != KeyState::RELEASE ||
      GetKeyStatus(KeyCode::KEY_RIGHT).state != KeyState::RELEASE)
  {
    return 1;
  }
  return 0;
}

int YukiInpControl::GetKeyVerticalAxis()
{
  if (GetKeyStatus(KeyCode::KEY_S).state != KeyState::RELEASE ||
      GetKeyStatus(KeyCode::KEY_DOWN).state != KeyState::RELEASE)
  {
    return -1;
  }
  if (GetKeyStatus(KeyCode::KEY_W).state != KeyState::RELEASE ||
      GetKeyStatus(KeyCode::KEY_UP).state != KeyState::RELEASE)
  {
    return 1;
  }
  return 0;
}

bool YukiInpControl::IsMouseLocked() { return m_tLockMouse.lock; }

void YukiInpControl::Create()
{
  for (int i = 0; i < (int) KeyCode::KEY_LAST; ++i)
  {
    m_tKeyStatuses[i].code      = (KeyCode) i;
    m_tKeyStatuses[i].modifiers = 0;
    m_tKeyStatuses[i].scancode  = 0;
    m_tKeyStatuses[i].state     = KeyState::RELEASE;
  }
}

void YukiInpControl::Destroy() {}

SharedPtr<IYukiInpControl> CreateNewInputControl()
{
  return CreateInterfaceInstance<IYukiInpControl, YukiInpControl>();
}

} // namespace Yuki::Core