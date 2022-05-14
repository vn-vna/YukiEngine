#include <YukiCore/YukiApplication.hpp>
#include <YukiComp/YukiCamera.hpp>
#include <YukiComp/YukiScene.hpp>
#include <YukiUtil/YukiChrono.hpp>
#include <YukiCore/YukiThreadPool.hpp>
#include <YukiUtil/YukiSystem.hpp>

#include "TestEntity.hpp"
#include "CameraController.hpp"
#include "SystemControl.hpp"

int main(int, char**)
{

  AutoType sysctrl = Yuki::Utils::GetYukiSystemController();

  AutoType yukiApp       = Yuki::Core::CreateYukiApp();
  AutoType camera        = Yuki::Comp::CreateYukiCamera();
  AutoType scene         = Yuki::Comp::CreateYukiScene();
  AutoType enTT1         = TestEntity::GetInstance();
  AutoType cameraControl = CameraController::GetInstance();
  AutoType sysCtrl       = SystemControl::GetInstance();

  scene->SetCamera(camera);
  scene->AddEntity(enTT1);
  scene->AddEntity(cameraControl);
  scene->AddEntity(sysCtrl);

  yukiApp->SetCurrentScene(scene);

  yukiApp->RunApp();

  return 0;
}