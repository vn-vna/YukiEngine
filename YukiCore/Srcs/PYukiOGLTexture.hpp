#pragma once

#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Core
{

class YukiOGLTexture : public IYukiOGLTexture
{
protected:
  unsigned    m_nTexID;
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

  const unsigned& GetID() override;
  void            BindObject() override;

  void GenerateMipMap() override;
  void BindTexture(const unsigned& slot) override;

  void Create() override;
  void Destroy() override;
};

} // namespace Yuki::Core