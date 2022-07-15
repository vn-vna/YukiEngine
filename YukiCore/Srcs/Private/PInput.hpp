/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/Input.hpp"
#include "YukiDebug/Errors.hpp"

#include "PObjects.hpp"

#define YUKI_MAX_KEYARRLEN (int) KeyCode::KEY_LAST + 1

namespace Yuki::Core
{

class YukiInpControl final : virtual public IInput,
                             virtual public YukiObject
{
public:
  YukiInpControl();
  ~YukiInpControl() override;

  void
       AddKeyboardInputCallback(const String&                  name,
                                const YukiInpKeyboardCallback& pcallback) override;
  void AddCursorInputCallback(const String&                name,
                              const YukiInpCursorCallback& pcallback) override;
  void RemoveCursorInputCallback(const String& name) override;
  void RemoveKeyboardInputCallback(const String& name) override;
  void ExecuteKeyCallbacks(int key, int scancode, int action,
                           int modifiers) override;
  void ExecuteCursorPosCallback(int x, int y) override;

  void SetCursorStandardStyle(const StandardCursorType& type) override;

  void LockMouse(int x, int y) override;
  void UnlockMouse() override;
  void HideMouse() override;
  void UnhideMouse() override;

  StKeyStatus& GetKeyStatus(const KeyCode& keyCode) override;
  MouseStatus& GetMouseStatus() override;
  Vec2F        GetMousePosition() override;
  Vec2F        GetMouseVelocity() override;
  int          GetKeyHorizontalAxis() override;
  int          GetKeyVerticalAxis() override;
  bool         IsMouseLocked() override;

  void Create() override;
  void Destroy() override;

private:
  Map<String, YukiInpKeyboardCallback> m_mpKeyCallbacksPool;
  Map<String, YukiInpCursorCallback>   m_mpCursorCallbacksPool;
  Array<KeyStatus, YUKI_MAX_KEYARRLEN> m_tKeyStatuses;
  MouseStatus                          m_tCrrMouseStatus;
  MouseStatus                          m_tPrevMouseStatus;
  MouseLock                            m_tLockMouse;
  bool                                 m_bMouseHide;
  GLFWcursor*                          m_pCursor;
};

} // namespace Yuki::Core
