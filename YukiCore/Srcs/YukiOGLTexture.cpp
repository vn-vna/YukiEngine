#include "YukiCore/YukiPCH.hpp"
#include "YukiDebug/YukiError.hpp"

#include "PYukiOGLTexture.hpp"

#define CHECK_VALID_TEXTURE_TYPE(type, valid)                 \
  if (type != valid)                                          \
  {                                                           \
    THROW_YUKI_ERROR(Debug::YukiOGLTextureTypeNotCompatible); \
  }

namespace Yuki::Core
{

YukiOGLTexture::YukiOGLTexture(const TextureType& type)
    : m_nTexID(), m_eTexType(type)
{}

void YukiOGLTexture::SetTextureMinFilter(const TextureMinFilter& minFilter)
{
  glTextureParameteri(m_nTexID, GL_TEXTURE_MIN_FILTER, (int) minFilter);
}

void YukiOGLTexture::SetTextureMagFilter(const TextureMagFilter& magFilter)
{
  glTextureParameteri(m_nTexID, GL_TEXTURE_MAG_FILTER, (int) magFilter);
}

void YukiOGLTexture::SetDepthStencilTextureMode(const TextureDepthStencilMode& mode)
{
  glTextureParameteri(m_nTexID, GL_DEPTH_STENCIL_TEXTURE_MODE, (int) mode);
}

void YukiOGLTexture::SetTextureBaseLevel(const int& baseLevel)
{
  glTextureParameteri(m_nTexID, GL_TEXTURE_BASE_LEVEL, baseLevel);
}

void YukiOGLTexture::SetTextureCompareFunc(const TextureCompareFunc& compareFunc)
{
  glTextureParameteri(m_nTexID, GL_TEXTURE_COMPARE_FUNC, (int) compareFunc);
}

void YukiOGLTexture::SetTextureCompareMode(const TextureCompareMode& compareMode)
{
  glTextureParameteri(m_nTexID, GL_TEXTURE_COMPARE_MODE, (int) compareMode);
}

void YukiOGLTexture::SetTextureLodBias(const float& bias)
{
  glTextureParameterf(m_nTexID, GL_TEXTURE_LOD_BIAS, bias);
}

const TextureType YukiOGLTexture::GetTextureType()
{
  return m_eTexType;
}

const TextureMinFilter YukiOGLTexture::GetTextureMinFilter()
{
  int param;
  glGetTextureParameteriv(m_nTexID, GL_TEXTURE_MIN_FILTER, &param);
  return (TextureMinFilter) param;
}

const TextureMagFilter YukiOGLTexture::GetTextureMagFilter()
{
  int param;
  glGetTextureParameteriv(m_nTexID, GL_TEXTURE_MAG_FILTER, &param);
  return (TextureMagFilter) param;
}

const TextureDepthStencilMode YukiOGLTexture::GetDepthStencilTextureMode()
{
  int param;
  glGetTextureParameteriv(m_nTexID, GL_DEPTH_STENCIL_TEXTURE_MODE, &param);
  return (TextureDepthStencilMode) param;
}

const int YukiOGLTexture::GetTextureBaseLevel()
{
  int param;
  glGetTextureParameteriv(m_nTexID, GL_TEXTURE_BASE_LEVEL, &param);
  return param;
}

const TextureCompareFunc YukiOGLTexture::GetTextureCompareFunc()
{
  int param;
  glGetTextureParameteriv(m_nTexID, GL_TEXTURE_COMPARE_FUNC, &param);
  return (TextureCompareFunc) param;
}

const TextureCompareMode YukiOGLTexture::GetTextureCompareMode()
{
  int param;
  glGetTextureParameteriv(m_nTexID, GL_TEXTURE_COMPARE_MODE, &param);
  return (TextureCompareMode) param;
}

const float YukiOGLTexture::GetTextureLodBias()
{
  float param;
  glGetTextureParameterfv(m_nTexID, GL_TEXTURE_LOD_BIAS, &param);
  return param;
}

void YukiOGLTexture::SetStorageData1D(
    const PixelInternalFormat& internalFormat, const int& level,
    const glm::vec1& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_1D);
  glTextureStorage1D(m_nTexID, level, (int) internalFormat, (int) size.x);
}

