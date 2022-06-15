/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Utils
{

using Core::IYukiOGLTexture;

class YukiImage
{
protected:
  uint8_t* m_pData;
  int      m_nWidth;
  int      m_nHeight;
  int      m_nChannel;

public:
  explicit YukiImage(const String& path, bool flip = false);
  YukiImage(YukiImage& image);
  YukiImage(YukiImage&& image);
  YukiImage(uint8_t* pData, int w, int h, int channel);
  virtual ~YukiImage();

  const uint8_t* GetData();
  const int&     GetWidth();
  const int&     GetHeight();
  const int&     GetDataChannel();

  SharedPtr<IYukiOGLTexture> Generate2DTexture(const Vec2I& offset,
                                               const Vec2I& size);
  SharedPtr<IYukiOGLTexture> Generate2DTexture();
};

SharedPtr<YukiImage> CreateSolidColorImage(const Vec1F& color,
                                           const Vec2I& size = {10, 10});
SharedPtr<YukiImage> CreateSolidColorImage(const Vec2F& color,
                                           const Vec2I& size = {10, 10});
SharedPtr<YukiImage> CreateSolidColorImage(const Vec3F& color,
                                           const Vec2I& size = {10, 10});
SharedPtr<YukiImage> CreateSolidColorImage(const Vec4F& color,
                                           const Vec2I& size = {10, 10});

} // namespace Yuki::Utils
