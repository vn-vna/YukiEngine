#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Core
{

class YukiOGLVertexArray : public IYukiOGLVertexArray
{
protected:
  unsigned m_nVaoID;

public:
  YukiOGLVertexArray();
  virtual ~YukiOGLVertexArray();

  const unsigned& GetID() override;
  void            BindObject() override;
  void            Create() override;
  void            Destroy() override;
  bool            OnUse() override;

  void EnableAttribute(const unsigned& attrib) override;
  void AttributeBinding(const unsigned& attrib, const unsigned& binding) override;
  void SetVertexBuffer(
      const SharedPtr<IYukiOGLVertexBuffer>& buffer, int bindIndex, size_t offset, size_t stride) override;
  void SetAttributeFormat(
      const unsigned& attrib, const unsigned& size, const size_t& offset, const bool& normalized = false) override;
};

} // namespace Yuki::Core