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

#include <limits>

namespace Yuki::Utils
{

using namespace Yuki::Core;
using namespace Yuki::Comp;

template <typename T>
using NumericLimits = std::numeric_limits<T>;

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
inline SharedPtr<Entity::YukiEntity> createEntity(Args&&... args)
{
  return CreateInterfaceInstance<Entity::YukiEntity, EntityClass>(std::forward<Args...>(args...));
}

template <typename T>
inline T MaximumValue()
{
  return NumericLimits<T>().max();
}

template <typename T>
inline T MinimumValue()
{
  return NumericLimits<T>().min();
}

} // namespace Yuki::Utils