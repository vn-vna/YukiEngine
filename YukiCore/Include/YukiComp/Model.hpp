/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Objects.hpp"
#include "YukiComp/Camera.hpp"

#include <glm/mat4x4.hpp>

namespace Yuki::Comp
{

using Core::ISharedObject;

typedef SharedPtr<IMesh>               MeshType;
typedef UnorderedMap<String, MeshType> MeshArrType;

/**
 * Load models from external resource
 * @param fileName File name (Relative path or Absolute
 * path)
 * @param modelName Provide a name for loaded model
 * @return An interface instance of the model
 * @bug Blender ^2.8 files can't be loaded
 */
SharedPtr<IModel> LoadModel(String fileName, String modelName);

/**
 * A collection of meshes that will be rendered by the
 * Entities
 */
class IModel : virtual public ISharedObject
{
public:
  virtual String&      GetName()                   = 0;
  virtual MeshArrType& GetMeshes()                 = 0;
  virtual Mat4F&       GetModelMatrix()            = 0;
  virtual MeshType     GetMesh(const String& name) = 0;

  virtual void Render(SharedPtr<ICamera> camera) = 0;
};

} // namespace Yuki::Comp
