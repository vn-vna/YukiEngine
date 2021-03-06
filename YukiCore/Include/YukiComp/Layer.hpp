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

using Core::ISharedObject;

class ILayer : virtual public ISharedObject
{
public:
  virtual SPIOGLFrameBuffer  GetFrameBuffer()    = 0;
  virtual SPIOGLRenderBuffer GetRenderBuffer()   = 0;
  virtual SPIOGLTexture      GetDepthTexture()   = 0;
  virtual SPIOGLTexture      GetStencilTexture() = 0;
  virtual SPIOGLTexture      GetColorTexture()   = 0;
};

SharedPtr<ILayer> CreateYukiLayer(unsigned width = 0, unsigned height = 0,
                                  unsigned multiSamples = 1);

} // namespace Yuki::Comp
