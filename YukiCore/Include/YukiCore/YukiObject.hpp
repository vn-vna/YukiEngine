#pragma once

#include "YukiCore/YukiVE.hpp"

namespace Yuki::Core
{

class YUKIAPI IYukiObject
{
public:
  IYukiObject()          = default;
  virtual ~IYukiObject() = default;

  virtual void Create(){};
  virtual void Awake(){};
  virtual void Update(){};
  virtual void Render(){};
  virtual void Destroy(){};
};

} // namespace Yuki::Core
