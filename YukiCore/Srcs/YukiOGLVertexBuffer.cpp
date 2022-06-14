#include "YukiCore/YukiPCH.hpp"

#include "PYukiOGLVertexBuffer.hpp"

namespace Yuki::Core
{

YukiOGLVertexBuffer::YukiOGLVertexBuffer() : m_nVboID() {}

YukiOGLVertexBuffer::~YukiOGLVertexBuffer() = default;

unsigned YukiOGLVertexBuffer::GetID() { return m_nVboID; }

bool YukiOGLVertexBuffer::OnUse()
{
  int crrVB;
  glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &crrVB);
  return crrVB == m_nVboID;
}

void YukiOGLVertexBuffer::BindObject() { glBindBuffer(GL_ARRAY_BUFFER, m_nVboID); }

void YukiOGLVertexBuffer::SetBufferData(Vector<float>& data)
{
  SetBufferData(data.data(), data.size() * sizeof(float));
}

void YukiOGLVertexBuffer::SetBufferData(float* pData, size_t size)
{
  glNamedBufferData(m_nVboID, size, pData, GL_STATIC_DRAW);
}

void YukiOGLVertexBuffer::Create() { glCreateBuffers(1, &m_nVboID); }

void YukiOGLVertexBuffer::Destroy() { glDeleteBuffers(1, &m_nVboID); }

SharedPtr<IYukiOGLVertexBuffer> CreateGLVertexBuffer()
{
  return CreateInterfaceInstance<IYukiOGLVertexBuffer, YukiOGLVertexBuffer>();
}

} // namespace Yuki::Core