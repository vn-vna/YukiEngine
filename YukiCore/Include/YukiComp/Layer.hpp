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

using Core::IOGLFrameBuffer;
using Core::IOGLRenderBuffer;
using Core::IOGLTexture;
using Core::ISharedObject;

class ILayer : virtual public ISharedObject
{
public:
  virtual SharedPtr<IOGLFrameBuffer>  GetFrameBuffer()    = 0;
  virtual SharedPtr<IOGLRenderBuffer> GetRenderBuffer()   = 0;
  virtual SharedPtr<IOGLTexture>      GetDepthTexture()   = 0;
  virtual SharedPtr<IOGLTexture>      GetStencilTexture() = 0;
  virtual SharedPtr<IOGLTexture>      GetColorTexture()   = 0;
};

SharedPtr<ILayer> CreateYukiLayer(unsigned width = 0, unsigned height = 0,
                                  unsigned multiSamples = 1);

} // namespace Yuki::Comp
