/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Graphics.hpp"

#include "PObjects.hpp"

namespace Yuki::Core
{

class YukiOGLTexture final : virtual public IOGLTexture,
                             virtual public YukiSharedObject
{
public:
  explicit YukiOGLTexture(const TextureType& type);
  ~YukiOGLTexture() override;

  void SetTextureMinFilter(TextureMinFilter minFilter) override;
  void SetTextureMagFilter(TextureMagFilter magFilter) override;
  void SetDepthStencilTextureMode(TextureDepthStencilMode mode) override;
  void SetTextureBaseLevel(int baseLevel) override;
  void SetTextureCompareFunc(TextureCompareFunc compareFunc) override;
  void SetTextureCompareMode(TextureCompareMode compareMode) override;
  void SetTextureLodBias(float bias) override;

  const TextureType             GetTextureType() override;
  const TextureMinFilter        GetTextureMinFilter() override;
  const TextureMagFilter        GetTextureMagFilter() override;
  const TextureDepthStencilMode GetDepthStencilTextureMode() override;
  const int                     GetTextureBaseLevel() override;
  const TextureCompareFunc      GetTextureCompareFunc() override;
  const TextureCompareMode      GetTextureCompareMode() override;
  const float                   GetTextureLodBias() override;

  void SetStorageData1D(
      PixelInternalFormat internalFormat, int level, const Vec1I& size
  ) override;
  void SetStorageData2D(
      PixelInternalFormat internalFormat, int level, const Vec2F& size
  ) override;
  void SetStorageData3D(
      PixelInternalFormat internalFormat, int level, const Vec3F& size
  ) override;

  void SetStorageData1D(
      PixelBasedInternalFormat internalFormat, int level, const Vec1I& size
  ) override;
  void SetStorageData2D(
      PixelBasedInternalFormat internalFormat, int level, const Vec2F& size
  ) override;
  void SetStorageData3D(
      PixelBasedInternalFormat internalFormat, int level, const Vec3F& size
  ) override;

  void SetTextureData1D(
      uint8_t* pixels, int level, PixelBasedInternalFormat imageFormat,
      const Vec1I& offset, const Vec1I& size
  ) override;
  void SetTextureData2D(
      uint8_t* pixels, int level, PixelBasedInternalFormat imageFormat,
      const Vec2I& offset, const Vec2I& size
  ) override;
  void SetTextureData3D(
      uint8_t* pixels, int level, PixelBasedInternalFormat imageFormat,
      const Vec3I& offset, const Vec3I& size
  ) override;

  unsigned GetID() override;
  void     BindObject() override;

  void GenerateMipMap() override;
  void BindTexture(unsigned slot) override;

  void Create() override;
  void Destroy() override;

private:
  unsigned    m_nTexID;
  TextureType m_eTexType;
};

} // namespace Yuki::Core
