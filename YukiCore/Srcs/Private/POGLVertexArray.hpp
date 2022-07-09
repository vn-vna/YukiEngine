/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/Graphics.hpp"

#include "PObjects.hpp"

namespace Yuki::Core
{

class YukiOGLVertexArray final : virtual public IOGLVertexArray,
                                 virtual public YukiSharedObject
{
public:
  YukiOGLVertexArray();
  ~YukiOGLVertexArray() override;

  bool     OnUse();
  unsigned GetID() override;
  void     BindObject() override;
  void     Create() override;
  void     Destroy() override;

  void EnableAttribute(unsigned attrib) override;
  void AttributeBinding(unsigned attrib, unsigned binding) override;
  void SetVertexBuffer(SharedPtr<IOGLVertexBuffer> buffer, int bindIndex, size_t offset,
                       size_t stride) override;
  void SetAttributeFormat(unsigned size, unsigned attrib, size_t offset, bool normalized) override;
  void SetElementBuffer(SharedPtr<IOGLElementBuffer> buffer) override;

private:
  unsigned m_nVaoID;
};

} // namespace Yuki::Core
