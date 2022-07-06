/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiComp/Model.hpp"

#include "PObjects.hpp"

// glm
#include "clion-dbg/vcpkg_installed/x64-windows/include/glm/mat4x4.hpp"

namespace Yuki::Comp
{

using Core::YukiSharedObject;

class YukiModel final : virtual public IYukiModel,
                        virtual public YukiSharedObject
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
