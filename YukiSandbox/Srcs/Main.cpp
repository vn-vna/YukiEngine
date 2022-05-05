#include <YukiCore/YukiApplication.hpp>
#include <YukiComp/YukiCamera.hpp>
#include <YukiComp/YukiScene.hpp>

#include "TestEntity.hpp"
#include "CameraController.hpp"


int main(int, char**)
{

  AutoType yukiApp       = Yuki::Core::CreateYukiApp();
  AutoType camera        = Yuki::Comp::CreateYukiCamera();
  AutoType scene         = Yuki::Comp::CreateYukiScene();
  AutoType enTT1         = Yuki::Utils::CreateEntity<TestEntity>("test_1");
  AutoType cameraControl = CameraController::GetInstance();

  scene->SetCamera(camera);
  scene->AddEntity(enTT1);
  scene->AddEntity(cameraControl);

  yukiApp->SetCurrentScene(scene);

  yukiApp->RunApp();

  return 0;
}