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
#include "YukiCore/Headers.hpp"

namespace Yuki::Comp
{

using Core::YukiSharedObject;

class YukiModel final : virtual public IModel,
                        virtual public YukiSharedObject
{
public:
  YukiModel(String name, const MeshArrType& meshArr);
  ~YukiModel() override;

  String&      GetName() override;
  MeshArrType& GetMeshes() override;
  Mat4F&       GetModelMatrix() override;
  MeshType     GetMesh(const String& name) override;


  void Render(SharedPtr<ICamera> camera, SharedPtr<IScene> scene) override;

  void Create() override;
  void Render() override;
  void Destroy() override;

private:
  MeshArrType m_apMeshes;
  Mat4F       m_tModelMatrix;
  String      m_sName;
};

} // namespace Yuki::Comp
