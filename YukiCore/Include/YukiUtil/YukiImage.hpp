#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Utils
{

class YUKIAPI YukiImage
{
protected:
  uint8_t* m_pData;
  int      m_nWidth;
  int      m_nHeight;
  int      m_nChannel;

public:
  YukiImage(const String& path, bool flip = false);
  YukiImage(const AsciiString& path, bool flip = false);
  virtual ~YukiImage();

  const uint8_t* GetData();
  const int&     GetWidth();
  const int&     GetHeight();
  const int&     GetDataChannel();

  SharedPtr<Core::IYukiOGLTexture> Create2DTexture(const glm::ivec2& offset, const glm::ivec2& size);
  SharedPtr<Core::IYukiOGLTexture> Create2DTexture();
};

} // namespace Yuki::Utils