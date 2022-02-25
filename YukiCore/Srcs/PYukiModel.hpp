#pragma once

#include "YukiComp/YukiModel.hpp"

#include <glm/mat4x4.hpp>

namespace Yuki::Comp
{

typedef SharedPtr<IYukiMesh>  MeshType;
typedef std::vector<MeshType> MeshArrType;

class YukiModel final : public IYukiModel
{
protected:
  MeshArrType m_apMeshes;
  glm::mat4   m_tModelMatrix;

public:
  YukiModel(const MeshArrType& meshArr);
  ~YukiModel();

  MeshArrType& GetMeshes() override;
  glm::mat4&   GetModelMatrix() override;

  void Create() override;
  void Render() override;
  void Destroy() override;
};

} // namespace Yuki::Comp