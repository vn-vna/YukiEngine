#include <YukiCore/Application.hpp>
#include <YukiComp/Camera.hpp>
#include <YukiComp/Scene.hpp>
#include <YukiUtil/Chrono.hpp>
#include <YukiCore/ThreadPool.hpp>
#include <YukiUtil/System.hpp>

#include "TestEntity.hpp"
#include "CameraController.hpp"
#include "SystemControl.hpp"

//#define APPLY_MEMCHECK

using Yuki::Comp::CreateYukiCamera;
using Yuki::Comp::CreateYukiScene;
using Yuki::Core::CreateYukiApp;

int main(int, char**)
{
#if defined(IS_WINDOWS) && defined(APPLY_MEMCHECK)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetBreakAlloc(9554);
  _CrtSetBreakAlloc(9553);
  _CrtSetBreakAlloc(9552);
#endif

  AutoType yukiApp       = CreateYukiApp();
  AutoType camera        = CreateYukiCamera();
  AutoType scene         = CreateYukiScene();
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