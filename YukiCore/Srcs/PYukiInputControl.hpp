#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

class YukiInpControl final : virtual public IYukiInpControl,
                             virtual public YukiObject
{
protected:
  Map<String, YukiInpKeyboardCallbackT> m_mpKeyCallbacksPool;
  Map<String, YukiInpCursorCallbackT>   m_mpCursorCallbacksPool;
  KeyStatus                             m_tKeyStatuses[(int) KeyCode::KEY_LAST + 1];

public:
  YukiInpControl();
  ~YukiInpControl() override;

  void AddKeyboardInputCallback(const String& name, const YukiInpKeyboardCallbackT& pcallback) override;
  void AddCursorInputCallback(const String& name, const YukiInpCursorCallbackT& pcallback) override;
  void RemoveCursorInputCallback(const String& name) override;
  void RemoveKeyboardInputCallback(const String& name) override;
  void ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers) override;
  void ExecuteCursorPosCallback(int x, int y) override;

  YUKI_NODISCARD StKeyStatus& GetKeyStatus(const KeyCode& keyCode) override;
};

} // namespace Yuki::Core