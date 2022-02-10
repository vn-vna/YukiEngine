#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Core
{

class YukiOGLVertexArray : public virtual IYukiOGLVertexArray
{
protected:
  unsigned m_nVaoID;
  int      m_nRequired;

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
};

} // namespace Yuki::Core
