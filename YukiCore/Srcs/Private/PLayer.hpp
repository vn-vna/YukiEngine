/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiComp/Layer.hpp"

#include "PObjects.hpp"
#include "YukiCore/Objects.hpp"

namespace Yuki::Comp
{

using Core::YukiSharedObject;

class YukiLayer final : virtual public ILayer,
                        virtual public YukiSharedObject
{
public:
  YukiLayer(unsigned width, unsigned height);
  ~YukiLayer() override;

  SPIOGLFrameBuffer  GetFrameBuffer() override;
  SPIOGLRenderBuffer GetRenderBuffer() override;
  SPIOGLTexture      GetDepthTexture() override;
  SPIOGLTexture      GetStencilTexture() override;
  SPIOGLTexture      GetColorTexture() override;

  void Create() override;
  void Awake() override;
  void Render() override;
  void Update() override;
  void Destroy() override;

private:
  SPIOGLFrameBuffer  m_pFrameBuffer;
  SPIOGLRenderBuffer m_pRenderBuffer;
  SPIOGLTexture      m_pDepthTexture;
  SPIOGLTexture      m_pStencilTexture;
  SPIOGLTexture      m_pColorTexture;

  unsigned m_nWidth;
  unsigned m_nHeight;
};

} // namespace Yuki::Comp
