#include "YukiCore/Application.hpp"
#include "YukiCore/Headers.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiUtil/Images.hpp"

#include <glm/gtc/type_ptr.hpp>

// stb image
#include <stb_image.h>

namespace Yuki::Utils
{

using Core::CreateGLTexture;
using Core::IOGLTexture;
using Core::MakeShared;
using Core::PixelBasedInternalFormat;
using Core::PixelInternalFormat;
using Core::TextureMagFilter;
using Core::TextureMinFilter;
using Core::TextureType;

Images::Images(const String& path, bool flip)
    : m_nWidth(0),
      m_nHeight(0)
{
  stbi_set_flip_vertically_on_load(!flip);
  m_pData    = stbi_load(path.c_str(), &m_nWidth, &m_nHeight, &m_nChannel, 4);
  m_nChannel = 4;
}

Images::Images(Images& image)
{
  m_nChannel = image.m_nChannel;
  m_nHeight  = image.m_nHeight;
  m_nWidth   = image.m_nWidth;

  size_t buffsz = m_nWidth * m_nHeight * m_nChannel;
  m_pData       = (uint8_t*) malloc(buffsz);
  memcpy(m_pData, image.m_pData, buffsz);
}

Images::Images(Images&& image)
{
  m_nChannel = image.m_nChannel;
  m_nHeight  = image.m_nHeight;
  m_nWidth   = image.m_nWidth;
  m_pData    = image.m_pData;

  image.m_pData = nullptr;
}

Images::Images(uint8_t* pData, int w, int h, int channel)
{
  m_pData    = pData;
  m_nWidth   = w;
  m_nHeight  = h;
  m_nChannel = channel;
}

Images::~Images()
{
  if (m_pData)
  {
    // stbi_image_free is actually stdlib.h->::free (LOL)
    // stbi_image_free(m_pData);
    free(m_pData);
  }
}

const uint8_t* Images::GetData()
{
  return m_pData;
}

const int& Images::GetWidth()
{
  return m_nWidth;
}

const int& Images::GetHeight()
{
  return m_nHeight;
}

const int& Images::GetDataChannel()
{
  return m_nChannel;
}

PixelBasedInternalFormat getPixelBasedInternalFormat(int channel)
{
  switch (channel)
  {
  case 1:
    return PixelBasedInternalFormat::RED;
  case 2:
    return PixelBasedInternalFormat::RG;
  case 3:
    return PixelBasedInternalFormat::RGB;
  case 4:
    return PixelBasedInternalFormat::RGBA;
  default:
    return PixelBasedInternalFormat::RGBA;
  }
}

PixelInternalFormat getInternalFormat(int channel)
{
  switch (channel)
  {
  case 1:
    return PixelInternalFormat::R8;
  case 2:
    return PixelInternalFormat::RG8;
  case 3:
    return PixelInternalFormat::RGB8;
  case 4:
    return PixelInternalFormat::RGBA8;
  default:
    return PixelInternalFormat::RGBA8;
  }
}

SharedPtr<IOGLTexture>
Images::Generate2DTexture(const Vec2I& offset, const Vec2I& size)
{
  SharedPtr<IOGLTexture> texture = CreateGLTexture(TextureType::TEXTURE_2D);
  texture->Require();
  texture->SetStorageData2D(
      getInternalFormat(m_nChannel), 4, Vec2F {m_nWidth, m_nHeight}
  );
  texture->SetTextureData2D(
      m_pData, 0, getPixelBasedInternalFormat(m_nChannel), offset, size
  );
  texture->SetTextureMagFilter(TextureMagFilter::LINEAR);
  texture->SetTextureMinFilter(TextureMinFilter::LINEAR);
  texture->GenerateMipMap();
  return texture;
}

SharedPtr<IOGLTexture> Images::Generate2DTexture()
{
  return Generate2DTexture(Vec2I {0, 0}, Vec2I {m_nWidth, m_nHeight});
}

uint8_t* createSolidColorArray(int w, int h, int channel, const float* color)
{
  AutoType* pData = (uint8_t*) std::malloc(w * h * channel);
  for (int px = 0; px < w * h; ++px)
  {
    for (int c = 0; c < channel; ++c)
    {
      AutoType fp             = color[c] * 255.0f;
      pData[px * channel + c] = fp;
    }
  }
  return pData;
}

SharedPtr<Images> CreateSolidColorImage(const Vec1F& color, const Vec2I& size)
{
  uint8_t* pData = createSolidColorArray(size.x, size.y, 1, &color.r);
  return MakeShared<Images>(pData, size.x, size.y, 1);
}

SharedPtr<Images> CreateSolidColorImage(const Vec2F& color, const Vec2I& size)
{
  uint8_t* pData =
      createSolidColorArray(size.x, size.y, 2, glm::value_ptr(color));
  return MakeShared<Images>(pData, size.x, size.y, 2);
}

SharedPtr<Images> CreateSolidColorImage(const Vec3F& color, const Vec2I& size)
{
  uint8_t* pData =
      createSolidColorArray(size.x, size.y, 3, glm::value_ptr(color));
  return MakeShared<Images>(pData, size.x, size.y, 3);
}

SharedPtr<Images> CreateSolidColorImage(const Vec4F& color, const Vec2I& size)
{
  uint8_t* pData =
      createSolidColorArray(size.x, size.y, 4, glm::value_ptr(color));
  return MakeShared<Images>(pData, size.x, size.y, 4);
}

} // namespace Yuki::Utils
