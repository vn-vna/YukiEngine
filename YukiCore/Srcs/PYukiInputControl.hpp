#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"

namespace Yuki::Core
{

class YukiInpControl : public IYukiInpControl
{
protected:
  std::map<String, YukiInpKeyboardCallbackT> m_mpKeyCallbacksPool;
  std::map<String, YukiInpCursorCallbackT>   m_mpCursorCallbacksPool;

public:
  YukiInpControl();
  virtual ~YukiInpControl() = default;

  void AddKeyboardInputCallback(const String& name, const YukiInpKeyboardCallbackT& pcallback) override;
  void AddCursorInputCallback(const String& name, const YukiInpCursorCallbackT& pcallback) override;
  void RemoveCursorInputCallback(const String& name) override;
  void RemoveKeyboardInputCallback(const String& name) override;
  void ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers) override;
  void ExecuteCursorPosCallback(int x, int y) override;
};

} // namespace Yuki::Core