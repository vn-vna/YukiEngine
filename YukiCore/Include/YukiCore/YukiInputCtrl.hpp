#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Core
{

typedef std::function<void(int x, int y)> YukiInpCursorCallbackT;

typedef std::function<void(const int& key, const int& scancode, const int& action, const int& modifier)> YukiInpKeyboardCallbackT;

class YUKIAPI IYukiInpControl : public IYukiObject
{
public:
  virtual void AddCursorInputCallback(const String& name, const YukiInpCursorCallbackT& pcallback)     = 0;
  virtual void AddKeyboardInputCallback(const String& name, const YukiInpKeyboardCallbackT& pcallback) = 0;
  virtual void RemoveCursorInputCallback(const String& name)                                           = 0;
  virtual void RemoveKeyboardInputCallback(const String& name)                                         = 0;
  virtual void ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers)                   = 0;
  virtual void ExecuteCursorPosCallback(int x, int y)                                                  = 0;
};

SharedPtr<IYukiInpControl> CreateNewInputControl();

} // namespace Yuki::Core