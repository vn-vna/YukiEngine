#pragma once

#include "YukiCore/YukiObject.hpp"

namespace Yuki::Entities
{

typedef std::map<String, SharedPtr<Entity>> EntitiesPoolType;

class YUKIAPI Scene : public Core::IYukiObject
{
  virtual EntitiesPoolType& GetEntitiesPool() = 0;
};

} // namespace Yuki::Entities