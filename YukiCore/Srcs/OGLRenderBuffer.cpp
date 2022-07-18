#include "Private/POGLRenderBuffer.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/Objects.hpp"

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

void YukiOGLRenderBuffer::SetBufferStorage(
    PixelInternalFormat internalFormat, const Vec2I& size
)
{
  glNamedRenderbufferStorage(m_nRboId, (GLenum) internalFormat, size.x, size.y);
}

void YukiOGLRenderBuffer::SetBufferStorageMultiSamples(
    PixelInternalFormat internalFormat, const Vec2I& size, int samples
)
{
  glNamedRenderbufferStorageMultisample(
      m_nRboId, samples, (GLenum) internalFormat, size.x, size.y
  );
}

void YukiOGLRenderBuffer::Create()
{
  glCreateRenderbuffers(1, &m_nRboId);
}

void YukiOGLRenderBuffer::Destroy()
{
  glDeleteRenderbuffers(1, &m_nRboId);
}

SharedPtr<IOGLRenderBuffer> CreateGLRegnderBuffer()
{
  return CreateInterfaceInstance<IOGLRenderBuffer, YukiOGLRenderBuffer>();
}

} // namespace Yuki::Core
