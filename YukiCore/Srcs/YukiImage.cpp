#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiUtil/YukiImage.hpp"

// stb image
#include <cstring>
#include <stb_image.h>

namespace Yuki::Utils
{

using Core::IYukiOGLTexture;
using Core::TextureType;
using Core::TextureMagFilter;
using Core::TextureMinFilter;
using Core::PixelInternalFormat;
using Core::PixelBasedInternalFormat;
using Core::CreateGLTexture;

YukiImage::YukiImage(const String& path, bool flip)
{
  stbi_set_flip_vertically_on_load(!flip);
  m_pData    = stbi_load(path.c_str(), &m_nWidth, &m_nHeight, &m_nChannel, 4);
  m_nChannel = 4;
}

YukiImage::YukiImage(YukiImage& image)
{
  m_nChannel = image.m_nChannel;
  m_nHeight  = image.m_nHeight;
  m_nWidth   = image.m_nWidth;

  size_t buffsz = m_nWidth * m_nHeight * m_nChannel;
  m_pData       = (uint8_t*) malloc(buffsz);
  memcpy(m_pData, image.m_pData, buffsz);
}

YukiImage::YukiImage(YukiImage&& image)
{
  m_nChannel = image.m_nChannel;
  m_nHeight  = image.m_nHeight;
  m_nWidth   = image.m_nWidth;
  m_pData    = image.m_pData;

  image.m_pData = nullptr;
}

YukiImage::~YukiImage()
{
  if (m_pData)
  {
    // stbi_image_free = free (LOL)
    // stbi_image_free(m_pData);
    free(m_pData);
  }
}

const uint8_t* YukiImage::GetData() { return m_pData; }

const int& YukiImage::GetWidth() { return m_nWidth; }

const int& YukiImage::GetHeight() { return m_nHeight; }

const int& YukiImage::GetDataChannel() { return m_nChannel; }

SharedPtr<IYukiOGLTexture> YukiImage::Create2DTexture(const Vec2I& offset, const Vec2I& size)
{
  SharedPtr<IYukiOGLTexture> texture = CreateGLTexture(TextureType::TEXTURE_2D);
  texture->Create();
  texture->SetStorageData2D(PixelInternalFormat::RGBA8, 4, Vec2F{m_nWidth, m_nHeight});
  texture->SetTextureData2D(m_pData, 0, PixelBasedInternalFormat::RGBA, offset, size);
  texture->SetTextureMagFilter(TextureMagFilter::LINEAR);
  texture->SetTextureMinFilter(TextureMinFilter::LINEAR);
  texture->GenerateMipMap();
  return texture;
}

SharedPtr<IYukiOGLTexture> YukiImage::Create2DTexture()
{
  return Create2DTexture(Vec2I{0, 0}, Vec2I{m_nWidth, m_nHeight});
}

} // namespace Yuki::Utils
