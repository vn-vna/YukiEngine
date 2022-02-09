#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"

namespace Yuki::Core
{

class YukiInpControl : public virtual IYukiInpControl
{
protected:
  std::map<String, YukiInpKeyboardCallbackT> m_mpKeyCallbacksPool;
  std::map<String, YukiInpCursorCallbackT>   m_mpCursorCallbacksPool;
  KeyStatus                                  m_tKeyStatuses[(int) KeyCode::KEY_LAST + 1];

public:
  YukiInpControl();
  virtual ~YukiInpControl() = default;

  void         AddKeyboardInputCallback(const String& name, const YukiInpKeyboardCallbackT& pcallback) override;
  void         AddCursorInputCallback(const String& name, const YukiInpCursorCallbackT& pcallback) override;
  void         RemoveCursorInputCallback(const String& name) override;
  void         RemoveKeyboardInputCallback(const String& name) override;
  void         ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers) override;
  void         ExecuteCursorPosCallback(int x, int y) override;
  StKeyStatus& GetKeyStatus(const KeyCode& keyCode) override;
};

} // namespace Yuki::Core