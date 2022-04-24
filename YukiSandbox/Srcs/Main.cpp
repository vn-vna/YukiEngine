#include <YukiCore/YukiApplication.hpp>
#include <YukiComp/YukiCamera.hpp>
#include <YukiComp/YukiScene.hpp>

#include "TestEntity.hpp"

int main(int, char**)
{
  AutoType yukiApp = Yuki::Core::CreateYukiApp();
  AutoType camera  = Yuki::Comp::CreateYukiCamera();
  AutoType scene   = Yuki::Comp::CreateYukiScene();
  AutoType enTT1   = Yuki::Core::CreateInterfaceInstance<Yuki::Entity::YukiEntity, TestEntity>("test_1");

  scene->SetCamera(camera);
  scene->AddEntity(enTT1);

  yukiApp->SetCurrentScene(scene);

  yukiApp->RunApp();

  return 0;
}