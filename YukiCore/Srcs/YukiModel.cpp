#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiComp/YukiMesh.hpp"
#include "YukiDebug/YukiError.hpp"

#include "PYukiModel.hpp"

// assimp
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

constexpr const int ASSIMP_LOAD_FLAGS = aiProcessPreset_TargetRealtime_MaxQuality;

namespace Yuki::Comp
{

using Core::CreateSolid2DTexture;
using Debug::YukiAssimpModelCantBeLoaded;
using Core::GetYukiApp;

YukiModel::YukiModel(String name, const MeshArrType& meshArr) : m_sName{name}, m_apMeshes{meshArr} { Create(); }

YukiModel::~YukiModel() { Destroy(); }

void YukiModel::Create()
{
  for (const AutoType& pMesh : this->GetMeshes())
  {
    pMesh.second->Create();
  }
}
void YukiModel::Render() {}
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

String& YukiModel::GetName() { return m_sName; }

MeshArrType& YukiModel::GetMeshes() { return m_apMeshes; }

Mat4F& YukiModel::GetModelMatrix() { return m_tModelMatrix; }

MeshType YukiModel::GetMesh(const String& name)
{
  if (this->GetMeshes()[name])
  {
    return this->GetMeshes()[name];
  }
  return {nullptr};
}

void YukiModel::Render(SharedPtr<IYukiCamera> camera)
{
  for (const AutoType& pMesh : this->GetMeshes())
  {
    if (pMesh.second.get())
    {
      pMesh.second->RenderMesh(camera);
    }
  }
}

SharedPtr<IYukiModel> LoadModel(String fileName, String modelName)
{
  Assimp::Importer importer = {};

  AutoType pScene = importer.ReadFile(fileName, ASSIMP_LOAD_FLAGS);

  AutoType defaultMaterial = CreateMaterial(0.6f, 0.02f);

  if (!pScene)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(importer.GetErrorString());
    THROW_YUKI_ERROR(AssimpModelCantBeLoaded);
  }

  MeshArrType meshes;
  meshes.reserve(pScene->mNumMeshes);

  std::for_each(pScene->mMeshes, pScene->mMeshes + pScene->mNumMeshes, [&](const aiMesh* aMesh) {
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
          face.mIndices, face.mIndices + face.mNumIndices, [&](unsigned index) { idata.emplace_back(index); });
    });
    MeshIndexData iform = {PrimitiveTopology::TRIANGLE_LIST, std::move(idata)};

    AutoType defaultTex = CreateSolid2DTexture({1.0f, 0.0f, 0.0f, 1.0f});
    AutoType mesh       = CreateYukiMesh(vform, iform, defaultTex, defaultMaterial, aMesh->mName.C_Str());

#ifndef _NDEBUG
    StringStream sstr = {};
    sstr << "Loaded a mesh [" << mesh->GetName() << "] from file [" << fileName << "]\n";
    Core::GetYukiApp()->GetLogger()->PushDebugMessage(sstr.str());
#endif
    meshes[mesh->GetName()] = mesh;
  });

  return Core::CreateInterfaceInstance<IYukiModel, YukiModel>(modelName, meshes);
}

} // namespace Yuki::Comp