void YukiOGLTexture::SetStorageData2D(
    const PixelInternalFormat& internalFormat, const int& level,
    const glm::vec2& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_2D);
  glTextureStorage2D(m_nTexID, level, (int) internalFormat, (int) size.x, (int) size.y);
}

void YukiOGLTexture::SetStorageData3D(
    const PixelInternalFormat& internalFormat, const int& level,
    const glm::vec3& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_3D);
  glTextureStorage3D(m_nTexID, level, (int) internalFormat, (int) size.x, (int) size.y, (int) size.z);
}

void YukiOGLTexture::SetStorageData1D(
    const PixelBasedInternalFormat& internalFormat, const int& level,
    const glm::vec1& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_1D);
  glTextureStorage1D(m_nTexID, level, (int) internalFormat, (int) size.x);
}

void YukiOGLTexture::SetStorageData2D(
    const PixelBasedInternalFormat& internalFormat, const int& level,
    const glm::vec2& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_2D);
  glTextureStorage2D(m_nTexID, level, (int) internalFormat, (int) size.x, (int) size.y);
}

void YukiOGLTexture::SetStorageData3D(
    const PixelBasedInternalFormat& internalFormat, const int& level,
    const glm::vec3& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_3D);
  glTextureStorage3D(m_nTexID, level, (int) internalFormat, (int) size.x, (int) size.y, (int) size.z);
}

void YukiOGLTexture::SetTextureData1D(
    uint8_t* pixels, const int& level,
    const PixelBasedInternalFormat& imageFormat,
    const glm::ivec1& offset, const glm::ivec1& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_1D);
  glTextureSubImage1D(
      m_nTexID, level,
      (int) offset.x,
      (int) size.x,
      (int) imageFormat, GL_UNSIGNED_BYTE, pixels);
}

void YukiOGLTexture::SetTextureData2D(
    uint8_t* pixels, const int& level,
    const PixelBasedInternalFormat& imageFormat,
    const glm::ivec2& offset, const glm::ivec2& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_2D);
  glTextureSubImage2D(
      m_nTexID, level,
      (int) offset.x, (int) offset.y,
      (int) size.x, (int) size.y,
      (int) imageFormat, GL_UNSIGNED_BYTE, pixels);
}

void YukiOGLTexture::SetTextureData3D(
    uint8_t* pixels, const int& level,
    const PixelBasedInternalFormat& imageFormat,
    const glm::ivec3& offset, const glm::ivec3& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_3D);
  glTextureSubImage3D(
      m_nTexID, level,
      (int) offset.x, (int) offset.y, (int) offset.z,
      (int) size.x, (int) size.y, (int) size.z,
      (int) imageFormat, GL_UNSIGNED_BYTE, pixels);
}

const unsigned& YukiOGLTexture::GetID()
{
  return m_nTexID;
}

void YukiOGLTexture::BindObject()
{
  glBindTexture((int) m_eTexType, m_nTexID);
}

void YukiOGLTexture::GenerateMipMap()
{
  glGenerateTextureMipmap(m_nTexID);
}

void YukiOGLTexture::BindTexture(const unsigned& slot)
{
  glActiveTexture(GL_TEXTURE0 + slot);
  BindObject();
}

void YukiOGLTexture::Create()
{
  glCreateTextures((int) m_eTexType, 1, &m_nTexID);
}

void YukiOGLTexture::Destroy()
{
  glDeleteTextures(1, &m_nTexID);
}

SharedPtr<IYukiOGLTexture> CreateGLTexture(const TextureType& type)
{
  return {(IYukiOGLTexture*) new YukiOGLTexture(type), std::default_delete<IYukiOGLTexture>()};
}

} // namespace Yuki::Core