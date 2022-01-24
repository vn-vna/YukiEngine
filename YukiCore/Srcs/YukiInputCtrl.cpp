#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"

namespace Yuki::Core
{

class YukiInpControl : public IYukiInpControl
{
protected:
  std::map<String, SharedPtr<IYukiInpKeyboardCallback>> m_mpKeyCallbacksPool;
  std::map<String, SharedPtr<IYukiInpCursorCallback>>   m_mpCursorCallbacksPool;

public:
  YukiInpControl();
  virtual ~YukiInpControl() = default;

  void AddCursorInputCallback(const String& name, SharedPtr<IYukiInpCursorCallback>& pcallback) override;
  void AddKeyboardInputCallback(const String& name, SharedPtr<IYukiInpKeyboardCallback>& pcallback) override;
  void ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers) override;
  void ExecuteCursorPosCallback(int x, int y) override;

};

} // namespace Yuki::Core

namespace Yuki::Core
{

YukiInpControl::YukiInpControl()
    : m_mpKeyCallbacksPool{},
      m_mpCursorCallbacksPool{}
{}

void YukiInpControl::AddCursorInputCallback(const String& name, SharedPtr<IYukiInpCursorCallback>& pcallback)
{
  if (m_mpCursorCallbacksPool.find(name) != m_mpCursorCallbacksPool.end())
  {
    THROW_YUKI_ERROR(Debug::YukiInpCtrlInsertCallbackExistsError);
  }
  m_mpCursorCallbacksPool.emplace(name, pcallback);
}

void YukiInpControl::AddKeyboardInputCallback(const String& name, SharedPtr<IYukiInpKeyboardCallback>& pcallback)
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
    if (!callback.second.get())
    {
      THROW_YUKI_ERROR(Debug::YukiInpCtrlInvokeUndefinedCallbackError);
    }
    callback.second->invoke(key, scancode, action, modifiers);
  }
}

void YukiInpControl::ExecuteCursorPosCallback(int x, int y)
{
  for (const auto& callback : m_mpCursorCallbacksPool)
  {
    if (!callback.second.get())
    {
      THROW_YUKI_ERROR(Debug::YukiInpCtrlInvokeUndefinedCallbackError);
    }
    callback.second->invoke(x, y);
  }
}

SharedPtr<IYukiInpControl> CreateNewInputControl()
{
  return {(IYukiInpControl*) new YukiInpControl(), [](IYukiInpControl* p) { delete p; }};
}

} // namespace Yuki::Core