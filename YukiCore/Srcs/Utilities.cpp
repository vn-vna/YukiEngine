#include <YukiUtil/YukiUtilities.hpp>

namespace Yuki::Utils
{

bool IsKeyPressed(KeyCode key)
{
  return GetYukiApp()->GetInputController()->GetKeyStatus(key).state == KeyState::PRESS;
}

bool IsKeyRepeated(KeyCode key)
{
  return GetYukiApp()->GetInputController()->GetKeyStatus(key).state == KeyState::REPEAT;
}

bool IsKeyReleased(KeyCode key)
{
  return GetYukiApp()->GetInputController()->GetKeyStatus(key).state == KeyState::RELEASE;
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