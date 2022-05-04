#include <YukiUtil/YukiUtilities.hpp>

namespace Yuki::Utils
{

using namespace Yuki::Core;

bool isKeyPressed(KeyCode key)
{
  return GetYukiApp()->GetInputController()->GetKeyStatus(key).state == KeyState::PRESS;
}

bool isKeyRepeated(KeyCode key)
{
  return GetYukiApp()->GetInputController()->GetKeyStatus(key).state == KeyState::REPEAT;
}

bool isKeyReleased(KeyCode key)
{
  return GetYukiApp()->GetInputController()->GetKeyStatus(key).state == KeyState::RELEASE;
}

void moveCameraRight(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(speed * camera->GetCameraHorizontalAxis());
}

void moveCameraLeft(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(-speed * camera->GetCameraHorizontalAxis());
}

void moveCameraFront(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(speed * camera->GetCameraVerticalAxis());
}

void moveCameraBack(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(-speed * camera->GetCameraVerticalAxis());
}

void moveCameraUp(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(speed * camera->GetCameraTopAxis());
}

void moveCameraDown(SharedPtr<IYukiCamera> camera, float speed)
{
  camera->MoveCamera(-speed * camera->GetCameraTopAxis());
}

} // namespace Yuki::Utils