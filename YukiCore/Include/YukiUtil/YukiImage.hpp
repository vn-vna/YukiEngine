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

class YUKIAPI YukiImage
{
protected:
  uint8_t* m_pData;
  int      m_nWidth;
  int      m_nHeight;
  int      m_nChannel;

public:
  explicit YukiImage(const String& path, bool flip = false);
  virtual ~YukiImage();

  const uint8_t* GetData();
  const int&     GetWidth();
  const int&     GetHeight();
  const int&     GetDataChannel();

  SharedPtr<IYukiOGLTexture> Create2DTexture(const Vec2I& offset, const Vec2I& size);
  SharedPtr<IYukiOGLTexture> Create2DTexture();
};

} // namespace Yuki::Utils