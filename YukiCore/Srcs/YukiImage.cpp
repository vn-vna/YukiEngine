#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiUtil/YukiImage.hpp"

#include <stb/stb_image.h>

namespace Yuki::Utils
{

YukiImage::YukiImage(const String& path, bool flip)
{
  stbi_set_flip_vertically_on_load(!flip);
  m_pData    = stbi_load(path.c_str(), &m_nWidth, &m_nHeight, &m_nChannel, 4);
  m_nChannel = 4;
}

YukiImage::~YukiImage()
{
  stbi_image_free(m_pData);
}

const uint8_t* YukiImage::GetData()
{
  return m_pData;
}

const int& YukiImage::GetWidth()
{
  return m_nWidth;
}

const int& YukiImage::GetHeight()
{
  return m_nHeight;
}

const int& YukiImage::GetDataChannel()
{
  return m_nChannel;
}

SharedPtr<Core::IYukiOGLTexture> YukiImage::Create2DTexture(const glm::ivec2& offset, const glm::ivec2& size)
{
  SharedPtr<Core::IYukiOGLTexture> texture = Core::CreateGLTexture(Core::TextureType::TEXTURE_2D);
  texture->Create();
  texture->SetStorageData2D(Core::PixelInternalFormat::RGBA8, 4, glm::vec2{m_nWidth, m_nHeight});
  texture->SetTextureData2D(m_pData, 0, Core::PixelBasedInternalFormat::RGBA, offset, size);
  texture->SetTextureMagFilter(Core::TextureMagFilter::LINEAR);
  texture->SetTextureMinFilter(Core::TextureMinFilter::LINEAR);
  texture->GenerateMipMap();
  return texture;
}

SharedPtr<Core::IYukiOGLTexture> YukiImage::Create2DTexture()
{
  return Create2DTexture(glm::ivec2{0, 0}, glm::ivec2{m_nWidth, m_nHeight});
}

} // namespace Yuki::Utils