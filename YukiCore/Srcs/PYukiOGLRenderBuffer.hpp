/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiObject.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

class YukiOGLRenderBuffer final : virtual public IYukiOGLRenderBuffer,
                                  virtual public YukiSharedObject
{
public:
  YukiOGLRenderBuffer();
  ~YukiOGLRenderBuffer() override;

  unsigned GetID() override;
  void     BindObject() override;

  void SetBufferStorage(PixelInternalFormat internalFormat,
                        const Vec2I&        size) override;
  void SetBufferStorageMultiSamples(PixelInternalFormat internalFormat,
                                    const Vec2I& size, int samples) override;

  void Create() override;
  void Destroy() override;

private:
  unsigned m_nRboId;
};

} // namespace Yuki::Core
