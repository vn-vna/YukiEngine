#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiUtil/YukiImage.hpp"

// stb image
#include <cstdlib>
#include <cstring>
#include <glm/gtc/type_ptr.hpp>
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

YukiImage::YukiImage(uint8_t* pData, int w, int h, int channel)
{
  m_pData    = pData;
  m_nWidth   = w;
  m_nHeight  = h;
  m_nChannel = channel;
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

uint8_t* createSolidColorArray(int w, int h, int channel, const float* color)
{
  AutoType logger = Core::GetYukiApp()->GetLogger();
  uint8_t* pData  = (uint8_t*) std::malloc(w * h * channel);
  for (int px = 0; px <= w * h; ++px)
  {
    for (int c = 0; c < channel; ++c)
    {
      AutoType fp             = color[c] * 255.0f;
      pData[px * channel + c] = fp;
    }
    std::cout << "\n";
  }
  return pData;
}

YukiImage CreateSolidColorImage(const Vec3F& color, const Vec2I& size)
{
  uint8_t* pData = createSolidColorArray(size.x, size.y, 3, glm::value_ptr(color));
  return {pData, size.x, size.y, 3};
}

YukiImage CreateSolidColorImage(const Vec4F& color, const Vec2I& size)
{
  uint8_t* pData = createSolidColorArray(size.x, size.y, 4, glm::value_ptr(color));
  return {pData, size.x, size.y, 4};
}

} // namespace Yuki::Utils
