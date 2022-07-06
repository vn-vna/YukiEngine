#include "YukiCore/Headers.hpp"

#include "YukiUtil/Utilities.hpp"

const char* ws = " \t\n\r\f\v";

inline std::string& rtrim(std::string& s, const char* t = ws)
{
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

inline std::string& ltrim(std::string& s, const char* t = ws)
{
  s.erase(0, s.find_first_not_of(t));
  return s;
}

inline std::string& trim(std::string& s, const char* t = ws)
{
  return ltrim(rtrim(s, t), t);
}

namespace Yuki::Utils
{

String& TrimString(String& str)
{
  return trim(str);
}

String GetTrimmed(const String& str)
{
  String cpy = str;
  TrimString(cpy);
  return std::move(cpy);
}

bool IsKeyPressed(KeyCode key)
{
  return GetYukiApp()->GetInputController()->GetKeyStatus(key).state ==
         KeyState::PRESS;
}

bool IsKeyRepeated(KeyCode key)
{
  return GetYukiApp()->GetInputController()->GetKeyStatus(key).state ==
         KeyState::REPEAT;
}

bool IsKeyReleased(KeyCode key)
{
  return GetYukiApp()->GetInputController()->GetKeyStatus(key).state ==
         KeyState::RELEASE;
}

void MoveCameraRight(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(speed * camera->GetCameraHorizontalAxis());
}

void MoveCameraLeft(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(-speed * camera->GetCameraHorizontalAxis());
}

void MoveCameraFront(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(speed * camera->GetCameraVerticalAxis());
}

void MoveCameraBack(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(-speed * camera->GetCameraVerticalAxis());
}

void MoveCameraUp(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(speed * camera->GetCameraTopAxis());
}

void MoveCameraDown(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(-speed * camera->GetCameraTopAxis());
}

} // namespace Yuki::Utils
