#pragma once

#include "YukiCore/YukiObject.hpp"
#include "YukiComp/YukiCamera.hpp"

#include <glm/mat4x4.hpp>

namespace Yuki::Comp
{

typedef SharedPtr<IYukiMesh>                 MeshType;
typedef UnorderedMap<String, MeshType> MeshArrType;

SharedPtr<IYukiModel> LoadModel(String fileName);

class YUKIAPI IYukiModel : virtual public Core::IYukiObject
{
public:
  virtual MeshArrType& GetMeshes()                 = 0;
  virtual glm::mat4&   GetModelMatrix()            = 0;
  virtual MeshType     GetMesh(const String& name) = 0;

  virtual void Render(SharedPtr<IYukiCamera> camera) = 0;
};

} // namespace Yuki::Comp