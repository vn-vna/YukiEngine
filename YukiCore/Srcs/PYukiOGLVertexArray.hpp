#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

class YukiOGLVertexArray : virtual public IYukiOGLVertexArray,
                           virtual public YukiObject
{
protected:
  unsigned m_nVaoID;

public:
  YukiOGLVertexArray();
  virtual ~YukiOGLVertexArray();

  bool            OnUse();
  const unsigned& GetID() override;
  void            BindObject() override;
  void            Create() override;
  void            Destroy() override;

  void EnableAttribute(const unsigned& attrib) override;
  void AttributeBinding(const unsigned& attrib, const unsigned& binding) override;
  void SetVertexBuffer(
      const SharedPtr<IYukiOGLVertexBuffer>& buffer, int bindIndex, size_t offset, size_t stride) override;
  void SetAttributeFormat(
      const unsigned& attrib, const unsigned& size, const size_t& offset, const bool& normalized = false) override;
  void SetElementBuffer(SharedPtr<IYukiOGLElementBuffer> buffer) override;
};

} // namespace Yuki::Core