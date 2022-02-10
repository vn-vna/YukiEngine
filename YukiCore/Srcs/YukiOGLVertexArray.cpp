#include "YukiCore/YukiPCH.hpp"
#include "PYukiOGLVertexArray.hpp"

namespace Yuki::Core
{

YukiOGLVertexArray::YukiOGLVertexArray()
    : m_nVaoID()
{}

YukiOGLVertexArray::~YukiOGLVertexArray() = default;

const unsigned& YukiOGLVertexArray::GetID()
{
  return m_nVaoID;
}

void YukiOGLVertexArray::BindObject()
{
  glBindVertexArray(m_nVaoID);
}

bool YukiOGLVertexArray::OnUse()
{
  int crrVAO;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &crrVAO);
  return crrVAO == m_nVaoID;
}

void YukiOGLVertexArray::SetVertexBuffer(
    const SharedPtr<IYukiOGLVertexBuffer>& buffer, int bindIndex, size_t offset, size_t stride)
{
  glVertexArrayVertexBuffer(m_nVaoID, 0, buffer->GetID(), offset, (GLsizei) stride);
}

void YukiOGLVertexArray::EnableAttribute(const unsigned& attrib)
{
  glEnableVertexArrayAttrib(m_nVaoID, attrib);
}

void YukiOGLVertexArray::SetAttributeFormat(
    const unsigned& attrib, const unsigned& size, const size_t& offset, const bool& normalized)
{
  glVertexArrayAttribFormat(m_nVaoID, attrib, size, GL_FLOAT, normalized, (GLsizei) offset);
}

void YukiOGLVertexArray::AttributeBinding(const unsigned& attrib, const unsigned& binding)
{
  glVertexArrayAttribBinding(m_nVaoID, attrib, binding);
}

void YukiOGLVertexArray::Create()
{
  if (m_nRequired <= 0)
  {
    glCreateVertexArrays(1, &m_nVaoID);
    m_nRequired = 0;
  }
  ++m_nRequired;
}

void YukiOGLVertexArray::Destroy()
{
  --m_nRequired;
  if (m_nRequired == 0)
  {
    glDeleteVertexArrays(1, &m_nVaoID);
  }
}

SharedPtr<IYukiOGLVertexArray> CreateGLVertexArray()
{
  return {(IYukiOGLVertexArray*) new YukiOGLVertexArray, std::default_delete<IYukiOGLVertexArray>()};
}

} // namespace Yuki::Core