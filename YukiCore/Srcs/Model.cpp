#include "YukiComp/Mesh.hpp"
#include "YukiCore/Application.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/Headers.hpp"
#include "YukiDebug/Errors.hpp"

#include "Private/PModel.hpp"

// assimp
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fmt/format.h>

constexpr const int ASSIMP_LOAD_FLAGS =
    aiProcessPreset_TargetRealtime_MaxQuality;

namespace Yuki::Comp
{

using Core::GenerateSolid2DTexture;
// using Debug::YukiAssimpModelCantBeLoaded;
using Core::GetYukiApp;

YukiModel::YukiModel(String name, const MeshArrType& meshArr)
    : m_sName {name},
      m_apMeshes {meshArr}
{
  Create();
}

YukiModel::~YukiModel()
{
  Destroy();
}

void YukiModel::Create()
{
  for (const AutoType& pMesh : this->GetMeshes())
  {
    pMesh.second->Create();
  }
}

void YukiModel::Render()
{}

void YukiModel::Destroy()
{
  for (const AutoType& pMesh : this->GetMeshes())
  {
    if (pMesh.second.get())
    {
      pMesh.second->Destroy();
    }
  }
}

String& YukiModel::GetName()
{
  return m_sName;
}

MeshArrType& YukiModel::GetMeshes()
{
  return m_apMeshes;
}

Mat4F& YukiModel::GetModelMatrix()
{
  return m_tModelMatrix;
}

MeshType YukiModel::GetMesh(const String& name)
{
  if (this->GetMeshes()[name])
  {
    return this->GetMeshes()[name];
  }
  return {nullptr};
}

void YukiModel::Render(SharedPtr<ICamera> camera)
{
  for (const AutoType& pMesh : this->GetMeshes())
  {
    if (pMesh.second.get())
    {
      pMesh.second->RenderMesh(camera);
    }
  }
}

SharedPtr<IModel> LoadModel(String fileName, String modelName)
{
  static AutoType defaultMaterial =
      GenerateSolidMaterial({0.1f, 0.1f, 0.1f, 1.0f}, 0.6f, 1.0f);

  AutoType defaultTex = GenerateSolid2DTexture({1.0f, 0.4f, 0.0f, 1.0f});

  // TODO: Assimp model loader cause memory leak
  Assimp::Importer importer = {};

  AutoType pScene = importer.ReadFile(fileName, ASSIMP_LOAD_FLAGS);

  if (!pScene)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(importer.GetErrorString());
    THROW_YUKI_ERROR(AssimpModelCantBeLoaded);
  }

  MeshArrType meshes;
  meshes.reserve(pScene->mNumMeshes);

  std::for_each(
      pScene->mMeshes, pScene->mMeshes + pScene->mNumMeshes,
      [&](const aiMesh* aMesh) {
        AutoType vcount = aMesh->mNumVertices;
        AutoType varr   = aMesh->mVertices;
        AutoType narr   = aMesh->mNormals;
        AutoType fcount = aMesh->mNumFaces;
        AutoType farr   = aMesh->mFaces;

        Vector<MeshVertexFormat> vform;
        vform.reserve(vcount);
        for (unsigned vID = 0; vID < vcount; ++vID)
        {
          // clang-format off
      vform.push_back({
          {varr[vID].x, varr[vID].y, varr[vID].z},
          {narr[vID].x, narr[vID].y, narr[vID].z},
          {0.0f, 0.0f}
        });
      // clang-format on
        }

        Vector<unsigned> idata;
        idata.reserve(fcount * 3);
        std::for_each(farr, farr + fcount, [&](const aiFace& face) {
          std::for_each(
              face.mIndices, face.mIndices + face.mNumIndices,
              [&](unsigned index) { idata.emplace_back(index); }
          );
        });
        MeshIndexData iform = {
            PrimitiveTopology::TRIANGLE_LIST, std::move(idata)};

        AutoType mesh = GenerateYukiMesh(
            vform, iform, defaultTex, defaultMaterial, aMesh->mName.C_Str()
        );

#ifndef _NDEBUG
        StringStream sstr = {};
        Core::GetYukiApp()->GetLogger()->PushDebugMessage(fmt::format(
            "Loaded a mesh [{}] from file: {}", mesh->GetName(), fileName
        ));
#endif
        meshes[mesh->GetName()] = mesh;
      }
  );

  return Core::CreateInterfaceInstance<IModel, YukiModel>(modelName, meshes);
}

} // namespace Yuki::Comp
