#include "YukiCore/Graphics.hpp"
#include "YukiCore/Headers.hpp"
#include "YukiDebug/Errors.hpp"

#include "Private/POGLTexture.hpp"
#include "YukiUtil/Images.hpp"

#define CHECK_VALID_TEXTURE_TYPE(type, valid)           \
  if (type != valid)                                    \
  {                                                     \
    THROW_YUKI_ERROR(OGLTextureTypeNotCompatibleError); \
  }

namespace Yuki::Core
{

YukiOGLTexture::YukiOGLTexture(const TextureType& type)
    : m_nTexID(),
      m_eTexType(type)
{}

YukiOGLTexture::~YukiOGLTexture() = default;

void YukiOGLTexture::SetTextureMinFilter(TextureMinFilter minFilter)
{
  glTextureParameteri(m_nTexID, GL_TEXTURE_MIN_FILTER, (int) minFilter);
}

void YukiOGLTexture::SetTextureMagFilter(TextureMagFilter magFilter)
{
  glTextureParameteri(m_nTexID, GL_TEXTURE_MAG_FILTER, (int) magFilter);
}

void YukiOGLTexture::SetDepthStencilTextureMode(TextureDepthStencilMode mode)
{
  glTextureParameteri(m_nTexID, GL_DEPTH_STENCIL_TEXTURE_MODE, (int) mode);
}

void YukiOGLTexture::SetTextureBaseLevel(int baseLevel)
{
  glTextureParameteri(m_nTexID, GL_TEXTURE_BASE_LEVEL, baseLevel);
}

void YukiOGLTexture::SetTextureCompareFunc(TextureCompareFunc compareFunc)
{
  glTextureParameteri(m_nTexID, GL_TEXTURE_COMPARE_FUNC, (int) compareFunc);
}

void YukiOGLTexture::SetTextureCompareMode(TextureCompareMode compareMode)
{
  glTextureParameteri(m_nTexID, GL_TEXTURE_COMPARE_MODE, (int) compareMode);
}

void YukiOGLTexture::SetTextureLodBias(float bias)
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

void YukiOGLTexture::SetStorageData1D(PixelInternalFormat internalFormat, int level,
                                      const Vec1I& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_1D);
  glTextureStorage1D(m_nTexID, level, (int) internalFormat, (int) size.x);
}

void YukiOGLTexture::SetStorageData2D(PixelInternalFormat internalFormat, int level,
                                      const Vec2F& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_2D);
  glTextureStorage2D(m_nTexID, level, (int) internalFormat, (int) size.x, (int) size.y);
}

void YukiOGLTexture::SetStorageData3D(PixelInternalFormat internalFormat, int level,
                                      const Vec3F& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_3D);
  glTextureStorage3D(m_nTexID, level, (int) internalFormat, (int) size.x, (int) size.y,
                     (int) size.z);
}

void YukiOGLTexture::SetStorageData1D(PixelBasedInternalFormat internalFormat, int level,
                                      const Vec1I& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_1D);
  glTextureStorage1D(m_nTexID, level, (int) internalFormat, (int) size.x);
}

void YukiOGLTexture::SetStorageData2D(PixelBasedInternalFormat internalFormat, int level,
                                      const Vec2F& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_2D);
  glTextureStorage2D(m_nTexID, level, (int) internalFormat, (int) size.x, (int) size.y);
}

void YukiOGLTexture::SetStorageData3D(PixelBasedInternalFormat internalFormat, int level,
                                      const Vec3F& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_3D);
  glTextureStorage3D(m_nTexID, level, (int) internalFormat, (int) size.x, (int) size.y,
                     (int) size.z);
}

void YukiOGLTexture::SetTextureData1D(uint8_t* pixels, int level,
                                      PixelBasedInternalFormat imageFormat, const Vec1I& offset,
                                      const Vec1I& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_1D);
  glTextureSubImage1D(m_nTexID, level, (int) offset.x, (int) size.x, (int) imageFormat,
                      GL_UNSIGNED_BYTE, pixels);
}

void YukiOGLTexture::SetTextureData2D(uint8_t* pixels, int level,
                                      PixelBasedInternalFormat imageFormat, const Vec2I& offset,
                                      const Vec2I& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_2D);
  glTextureSubImage2D(m_nTexID, level, (int) offset.x, (int) offset.y, (int) size.x, (int) size.y,
                      (int) imageFormat, GL_UNSIGNED_BYTE, pixels);
}

void YukiOGLTexture::SetTextureData3D(uint8_t* pixels, int level,
                                      PixelBasedInternalFormat imageFormat, const Vec3I& offset,
                                      const Vec3I& size)
{
  CHECK_VALID_TEXTURE_TYPE(m_eTexType, TextureType::TEXTURE_3D);
  glTextureSubImage3D(m_nTexID, level, (int) offset.x, (int) offset.y, (int) offset.z, (int) size.x,
                      (int) size.y, (int) size.z, (int) imageFormat, GL_UNSIGNED_BYTE, pixels);
}

unsigned YukiOGLTexture::GetID()
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

void YukiOGLTexture::BindTexture(unsigned slot)
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

SharedPtr<IOGLTexture> CreateGLTexture(TextureType type)
{
  return CreateInterfaceInstance<IOGLTexture, YukiOGLTexture>(type);
}

SharedPtr<IOGLTexture> GenerateSolid2DTexture(const Vec1F& color)
{
  AutoType solidImage = Utils::CreateSolidColorImage(color);
  return solidImage->Generate2DTexture();
}

SharedPtr<IOGLTexture> GenerateSolid2DTexture(const Vec2F& color)
{
  AutoType solidImage = Utils::CreateSolidColorImage(color);
  return solidImage->Generate2DTexture();
}

SharedPtr<IOGLTexture> GenerateSolid2DTexture(const Vec3F& color)
{
  AutoType solidImage = Utils::CreateSolidColorImage(color);
  return solidImage->Generate2DTexture();
}

SharedPtr<IOGLTexture> GenerateSolid2DTexture(const Vec4F& color)
{
  AutoType solidImage = Utils::CreateSolidColorImage(color);
  return solidImage->Generate2DTexture();
}

} // namespace Yuki::Core
