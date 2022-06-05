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

template <typename T> using NumericLimits = std::numeric_limits<T>;

String& TrimString(String& str);
String  GetTrimmed(const String& str);

bool IsKeyPressed(KeyCode key);
bool IsKeyRepeated(KeyCode key);
bool IsKeyReleased(KeyCode key);

void MoveCameraRight(SharedPtr<IYukiCamera> camera, float speed);
void MoveCameraLeft(SharedPtr<IYukiCamera> camera, float speed);
void MoveCameraFront(SharedPtr<IYukiCamera> camera, float speed);
void MoveCameraBack(SharedPtr<IYukiCamera> camera, float speed);
void MoveCameraUp(SharedPtr<IYukiCamera> camera, float speed);
void MoveCameraDown(SharedPtr<IYukiCamera> camera, float speed);

template <class EntityClass, typename... Args> inline SharedPtr<Entity::TemplateEntity> createEntity(Args&&... args)
{
  return CreateInterfaceInstance<Entity::TemplateEntity, EntityClass>(std::forward<Args...>(args...));
}

template <typename T> inline T MaximumValue() { return NumericLimits<T>().max(); }

template <typename T> inline T MinimumValue() { return NumericLimits<T>().min(); }

} // namespace Yuki::Utils
