#include "YukiCore/YukiPCH.hpp"

#include "PYukiOGLTexture.hpp"

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