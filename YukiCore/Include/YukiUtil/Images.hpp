/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/Objects.hpp"

namespace Yuki::Utils
{

using Core::IOGLTexture;

class Images
{

public:
  explicit Images(const String& path, bool flip = false);
  Images(Images& image);
  Images(Images&& image);
  Images(uint8_t* pData, int w, int h, int channel);
  virtual ~Images();

  const uint8_t* GetData();
  const int&     GetWidth();
  const int&     GetHeight();
  const int&     GetDataChannel();

  SharedPtr<IOGLTexture> Generate2DTexture(const Vec2I& offset,
                                           const Vec2I& size);
  SharedPtr<IOGLTexture> Generate2DTexture();

protected:
  uint8_t* m_pData;
  int      m_nWidth;
  int      m_nHeight;
  int      m_nChannel;
};

class TextureInstruction
{};

SharedPtr<Images> CreateSolidColorImage(const Vec1F& color,
                                        const Vec2I& size = {10, 10});
SharedPtr<Images> CreateSolidColorImage(const Vec2F& color,
                                        const Vec2I& size = {10, 10});
SharedPtr<Images> CreateSolidColorImage(const Vec3F& color,
                                        const Vec2I& size = {10, 10});
SharedPtr<Images> CreateSolidColorImage(const Vec4F& color,
                                        const Vec2I& size = {10, 10});

} // namespace Yuki::Utils
