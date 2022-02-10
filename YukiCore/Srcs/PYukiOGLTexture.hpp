#pragma once

#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Core
{

class YukiOGLTexture : public virtual IYukiOGLTexture
{
protected:
  unsigned    m_nTexID;
  int         m_nRequired;
  TextureType m_eTexType;

public:
  YukiOGLTexture(const TextureType& type);
  virtual ~YukiOGLTexture() = default;

  void SetTextureMinFilter(const TextureMinFilter& minFilter) override;
  void SetTextureMagFilter(const TextureMagFilter& magFilter) override;
  void SetDepthStencilTextureMode(const TextureDepthStencilMode& mode) override;
  void SetTextureBaseLevel(const int& baseLevel) override;
  void SetTextureCompareFunc(const TextureCompareFunc& compareFunc) override;
  void SetTextureCompareMode(const TextureCompareMode& compareMode) override;
  void SetTextureLodBias(const float& bias) override;

  const TextureType             GetTextureType() override;
  const TextureMinFilter        GetTextureMinFilter() override;
  const TextureMagFilter        GetTextureMagFilter() override;
  const TextureDepthStencilMode GetDepthStencilTextureMode() override;
  const int                     GetTextureBaseLevel() override;
  const TextureCompareFunc      GetTextureCompareFunc() override;
  const TextureCompareMode      GetTextureCompareMode() override;
  const float                   GetTextureLodBias() override;

  void SetStorageData1D(
      const PixelInternalFormat& internalFormat, const int& level,
      const glm::vec1& size);
  void SetStorageData2D(
      const PixelInternalFormat& internalFormat, const int& level,
      const glm::vec2& size);
  void SetStorageData3D(
      const PixelInternalFormat& internalFormat, const int& level,
      const glm::vec3& size);

  void SetStorageData1D(
      const PixelBasedInternalFormat& internalFormat, const int& level,
      const glm::vec1& size);
  void SetStorageData2D(
      const PixelBasedInternalFormat& internalFormat, const int& level,
      const glm::vec2& size);
  void SetStorageData3D(
      const PixelBasedInternalFormat& internalFormat, const int& level,
      const glm::vec3& size);

  void SetTextureData1D(
      uint8_t* pixels, const int& level,
      const PixelBasedInternalFormat& imageFormat,
      const glm::ivec1& offset, const glm::ivec1& size) override;
  void SetTextureData2D(
      uint8_t* pixels, const int& level,
      const PixelBasedInternalFormat& imageFormat,
      const glm::ivec2& offset, const glm::ivec2& size) override;
  void SetTextureData3D(
      uint8_t* pixels, const int& level,
      const PixelBasedInternalFormat& imageFormat,
      const glm::ivec3& offset, const glm::ivec3& size) override;

  const unsigned& GetID() override;
  void            BindObject() override;

  void GenerateMipMap() override;
  void BindTexture(const unsigned& slot) override;

  void Create() override;
  void Destroy() override;
};

} // namespace Yuki::Core
