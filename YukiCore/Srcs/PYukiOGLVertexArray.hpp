#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

class YukiOGLVertexArray final : virtual public IYukiOGLVertexArray,
                                 virtual public YukiObject
{
protected:
  unsigned m_nVaoID;

public:
  YukiOGLVertexArray();
  ~YukiOGLVertexArray() override;

  bool            OnUse();
  const unsigned& GetID() override;
  void            BindObject() override;
  void            Create() override;
  void            Destroy() override;

  void EnableAttribute(unsigned attrib) override;
  void AttributeBinding(unsigned attrib, unsigned binding) override;
  void SetVertexBuffer(SharedPtr<IYukiOGLVertexBuffer> buffer, int bindIndex, size_t offset, size_t stride) override;
  void SetAttributeFormat(unsigned size, unsigned attrib, size_t offset, bool normalized) override;
  void SetElementBuffer(SharedPtr<IYukiOGLElementBuffer> buffer) override;
};

} // namespace Yuki::Core