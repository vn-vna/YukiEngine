#include "PYukiOGLFrameBuffer.hpp"
#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Core
{

YukiOGLFrameBuffer::YukiOGLFrameBuffer()
{}

YukiOGLFrameBuffer::~YukiOGLFrameBuffer() = default;

unsigned YukiOGLFrameBuffer::GetID()
{
  return m_nFboID;
}

void YukiOGLFrameBuffer::BindObject()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_nFboID);
}

bool YukiOGLFrameBuffer::BufferOK()
{
  return glCheckNamedFramebufferStatus(m_nFboID, GL_FRAMEBUFFER);
}

void YukiOGLFrameBuffer::AttachTextureColor(SharedPtr<IYukiOGLTexture> tex, unsigned position, unsigned level)
{
  glNamedFramebufferTexture(m_nFboID, GL_COLOR_ATTACHMENT0 + position, tex->GetID(), level);
}

void YukiOGLFrameBuffer::AttachTextureDepth(SharedPtr<IYukiOGLTexture> tex, unsigned level)
{
  glNamedFramebufferTexture(m_nFboID, GL_DEPTH_ATTACHMENT, tex->GetID(), level);
}

void YukiOGLFrameBuffer::AttachTextureStencil(SharedPtr<IYukiOGLTexture> tex, unsigned level)
{
  glNamedFramebufferTexture(m_nFboID, GL_STENCIL_ATTACHMENT, tex->GetID(), level);
}

void YukiOGLFrameBuffer::AttachTextureDepthStencil(SharedPtr<IYukiOGLTexture> tex, unsigned level)
{
  glNamedFramebufferTexture(m_nFboID, GL_DEPTH_STENCIL_ATTACHMENT, tex->GetID(), level);
}

void YukiOGLFrameBuffer::AttachRenderBufferColor(SharedPtr<IYukiOGLRenderBuffer> rbo, unsigned position)
{
  glNamedFramebufferRenderbuffer(m_nFboID, GL_COLOR_ATTACHMENT0 + position, GL_RENDERBUFFER, rbo->GetID());
}

void YukiOGLFrameBuffer::AttachRenderBufferDepth(SharedPtr<IYukiOGLRenderBuffer> rbo)
{
  glNamedFramebufferRenderbuffer(m_nFboID, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo->GetID());
}

void YukiOGLFrameBuffer::AttachRenderBufferStencil(SharedPtr<IYukiOGLRenderBuffer> rbo)
{
  glNamedFramebufferRenderbuffer(m_nFboID, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo->GetID());
}

void YukiOGLFrameBuffer::AttachRenderBufferDepthStencil(SharedPtr<IYukiOGLRenderBuffer> rbo)
{
  glNamedFramebufferRenderbuffer(m_nFboID, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo->GetID());
}

void YukiOGLFrameBuffer::Create()
{
  glCreateFramebuffers(1, &m_nFboID);
}

void YukiOGLFrameBuffer::Destroy()
{
  glDeleteFramebuffers(1, &m_nFboID);
}


} // namespace Yuki::Core