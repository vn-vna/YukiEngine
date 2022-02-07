#pragma once

#include "YukiCore/YukiObject.hpp"

namespace Yuki::Comp
{

typedef std::map<String, SharedPtr<YukiEntity>>            EntitiesPoolType;
typedef std::map<String, SharedPtr<IYukiCamera>>           CamerasPoolType;
typedef std::map<String, SharedPtr<IYukiMesh>>             MeshesPoolType;
typedef std::map<String, SharedPtr<IYukiDirectionalLight>> DirectionalLightsPoolType;
typedef std::map<String, SharedPtr<IYukiPointLight>>       PointLightsPoolType;
typedef std::map<String, SharedPtr<IYukiSpotLight>>        SpotLightsPoolType;

class YUKIAPI YukiScene : public Core::IYukiObject
{
protected:
  EntitiesPoolType          m_mEntitiesPool;
  CamerasPoolType           m_mCamerasPool;
  MeshesPoolType            m_mMeshesPool;
  DirectionalLightsPoolType m_mDirectionalLightsPool;
  PointLightsPoolType       m_mPointLightsPool;
  SpotLightsPoolType        m_mSpotLightsPool;

public:
  YukiScene();
  virtual ~YukiScene();

  EntitiesPoolType&          GetEntitiesPool();
  CamerasPoolType&           GetCamerasPool();
  MeshesPoolType&            GetMeshesPool();
  DirectionalLightsPoolType& GetDirectionalLightsPool();
  PointLightsPoolType&       GetPointLightsPool();
  SpotLightsPoolType&        GetSpotLightsPool();

  friend class YukiEntity;
};

} // namespace Yuki::Comp