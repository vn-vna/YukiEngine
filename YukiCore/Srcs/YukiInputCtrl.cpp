#include "YukiCore/YukiPCH.hpp"

#include "PYukiInputControl.hpp"

namespace Yuki::Core
{

YukiInpControl::YukiInpControl()
    : m_mpKeyCallbacksPool{},
      m_mpCursorCallbacksPool{}
{}

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
  for (const auto& callback : m_mpCursorCallbacksPool)
  {
    if (!callback.second)
    {
      THROW_YUKI_ERROR(Debug::YukiInpCtrlInvokeUndefinedCallbackError);
    }
    callback.second(x, y);
  }
}

SharedPtr<IYukiInpControl> CreateNewInputControl()
{
  return {(IYukiInpControl*) new YukiInpControl(), std::default_delete<IYukiInpControl>()};
}

} // namespace Yuki::Core