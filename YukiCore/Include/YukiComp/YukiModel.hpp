#pragma once

#include "YukiCore/YukiObject.hpp"

#include <glm/mat4x4.hpp>

namespace Yuki::Comp
{

SharedPtr<IYukiModel> LoadModel(String fileName);

class YUKIAPI IYukiModel : protected Core::IYukiObject
{
public:
  virtual std::vector<SharedPtr<IYukiMesh>>& GetMeshes()      = 0;
  virtual glm::mat4&                         GetModelMatrix() = 0;
};

} // namespace Yuki::Comp