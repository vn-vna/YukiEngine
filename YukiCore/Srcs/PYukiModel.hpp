#pragma once

#include "YukiComp/YukiModel.hpp"

#include "PYukiObject.hpp"

// glm
#include <glm/mat4x4.hpp>

namespace Yuki::Comp
{

class YukiModel final : virtual public IYukiModel,
                        virtual public Core::YukiObject
{
protected:
  MeshArrType m_apMeshes;
  glm::mat4   m_tModelMatrix;

public:
  YukiModel(const MeshArrType& meshArr);
  ~YukiModel();

  MeshArrType& GetMeshes() override;
  glm::mat4&   GetModelMatrix() override;
  MeshType     GetMesh(const String& name) override;


  void Render(SharedPtr<IYukiCamera> camera) override;

  void Create() override;
  void Render() override;
  void Destroy() override;
};

} // namespace Yuki::Comp