#pragma once

#include <YukiEntity/Entity.hpp>

class TestEntity : virtual public Yuki::Entity::YukiEntity
{
protected:
public:
  explicit TestEntity(const Yuki::String& name);
  ~TestEntity() override;

  void OnCreate() override;
  void OnAwake() override;
  void OnUpdate() override;
  void OnRender() override;
  void OnDestroy() override;

  static Yuki::SharedPtr<Yuki::Entity::YukiEntity> getInstance();
};

inline void TestEntity::OnCreate()
{
  Yuki::SharedPtr<Yuki::Comp::IYukiModel> testModel = Yuki::Comp::LoadModel("sphere.fbx", "Sphere");
  this->SetModel(testModel);
}

inline void TestEntity::OnAwake()
{
  AutoType logger = Yuki::Core::GetYukiApp()->GetLogger();
  logger->PushDebugMessage("On awake is called");
}

inline void TestEntity::OnUpdate()
{
}

inline void TestEntity::OnRender()
{
}

inline void TestEntity::OnDestroy()
{
}

inline TestEntity::TestEntity(const Yuki::String& name) : YukiEntity(name)
{
}

inline TestEntity::~TestEntity() = default;

inline Yuki::SharedPtr<Yuki::Entity::YukiEntity> TestEntity::getInstance()
{
  static Yuki::SharedPtr<Yuki::Entity::YukiEntity> instance;
  if (!instance.get())
  {
    instance = Yuki::Core::CreateInterfaceInstance<Yuki::Entity::YukiEntity, TestEntity>("test_entt");
  }
  return instance;
}