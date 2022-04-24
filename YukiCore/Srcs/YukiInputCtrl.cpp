#include "YukiCore/YukiPCH.hpp"

#include "PYukiInputControl.hpp"

namespace Yuki::Core
{

YukiInpControl::YukiInpControl()
    : m_mpKeyCallbacksPool{},
      m_mpCursorCallbacksPool{}
{
  ZeroMemory(m_tKeyStatuses, (int) KeyCode::KEY_LAST);
  for (int i = 0; i < (int) KeyCode::KEY_LAST; ++i)
  {
    m_tKeyStatuses[i].code      = (KeyCode) i;
    m_tKeyStatuses[i].modifiers = 0;
    m_tKeyStatuses[i].scancode  = 0;
    m_tKeyStatuses[i].state     = KeyState::RELEASE;
  }
}

YukiInpControl::~YukiInpControl() = default;

void YukiInpControl::AddCursorInputCallback(const String& name, const YukiInpCursorCallbackT& pcallback)
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

void YukiInpControl::AddKeyboardInputCallback(const String& name, const YukiInpKeyboardCallbackT& pcallback)
{
  if (m_mpKeyCallbacksPool.find(name) != m_mpKeyCallbacksPool.end())
  {
    THROW_YUKI_ERROR(InpCtrlInsertCallbackExistsError);
  }
  m_mpKeyCallbacksPool.emplace(name, pcallback);
}

void YukiInpControl::ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers)
{
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

StKeyStatus& YukiInpControl::GetKeyStatus(const KeyCode& keyCode)
{
  return m_tKeyStatuses[(int) keyCode];
}

SharedPtr<IYukiInpControl> CreateNewInputControl()
{
  return CreateInterfaceInstance<IYukiInpControl, YukiInpControl>();
}

} // namespace Yuki::Core