#include "YukiCore/Objects.hpp"

#include "Private/PObjects.hpp"

namespace Yuki::Core
{

void YukiObject::Create()
{}

void YukiObject::Awake()
{}

void YukiObject::Update()
{}

void YukiObject::Render()
{}

void YukiObject::Destroy()
{}

YukiSharedObject::YukiSharedObject()
    : m_nRequired(0),
      m_bCreated(false)
{}

YukiSharedObject::~YukiSharedObject() = default;

void YukiSharedObject::Require()
{
  if (m_nRequired > 0)
  {
    ++m_nRequired;
    return;
  }
  m_nRequired = 1;
  if (m_bCreated)
  {
    return;
  }
  this->Create();
  m_bCreated = true;
}

void YukiSharedObject::Release()
{
  if (m_nRequired > 1)
  {
    --m_nRequired;
    return;
  }
  m_nRequired = 0;
  if (!m_bCreated)
  {
    return;
  }
  this->Destroy();
  m_bCreated = false;
}

} // namespace Yuki::Core
