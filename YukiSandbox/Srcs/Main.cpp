#include <YukiCore/Application.hpp>
#include <YukiComp/Camera.hpp>
#include <YukiComp/Scene.hpp>
#include <YukiUtil/Chrono.hpp>
#include <YukiCore/ThreadPool.hpp>
#include <YukiUtil/System.hpp>

#include "TestEntity.hpp"
#include "CameraController.hpp"
#include "SystemControl.hpp"

int main(int, char**)
{
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