#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Core
{

class YUKIAPI IYukiInpCursorCallback
{
public:
    virtual void invoke(int x, int y) = 0;
};

class YUKIAPI IYukiInpKeyboardCallback
{
public:
    virtual void invoke(const int& key, const int& scancode, const int& action, const int& modifier) = 0;
};

class YUKIAPI IYukiInpControl : public IYukiObject
{
public:
    virtual void AddCursorInputCallback(const String& name, SharedPtr<IYukiInpCursorCallback>& pcallback)     = 0;
    virtual void AddKeyboardInputCallback(const String& name, SharedPtr<IYukiInpKeyboardCallback>& pcallback) = 0;
    virtual void ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers)                        = 0;
    virtual void ExecuteCursorPosCallback(int x, int y)                                                       = 0;
};

SharedPtr<IYukiInpControl> CreateNewInputControl();

} // namespace Yuki::Core