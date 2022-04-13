#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Entity
{

class YUKIAPI Entity : virtual public Core::IYukiObject
{
protected:


public:
  Entity();
  virtual ~Entity();

  void Create() override final;
  void Awake() override final;
  void Update() override final;
  void Render() override final;
  void Destroy() override final;

  virtual void OnCreate();
  virtual void OnAwake();
  virtual void OnUpdate();
  virtual void OnRender();
  virtual void OnDestroy();
};

} // namespace Yuki::Entity