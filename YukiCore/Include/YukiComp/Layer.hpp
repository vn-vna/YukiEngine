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
#include "YukiCore/Headers.hpp"

namespace Yuki::Comp
{

using Core::IYukiOGLFrameBuffer;
using Core::IYukiOGLRenderBuffer;
using Core::IYukiOGLTexture;
using Core::IYukiSharedObject;

class IYukiLayer : virtual public IYukiSharedObject
{
public:
  virtual SharedPtr<IYukiOGLFrameBuffer>  GetFrameBuffer()    = 0;
  virtual SharedPtr<IYukiOGLRenderBuffer> GetRenderBuffer()   = 0;
  virtual SharedPtr<IYukiOGLTexture>      GetDepthTexture()   = 0;
  virtual SharedPtr<IYukiOGLTexture>      GetStencilTexture() = 0;
  virtual SharedPtr<IYukiOGLTexture>      GetColorTexture()   = 0;
};

SharedPtr<IYukiLayer> CreateYukiLayer(unsigned width = 0, unsigned height = 0,
                                      unsigned multiSamples = 1);

} // namespace Yuki::Comp
