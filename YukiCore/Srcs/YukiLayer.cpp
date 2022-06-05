#include "PYukiLayer.hpp"
#include "YukiComp/YukiLayer.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiPCH.hpp"

namespace Yuki::Comp
{

using Core::TextureType;
using Core::CreateGLFrameBuffer;
using Core::CreateGLRegnderBuffer;
using Core::CreateGLTexture;

YukiLayer::YukiLayer(unsigned width, unsigned height) : m_nWidth(width), m_nHeight(height)
{
  m_pFrameBuffer    = CreateGLFrameBuffer();
  m_pRenderBuffer   = CreateGLRegnderBuffer();
  m_pColorTexture   = CreateGLTexture(TextureType::TEXTURE_2D);
  m_pDepthTexture   = CreateGLTexture(TextureType::TEXTURE_2D);
  m_pStencilTexture = CreateGLTexture(TextureType::TEXTURE_2D);
}

YukiLayer::~YukiLayer() = default;

SharedPtr<IYukiOGLFrameBuffer> YukiLayer::GetFrameBuffer() { return m_pFrameBuffer; }

SharedPtr<IYukiOGLRenderBuffer> YukiLayer::GetRenderBuffer() { return m_pRenderBuffer; }

SharedPtr<IYukiOGLTexture> YukiLayer::GetDepthTexture() { return m_pDepthTexture; }

SharedPtr<IYukiOGLTexture> YukiLayer::GetStencilTexture() { return m_pStencilTexture; }

SharedPtr<IYukiOGLTexture> YukiLayer::GetColorTexture() { return m_pColorTexture; }

void YukiLayer::Create()
{
  m_pFrameBuffer->Create();

  m_pRenderBuffer->Create();

  m_pColorTexture->Create();
  m_pColorTexture->SetStorageData2D(Core::PixelInternalFormat::RGBA8, 4, Vec2F{m_nWidth, m_nHeight});
  m_pColorTexture->SetTextureData2D(nullptr, 0, Core::PixelBasedInternalFormat::RGBA, {0, 0}, {m_nWidth, m_nHeight});
  m_pColorTexture->SetTextureMagFilter(Core::TextureMagFilter::LINEAR);
  m_pColorTexture->SetTextureMinFilter(Core::TextureMinFilter::LINEAR);

  m_pFrameBuffer->AttachRenderBufferColor(m_pRenderBuffer);
  m_pFrameBuffer->AttachTextureColor(m_pColorTexture);
}

void YukiLayer::Awake() {}

void YukiLayer::Render() { m_pRenderBuffer->Render(); }

void YukiLayer::Update() {}

void YukiLayer::Destroy()
{
  m_pColorTexture->Destroy();
  m_pRenderBuffer->Destroy();
  m_pFrameBuffer->Destroy();
}

SharedPtr<IYukiLayer> CreateYukiLayer(unsigned width, unsigned height, unsigned multiSample)
{
  AutoType layer = Core::CreateInterfaceInstance<IYukiLayer, YukiLayer>(width, height);
  return layer;
}

} // namespace Yuki::Comp
