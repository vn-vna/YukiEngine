/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

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
  Map<String, YukiInpKeyboardCallback>         m_mpKeyCallbacksPool;
  Map<String, YukiInpCursorCallback>           m_mpCursorCallbacksPool;
  Array<KeyStatus, (int) KeyCode::KEY_LAST + 1> m_tKeyStatuses;
  MouseStatus                                   m_tCrrMouseStatus;
  MouseStatus                                   m_tPrevMouseStatus;
  MouseLock                                     m_tLockMouse;

public:
  YukiInpControl();
  ~YukiInpControl() override;

  void AddKeyboardInputCallback(const String& name, const YukiInpKeyboardCallback& pcallback) override;
  void AddCursorInputCallback(const String& name, const YukiInpCursorCallback& pcallback) override;
  void RemoveCursorInputCallback(const String& name) override;
  void RemoveKeyboardInputCallback(const String& name) override;
  void ExecuteKeyCallbacks(int key, int scancode, int action, int modifiers) override;
  void ExecuteCursorPosCallback(int x, int y) override;
  void LockMouse(int x, int y) override;
  void UnlockMouse() override;

  StKeyStatus& GetKeyStatus(const KeyCode& keyCode) override;
  MouseStatus& GetMouseStatus() override;
  Vec2F        GetMousePosition() override;
  Vec2F        GetMouseVelocity() override;
  int          GetKeyHorizontalAxis() override;
  int          GetKeyVerticalAxis() override;
  bool         IsMouseLocked() override;

  void Create() override;
  void Destroy() override;
};

} // namespace Yuki::Core