#include "Private/PLayer.hpp"
#include "YukiComp/Layer.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/Objects.hpp"
#include "YukiCore/Headers.hpp"

namespace Yuki::Comp
{

using Core::CreateGLFrameBuffer;
using Core::CreateGLRegnderBuffer;
using Core::CreateGLTexture;
using Core::TextureType;

YukiLayer::YukiLayer(unsigned width, unsigned height)
    : m_nWidth(width),
      m_nHeight(height)
{
  m_pFrameBuffer    = CreateGLFrameBuffer();
  m_pRenderBuffer   = CreateGLRegnderBuffer();
  m_pColorTexture   = CreateGLTexture(TextureType::TEXTURE_2D);
  m_pDepthTexture   = CreateGLTexture(TextureType::TEXTURE_2D);
  m_pStencilTexture = CreateGLTexture(TextureType::TEXTURE_2D);
}

YukiLayer::~YukiLayer() = default;

SharedPtr<IOGLFrameBuffer> YukiLayer::GetFrameBuffer()
{
  return m_pFrameBuffer;
}

SharedPtr<IOGLRenderBuffer> YukiLayer::GetRenderBuffer()
{
  return m_pRenderBuffer;
}

SharedPtr<IOGLTexture> YukiLayer::GetDepthTexture()
{
  return m_pDepthTexture;
}

SharedPtr<IOGLTexture> YukiLayer::GetStencilTexture()
{
  return m_pStencilTexture;
}

SharedPtr<IOGLTexture> YukiLayer::GetColorTexture()
{
  return m_pColorTexture;
}

void YukiLayer::Create()
{
  m_pFrameBuffer->Require();

  m_pRenderBuffer->Require();

  m_pColorTexture->Require();
  m_pColorTexture->SetStorageData2D(
      Core::PixelInternalFormat::RGBA8, 4, Vec2F {m_nWidth, m_nHeight}
  );
  m_pColorTexture->SetTextureData2D(
      nullptr, 0, Core::PixelBasedInternalFormat::RGBA, {0, 0},
      {m_nWidth, m_nHeight}
  );
  m_pColorTexture->SetTextureMagFilter(Core::TextureMagFilter::LINEAR);
  m_pColorTexture->SetTextureMinFilter(Core::TextureMinFilter::LINEAR);

  m_pFrameBuffer->AttachRenderBufferColor(m_pRenderBuffer);
  m_pFrameBuffer->AttachTextureColor(m_pColorTexture);
}

void YukiLayer::Awake()
{}

void YukiLayer::Render()
{
  m_pRenderBuffer->Render();
}

void YukiLayer::Update()
{}

void YukiLayer::Destroy()
{
  m_pColorTexture->Release();
  m_pRenderBuffer->Release();
  m_pFrameBuffer->Release();
}

SharedPtr<ILayer>
CreateYukiLayer(unsigned width, unsigned height, unsigned multiSample)
{
  AutoType layer =
      Core::CreateInterfaceInstance<ILayer, YukiLayer>(width, height);
  return layer;
}

} // namespace Yuki::Comp
