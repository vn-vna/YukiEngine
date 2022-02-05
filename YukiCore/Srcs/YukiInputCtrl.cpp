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

void YukiInpControl::AddCursorInputCallback(const String& name, const YukiInpCursorCallbackT& pcallback)
{
  if (m_mpCursorCallbacksPool.find(name) != m_mpCursorCallbacksPool.end())
  {
    THROW_YUKI_ERROR(Debug::YukiInpCtrlInsertCallbackExistsError);
  }
  m_mpCursorCallbacksPool.emplace(name, pcallback);
}

void YukiInpControl::RemoveCursorInputCallback(const String& name)
{
  if (m_mpCursorCallbacksPool.find(name) == m_mpCursorCallbacksPool.end())
  {
    THROW_YUKI_ERROR(Debug::YukiInpCtrlRemoveCallbackNExistsError);
  }
  m_mpCursorCallbacksPool.erase(name);
}

void YukiInpControl::RemoveKeyboardInputCallback(const String& name)
{
  if (m_mpKeyCallbacksPool.find(name) == m_mpKeyCallbacksPool.end())
  {
    THROW_YUKI_ERROR(Debug::YukiInpCtrlRemoveCallbackNExistsError);
  }
  m_mpKeyCallbacksPool.erase(name);
}

void YukiInpControl::AddKeyboardInputCallback(const String& name, const YukiInpKeyboardCallbackT& pcallback)
{
  if (m_mpKeyCallbacksPool.find(name) != m_mpKeyCallbacksPool.end())
  {
    THROW_YUKI_ERROR(Debug::YukiInpCtrlInsertCallbackExistsError);
  }
  m_mpKeyCallbacksPool.emplace(name, pcallback);
}

void YukiInpControl::ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers)
{
  if (key > (int) KeyCode::KEY_LAST)
  {
    THROW_YUKI_ERROR(Debug::YukiInpCtrlKeyCodeInvalidError);
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
      THROW_YUKI_ERROR(Debug::YukiInpCtrlInvokeUndefinedCallbackError);
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
      THROW_YUKI_ERROR(Debug::YukiInpCtrlInvokeUndefinedCallbackError);
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
  return {(IYukiInpControl*) new YukiInpControl(), std::default_delete<IYukiInpControl>()};
}

} // namespace Yuki::Core