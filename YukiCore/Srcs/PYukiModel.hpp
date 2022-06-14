/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiComp/YukiModel.hpp"

#include "PYukiObject.hpp"

// glm
#include <glm/mat4x4.hpp>

namespace Yuki::Comp
{

using Core::YukiObject;

class YukiModel final : virtual public IYukiModel, virtual public YukiObject
{
public:
  YukiModel(String name, const MeshArrType& meshArr);
  ~YukiModel() override;

  String&      GetName() override;
  MeshArrType& GetMeshes() override;
  Mat4F&       GetModelMatrix() override;
  MeshType     GetMesh(const String& name) override;


  void Render(SharedPtr<IYukiCamera> camera) override;

  void Create() override;
  void Render() override;
  void Destroy() override;

private:
  MeshArrType m_apMeshes;
  Mat4F       m_tModelMatrix;
  String      m_sName;
};

} // namespace Yuki::Comp
