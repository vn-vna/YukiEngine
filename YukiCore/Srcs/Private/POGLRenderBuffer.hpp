/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Graphics.hpp"
#include "YukiCore/Objects.hpp"

#include "PObjects.hpp"

namespace Yuki::Core
{

class YukiOGLRenderBuffer final : virtual public IOGLRenderBuffer,
                                  virtual public YukiSharedObject
{
public:
  YukiOGLRenderBuffer();
  ~YukiOGLRenderBuffer() override;

  unsigned GetID() override;
  void     BindObject() override;

  void SetBufferStorage(PixelInternalFormat internalFormat, const Vec2I& size) override;
  void SetBufferStorageMultiSamples(PixelInternalFormat internalFormat, const Vec2I& size,
                                    int samples) override;

  void Create() override;
  void Destroy() override;

private:
  unsigned m_nRboId;
};

} // namespace Yuki::Core
