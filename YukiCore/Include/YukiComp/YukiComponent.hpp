#pragma once

#include "YukiCore/YukiObject.hpp"

namespace Yuki::Comp
{

enum class ComponentType
{
  CAMERA,
  LIGHT,
  MESH
};

class YUKIAPI IYukiComp : public Core::IYukiObject
{
public:
  virtual ComponentType GetComponentType() = 0;
};

} // namespace Yuki::Comp