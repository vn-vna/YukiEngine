#include "PYukiOGLRenderBuffer.hpp"

namespace Yuki::Core
{

YukiOGLRenderBuffer::YukiOGLRenderBuffer()
{}

YukiOGLRenderBuffer::~YukiOGLRenderBuffer() = default;

unsigned YukiOGLRenderBuffer::GetID()
{
  return m_nRboId;
}

void YukiOGLRenderBuffer::BindObject()
{
  glBindRenderbuffer(GL_RENDERBUFFER, m_nRboId);
}

void YukiOGLRenderBuffer::Create()
{
  glCreateRenderbuffers(1, &m_nRboId);
}

void YukiOGLRenderBuffer::Destroy()
{
  glDeleteRenderbuffers(1, &m_nRboId);
}

} // namespace Yuki::Core