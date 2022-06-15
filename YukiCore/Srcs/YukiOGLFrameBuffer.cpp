#include "PYukiOGLFrameBuffer.hpp"

#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Core
{

YukiOGLFrameBuffer::YukiOGLFrameBuffer()
{}

YukiOGLFrameBuffer::~YukiOGLFrameBuffer() = default;

unsigned YukiOGLFrameBuffer::GetID()
{
  return m_nFboID;
}

bool YukiOGLFrameBuffer::IsEnabledStencilTesting()
{
  return m_bStencilTesting;
}

bool YukiOGLFrameBuffer::IsEnabledBlendMode()
{
  return m_bBlendMode;
}

bool YukiOGLFrameBuffer::IsEnabledAlphaTest()
{
  return m_bAlphaTest;
}

bool YukiOGLFrameBuffer::IsEnabledDepthTest()
{
  return m_bDepthTest;
}

bool YukiOGLFrameBuffer::IsEnabledDither()
{
  return m_bDither;
}

bool YukiOGLFrameBuffer::IsEnabledHistogram()
{
  return m_bHistogram;
}

bool YukiOGLFrameBuffer::IsEnabledLineSmooth()
{
  return m_bLineSmooth;
}

void YukiOGLFrameBuffer::EnableStencilTesting()
{
  m_bStencilTesting = true;
}

void YukiOGLFrameBuffer::EnableBlendMode()
{
  m_bBlendMode = true;
}

void YukiOGLFrameBuffer::EnableAlphaTest()
{
  m_bAlphaTest = true;
}

void YukiOGLFrameBuffer::EnableDepthTest()
{
  m_bDepthTest = true;
}

void YukiOGLFrameBuffer::EnableDither()
{
  m_bDither = true;
}

void YukiOGLFrameBuffer::EnableHistogram()
{
  m_bHistogram = true;
}

void YukiOGLFrameBuffer::EnableLineSmooth()
{
  m_bLineSmooth = true;
}

void YukiOGLFrameBuffer::DisableStencilTesting()
{
  m_bStencilTesting = false;
}

void YukiOGLFrameBuffer::DisableBlendMode()
{
  m_bBlendMode = false;
}

void YukiOGLFrameBuffer::DisableAlphaTest()
{
  m_bAlphaTest = false;
}

void YukiOGLFrameBuffer::DisableDepthTest()
{
  m_bDepthTest = false;
}

void YukiOGLFrameBuffer::DisableDither()
{
  m_bDither = false;
}

void YukiOGLFrameBuffer::DisableHistogram()
{
  m_bHistogram = false;
}

void YukiOGLFrameBuffer::DisableLineSmooth()
{
  m_bLineSmooth = false;
}

void YukiOGLFrameBuffer::BindObject()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_nFboID);
}

bool YukiOGLFrameBuffer::BufferOK()
{
  return glCheckNamedFramebufferStatus(m_nFboID, GL_FRAMEBUFFER);
}

void YukiOGLFrameBuffer::AttachTextureColor(SharedPtr<IYukiOGLTexture> tex,
                                            unsigned position, unsigned level)
{
  glNamedFramebufferTexture(m_nFboID, GL_COLOR_ATTACHMENT0 + position,
                            tex->GetID(), level);
}

void YukiOGLFrameBuffer::AttachTextureDepth(SharedPtr<IYukiOGLTexture> tex,
                                            unsigned                   level)
{
  glNamedFramebufferTexture(m_nFboID, GL_DEPTH_ATTACHMENT, tex->GetID(), level);
}

void YukiOGLFrameBuffer::AttachTextureStencil(SharedPtr<IYukiOGLTexture> tex,
                                              unsigned                   level)
{
  glNamedFramebufferTexture(m_nFboID, GL_STENCIL_ATTACHMENT, tex->GetID(),
                            level);
}

void YukiOGLFrameBuffer::AttachTextureDepthStencil(
    SharedPtr<IYukiOGLTexture> tex, unsigned level)
{
  glNamedFramebufferTexture(m_nFboID, GL_DEPTH_STENCIL_ATTACHMENT, tex->GetID(),
                            level);
}

void YukiOGLFrameBuffer::AttachRenderBufferColor(
    SharedPtr<IYukiOGLRenderBuffer> rbo, unsigned position)
{
  glNamedFramebufferRenderbuffer(m_nFboID, GL_COLOR_ATTACHMENT0 + position,
                                 GL_RENDERBUFFER, rbo->GetID());
}

void YukiOGLFrameBuffer::AttachRenderBufferDepth(
    SharedPtr<IYukiOGLRenderBuffer> rbo)
{
  glNamedFramebufferRenderbuffer(m_nFboID, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
                                 rbo->GetID());
}

void YukiOGLFrameBuffer::AttachRenderBufferStencil(
    SharedPtr<IYukiOGLRenderBuffer> rbo)
{
  glNamedFramebufferRenderbuffer(m_nFboID, GL_STENCIL_ATTACHMENT,
                                 GL_RENDERBUFFER, rbo->GetID());
}

void YukiOGLFrameBuffer::AttachRenderBufferDepthStencil(
    SharedPtr<IYukiOGLRenderBuffer> rbo)
{
  glNamedFramebufferRenderbuffer(m_nFboID, GL_DEPTH_STENCIL_ATTACHMENT,
                                 GL_RENDERBUFFER, rbo->GetID());
}

void YukiOGLFrameBuffer::Create()
{
  glCreateFramebuffers(1, &m_nFboID);
}

void YukiOGLFrameBuffer::Awake()
{}

void YukiOGLFrameBuffer::Render()
{
  AutoType gfxControl = Core::GetYukiApp()->GetGraphicsController();

  this->BindObject();
  gfxControl->SetAttributeStatus(OpenGLAttribute::ALPHA_TEST, m_bAlphaTest);
  gfxControl->SetAttributeStatus(OpenGLAttribute::DEPTH_TEST, m_bDepthTest);
  gfxControl->SetAttributeStatus(OpenGLAttribute::STENCIL_TEST,
                                 m_bStencilTesting);
  gfxControl->SetAttributeStatus(OpenGLAttribute::BLEND_MODE, m_bBlendMode);
  gfxControl->SetAttributeStatus(OpenGLAttribute::DITHER, m_bDither);
  gfxControl->SetAttributeStatus(OpenGLAttribute::LINE_SMOOTH, m_bLineSmooth);
}

void YukiOGLFrameBuffer::Update()
{}

void YukiOGLFrameBuffer::Destroy()
{
  glDeleteFramebuffers(1, &m_nFboID);
}

SharedPtr<IYukiOGLFrameBuffer> CreateGLFrameBuffer()
{
  return CreateInterfaceInstance<IYukiOGLFrameBuffer, YukiOGLFrameBuffer>();
}

} // namespace Yuki::Core
