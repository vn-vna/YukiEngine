/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiObject.hpp"

namespace Yuki::Core
{

class YukiObject : virtual public IYukiObject
{
public:
  YukiObject()          = default;
  virtual ~YukiObject() = default;

  void Create() override;
  void Awake() override;
  void Update() override;
  void Render() override;
  void Destroy() override;
};

class YukiSharedObject : virtual public IYukiSharedObject,
                         virtual public YukiObject
{
public:
  YukiSharedObject();
  ~YukiSharedObject() override;

  void Require() override;
  void Release() override;

protected:
  int  m_nRequired;
  bool m_bCreated;
};

} // namespace Yuki::Core
