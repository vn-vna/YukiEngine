#pragma once

#include "YukiCore/YukiVE.hpp"
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
  IYukiInpControl()          = default;
  virtual ~IYukiInpControl() = default;

  virtual void AddCursorInputCallback(const String& name, SharedPtr<IYukiInpCursorCallback>& pcallback)     = 0;
  virtual void AddKeyboardInputCallback(const String& name, SharedPtr<IYukiInpKeyboardCallback>& pcallback) = 0;
  virtual void ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers)                        = 0;
  virtual void ExecuteCursorPosCallback(int x, int y)                                                       = 0;
};


class YUKIAPI YukiInpControl : public IYukiInpControl
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

  static SharedPtr<IYukiInpControl> CreateNewInputControl();
};

} // namespace Yuki::Core