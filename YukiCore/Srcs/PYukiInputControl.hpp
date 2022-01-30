#pragma once

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