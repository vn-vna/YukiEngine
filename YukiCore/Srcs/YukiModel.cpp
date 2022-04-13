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

constexpr const int ASSIMP_LOAD_FLAGS = aiProcessPreset_TargetRealtime_Fast;

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
  for (const AutoType& pMesh : this->GetMeshes())
  {
    pMesh.second->Create();
  }
}
void YukiModel::Render()
{
}
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

MeshArrType& YukiModel::GetMeshes()
{
  return m_apMeshes;
}

glm::mat4& YukiModel::GetModelMatrix()
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

SharedPtr<IYukiModel> LoadModel(String fileName)
{
  Assimp::Importer importer = {};

  AutoType pScene = importer.ReadFile(fileName, ASSIMP_LOAD_FLAGS);

  AutoType defaultMaterial = Comp::CreateMaterial(0.6f, 0.02f);

  if (!pScene)
  {
    Core::GetYukiApp()->GetLogger()->PushErrorMessage(importer.GetErrorString());
    THROW_YUKI_ERROR(Debug::YukiAssimpModelCantBeLoaded);
  }

  MeshArrType meshes;
  meshes.reserve(pScene->mNumMeshes);

  for (unsigned meshID = 0; meshID < pScene->mNumMeshes; ++meshID)
  {
    AutoType aimesh = pScene->mMeshes[meshID];
    AutoType vcount = aimesh->mNumVertices;
    AutoType varr   = aimesh->mVertices;
    AutoType narr   = aimesh->mNormals;
    AutoType fcount = aimesh->mNumFaces;
    AutoType farr   = aimesh->mFaces;

    Vector<Core::VertexData> vform;
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
    for (unsigned faceID = 0; faceID < fcount; ++faceID)
    {
      AutoType& face = farr[faceID];
      for (unsigned i = 0; i < face.mNumIndices; ++i)
      {
        idata.emplace_back(face.mIndices[i]);
      }
    }
    Core::IndexData iform = {Core::PrimitiveTopology::TRIANGLE_LIST, std::move(idata)};

    AutoType mesh = CreateYukiMesh(vform, iform, NO_TEXTURE, defaultMaterial, aimesh->mName.C_Str());

#ifndef _NDEBUG
    StringStream sstr = {};
    sstr << "Loaded a mesh [" << mesh->GetName() << "] from file [" << fileName << "]\n";
    Core::GetYukiApp()
        ->GetLogger()
        ->PushDebugMessage(sstr.str());
#endif
    meshes[mesh->GetName()] = mesh;
  }

  return Core::CreateInterfaceInstance<IYukiModel, YukiModel>(meshes);
}

} // namespace Yuki::Comp