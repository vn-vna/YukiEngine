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

bool YUKIAPI isKeyPressed(KeyCode key);
bool YUKIAPI isKeyRepeated(KeyCode key);
bool YUKIAPI isKeyReleased(KeyCode key);

void YUKIAPI moveCameraRight(SharedPtr<IYukiCamera> camera, float speed);
void YUKIAPI moveCameraLeft(SharedPtr<IYukiCamera> camera, float speed);
void YUKIAPI moveCameraFront(SharedPtr<IYukiCamera> camera, float speed);
void YUKIAPI moveCameraBack(SharedPtr<IYukiCamera> camera, float speed);
void YUKIAPI moveCameraUp(SharedPtr<IYukiCamera> camera, float speed);
void YUKIAPI moveCameraDown(SharedPtr<IYukiCamera> camera, float speed);

template <class EntityClass, typename... Args>
SharedPtr<Entity::YukiEntity> CreateEntity(Args&&... args)
{
  return CreateInterfaceInstance<Entity::YukiEntity, EntityClass>(std::forward<Args...>(args...));
}

} // namespace Yuki::Utils