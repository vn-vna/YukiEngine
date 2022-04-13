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

void YukiOGLVertexArray::SetElementBuffer(SharedPtr<IYukiOGLElementBuffer> buffer)
{
  glVertexArrayElementBuffer(m_nVaoID, buffer->GetID());
}

void YukiOGLVertexArray::Create()
{
  glCreateVertexArrays(1, &m_nVaoID);
}

void YukiOGLVertexArray::Destroy()
{
  glDeleteVertexArrays(1, &m_nVaoID);
}

SharedPtr<IYukiOGLVertexArray> CreateGLVertexArray()
{
  return CreateInterfaceInstance<IYukiOGLVertexArray, YukiOGLVertexArray>();
}

} // namespace Yuki::Core