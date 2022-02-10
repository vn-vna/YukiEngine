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

class YUKIAPI IYukiComp : protected Core::IYukiObject
{
public:
  virtual ComponentType GetComponentType() = 0;

  friend class YukiEntity;
};

} // namespace Yuki::Comp