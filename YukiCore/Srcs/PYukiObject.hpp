#pragma once

#include "YukiCore/YukiObject.hpp"

namespace Yuki::Core
{

class YukiObject : virtual public IYukiObject
{
public:
  YukiObject()          = default;
  virtual ~YukiObject() = default;

  virtual void Create() override;
  virtual void Awake() override;
  virtual void Update() override;
  virtual void Render() override;
  virtual void Destroy() override;
};

} // namespace Yuki::Core