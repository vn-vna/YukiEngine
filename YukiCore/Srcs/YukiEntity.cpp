#include "YukiCore/YukiPCH.hpp"

#include "YukiCore/YukiApplication.hpp"
#include "YukiComp/YukiEntity.hpp"
#include "YukiComp/YukiMesh.hpp"
#include "YukiDebug/YukiError.hpp"

#define INTERFACE_FUNC_CALL(func)          \
  if (m_mMeshPool.empty())                 \
  {                                        \
    return;                                \
  }                                        \
  for (const AutoType& comp : m_mMeshPool) \
  {                                        \
    AutoType& ptr = comp.second;           \
    if (!ptr.get())                        \
    {                                      \
      continue;                            \
    }                                      \
    ptr->func##();                         \
  }

namespace Yuki::Comp
{
YukiEntity::YukiEntity(const String& name)
    : m_mMeshPool(),
      m_RotationMatrix(1.00f),
      m_ScaleMatrix(1.00f),
      m_TranslateMatrix(1.00f),
      m_Name(name)
{}

YukiEntity::~YukiEntity() = default;

void YukiEntity::OnCreate()
{}

void YukiEntity::OnAwake()
{}

void YukiEntity::OnUpdate()
{}

void YukiEntity::OnRender()
{}

void YukiEntity::OnDestroy()
{}

void YukiEntity::BindMesh(const String& name, const SharedPtr<IYukiMesh>& comp)
{
    if (!comp.get())
    {
        THROW_YUKI_ERROR(Debug::YukiEntityBindUndefinedMeshError);
    }
    if (m_mMeshPool.find(name) != m_mMeshPool.end())
    {
        THROW_YUKI_ERROR(Debug::YukiEntityBindMeshExistsError);
    }
    m_mMeshPool.emplace(name, comp);
}

void YukiEntity::UnbindMesh(const String& name)
{
    if (m_mMeshPool.find(name) == m_mMeshPool.end())
    {
        THROW_YUKI_ERROR(Debug::YukiEntityUnbindMeshNExistsError);
    }
    m_mMeshPool.erase(name);
}

glm::mat4& YukiEntity::GetTranslateMatrix()
{
    return m_TranslateMatrix;
}

glm::mat4& YukiEntity::GetScaleMatrix()
{
    return m_ScaleMatrix;
}

glm::mat4& YukiEntity::GetRotationMatrix()
{
    return m_RotationMatrix;
}

SharedPtr<Core::IYukiApp> YukiEntity::GetApp()
{
    return Core::GetYukiApp();
}

SharedPtr<Core::IYukiInpControl> YukiEntity::GetInputControl()
{
    return GetApp()->GetInputController();
}

SharedPtr<Core::IYukiGfxControl> YukiEntity::GetGraphicsControl()
{
    return GetApp()->GetGraphicsController();
}

SharedPtr<Core::IYukiWindow> YukiEntity::GetWindow()
{
    return GetApp()->GetWindow();
}

void YukiEntity::Create()
{
    OnCreate();
    INTERFACE_FUNC_CALL(Create);
}

void YukiEntity::Awake()
{
    OnAwake();
    INTERFACE_FUNC_CALL(Awake);
}

void YukiEntity::Update()
{
    OnUpdate();
    INTERFACE_FUNC_CALL(Update);
}

void YukiEntity::Render()
{
    OnRender();
    INTERFACE_FUNC_CALL(Render);
}

void YukiEntity::Destroy()
{
    OnDestroy();
    INTERFACE_FUNC_CALL(Destroy);
}

} // namespace Yuki::Comp