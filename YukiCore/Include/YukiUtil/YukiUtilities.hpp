/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include <YukiCore/YukiApplication.hpp>
#include <YukiCore/YukiInputCtrl.hpp>
#include <YukiComp/YukiCamera.hpp>
#include <YukiEntity/Entity.hpp>

namespace Yuki::Utils
{

using namespace Yuki::Core;
using namespace Yuki::Comp;

bool YUKIAPI IsKeyPressed(KeyCode key);
bool YUKIAPI IsKeyRepeated(KeyCode key);
bool YUKIAPI IsKeyReleased(KeyCode key);

void YUKIAPI MoveCameraRight(SharedPtr<IYukiCamera> camera, float speed);
void YUKIAPI MoveCameraLeft(SharedPtr<IYukiCamera> camera, float speed);
void YUKIAPI MoveCameraFront(SharedPtr<IYukiCamera> camera, float speed);
void YUKIAPI MoveCameraBack(SharedPtr<IYukiCamera> camera, float speed);
void YUKIAPI MoveCameraUp(SharedPtr<IYukiCamera> camera, float speed);
void YUKIAPI MoveCameraDown(SharedPtr<IYukiCamera> camera, float speed);

template <class EntityClass, typename... Args>
SharedPtr<Entity::YukiEntity> CreateEntity(Args&&... args)
{
  return CreateInterfaceInstance<Entity::YukiEntity, EntityClass>(std::forward<Args...>(args...));
}

} // namespace Yuki::Utils