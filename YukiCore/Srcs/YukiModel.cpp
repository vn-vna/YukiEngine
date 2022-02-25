#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiComp/YukiMesh.hpp"

#include "PYukiModel.hpp"

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

constexpr const auto ASSIMP_LOAD_FLAGS = aiProcessPreset_TargetRealtime_Quality;

namespace Yuki::Comp
{

YukiModel::YukiModel(const MeshArrType& meshArr)
    : m_apMeshes{meshArr}
{
  Create();
}

YukiModel::~YukiModel()
{
  Destroy();
}

void YukiModel::Create()
{
  for (AutoType pMesh : GetMeshes())
  {
    pMesh->Create();
  }
}
void YukiModel::Render()
{
}
void YukiModel::Destroy()
{
  for (AutoType pMesh : GetMeshes())
  {
    pMesh->Destroy();
  }
}

MeshArrType& YukiModel::GetMeshes()
{
  return m_apMeshes;
}

glm::mat4& YukiModel::GetModelMatrix()
{
  return m_tModelMatrix;
}

SharedPtr<IYukiModel> LoadModel(String fileName)
{
  StringStream FilePathSS = {};
  FilePathSS << fileName;
  Assimp::Importer importer = {};

  AutoType pScene = importer.ReadFile(FilePathSS.str(), ASSIMP_LOAD_FLAGS);

  MeshArrType meshes;
  meshes.reserve(pScene->mNumMeshes);

  for (unsigned meshID = 0; meshID < pScene->mNumMeshes; ++meshID)
  {
    AutoType vcount = pScene->mMeshes[meshID]->mNumVertices;
    AutoType varr   = pScene->mMeshes[meshID]->mVertices;
    AutoType narr   = pScene->mMeshes[meshID]->mNormals;
    AutoType fcount = pScene->mMeshes[meshID]->mNumFaces;
    AutoType farr   = pScene->mMeshes[meshID]->mFaces;

    std::vector<Core::VertexData> vform;
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

    std::vector<unsigned> idata;
    idata.reserve(fcount * 3);
    for (unsigned faceID = 0; faceID < fcount; ++faceID)
    {
      AutoType& face = farr[faceID];
      for (unsigned i = 0; i < face.mNumIndices; ++i)
      {
        idata.emplace_back(face.mIndices[i]);
      }
    }
    Core::IndexData iform = {Core::PrimitiveTopology::TRIANGLE_LIST, idata};

    AutoType default_mat = Comp::CreateMaterial(0.3f, 0.02f);

    AutoType mesh = CreateYukiMesh(vform, iform, NO_TEXTURE, default_mat, "MeshName");
    meshes.emplace_back(mesh);
  }

  return {(IYukiModel*) new YukiModel(meshes), std::default_delete<IYukiModel>()};
}

} // namespace Yuki::Comp