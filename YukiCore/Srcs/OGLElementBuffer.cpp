#include "YukiCore/Headers.hpp"

#include "Private/POGLElementBuffer.hpp"

namespace Yuki::Core
{

YukiOGLElementBuffer::YukiOGLElementBuffer()
    : m_nEboID(),
      m_nElementCount()
{}

YukiOGLElementBuffer::~YukiOGLElementBuffer() = default;

unsigned YukiOGLElementBuffer::GetID()
{
  return m_nEboID;
}

void YukiOGLElementBuffer::BindObject()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nEboID);
}

bool YukiOGLElementBuffer::OnUse()
{
  int crrEbo;
  glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &crrEbo);
  return m_nEboID == crrEbo;
}

void YukiOGLElementBuffer::SetBufferData(Vector<unsigned>& data)
{
  SetBufferData(data.data(), data.size() * sizeof(unsigned));
}

void YukiOGLElementBuffer::SetBufferData(unsigned* pData, size_t size)
{
  glNamedBufferData(m_nEboID, size, pData, GL_STATIC_DRAW);
  m_nElementCount = (unsigned) (size / sizeof(unsigned));
}

void YukiOGLElementBuffer::DrawElements(Core::PrimitiveTopology topology,
                                        unsigned start, unsigned count)
{
  GLenum glTopology = (GLenum) topology;
  glDrawElements(glTopology, count, GL_UNSIGNED_INT,
                 (void*) (start * sizeof(unsigned)));
}

void YukiOGLElementBuffer::DrawAllElements(Core::PrimitiveTopology topology)
{
  DrawElements(topology, 0, m_nElementCount);
}

void YukiOGLElementBuffer::Create()
{
  glCreateBuffers(1, &m_nEboID);
}

void YukiOGLElementBuffer::Destroy()
{
  glDeleteBuffers(1, &m_nEboID);
}

SharedPtr<IOGLElementBuffer> CreateGLElementBuffer()
{
  return CreateInterfaceInstance<IOGLElementBuffer, YukiOGLElementBuffer>();
}

} // namespace Yuki::Core
