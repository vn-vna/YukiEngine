#include "YukiCore/YukiPCH.hpp"

#include "PYukiOGLElementBuffer.hpp"

namespace Yuki::Core
{

YukiOGLElementBuffer::YukiOGLElementBuffer()
    : m_nEboID(),
      m_nElementCount(),
      m_nRequired(0)
{}

YukiOGLElementBuffer::~YukiOGLElementBuffer() = default;

const unsigned& YukiOGLElementBuffer::GetID()
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

void YukiOGLElementBuffer::SetBufferData(std::vector<unsigned>& data)
{
  SetBufferData(data.data(), data.size() * sizeof(unsigned));
}

void YukiOGLElementBuffer::SetBufferData(unsigned* pData, size_t size)
{
  glNamedBufferData(m_nEboID, size, pData, GL_STATIC_DRAW);
  m_nElementCount = (unsigned) (size / sizeof(unsigned));
}

void YukiOGLElementBuffer::DrawElements(Core::PrimitiveTopology topology, const unsigned& start, const unsigned& count)
{
  GLenum glTopology = (GLenum) topology;
  glDrawElements(glTopology, count, GL_UNSIGNED_INT, (void*) (start * sizeof(unsigned)));
}

void YukiOGLElementBuffer::DrawAllElements(Core::PrimitiveTopology topology)
{
  DrawElements(topology, 0, m_nElementCount);
}

void YukiOGLElementBuffer::Create()
{
  if (m_nRequired <= 0)
  {
    glCreateBuffers(1, &m_nEboID);
    m_nRequired = 0;
  }
  ++m_nRequired;
}

void YukiOGLElementBuffer::Destroy()
{
  --m_nRequired;
  if (m_nRequired == 0)
  {
    glDeleteBuffers(1, &m_nEboID);
  }
}

SharedPtr<IYukiOGLElementBuffer> YUKIAPI CreateGLElementBuffer()
{
  return {(IYukiOGLElementBuffer*) new YukiOGLElementBuffer, std::default_delete<IYukiOGLElementBuffer>()};
}

} // namespace Yuki::Core
