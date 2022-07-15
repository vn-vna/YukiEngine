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

  SharedPtr<IOGLFrameBuffer>  GetFrameBuffer() override;
  SharedPtr<IOGLRenderBuffer> GetRenderBuffer() override;
  SharedPtr<IOGLTexture>      GetDepthTexture() override;
  SharedPtr<IOGLTexture>      GetStencilTexture() override;
  SharedPtr<IOGLTexture>      GetColorTexture() override;

  void Create() override;
  void Awake() override;
  void Render() override;
  void Update() override;
  void Destroy() override;

private:
  SharedPtr<IOGLFrameBuffer>  m_pFrameBuffer;
  SharedPtr<IOGLRenderBuffer> m_pRenderBuffer;
  SharedPtr<IOGLTexture>      m_pDepthTexture;
  SharedPtr<IOGLTexture>      m_pStencilTexture;
  SharedPtr<IOGLTexture>      m_pColorTexture;

  unsigned m_nWidth;
  unsigned m_nHeight;
};

} // namespace Yuki::Comp
