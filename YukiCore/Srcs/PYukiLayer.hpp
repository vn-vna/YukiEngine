/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiComp/YukiLayer.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Comp
{

using Core::YukiObject;

class YukiLayer final : virtual public IYukiLayer, virtual public YukiObject
{
public:
  YukiLayer(unsigned width, unsigned height);
  ~YukiLayer() override;

  SharedPtr<IYukiOGLFrameBuffer>  GetFrameBuffer() override;
  SharedPtr<IYukiOGLRenderBuffer> GetRenderBuffer() override;
  SharedPtr<IYukiOGLTexture>      GetDepthTexture() override;
  SharedPtr<IYukiOGLTexture>      GetStencilTexture() override;
  SharedPtr<IYukiOGLTexture>      GetColorTexture() override;

  void Create() override;
  void Awake() override;
  void Render() override;
  void Update() override;
  void Destroy() override;

private:
  SharedPtr<IYukiOGLFrameBuffer>  m_pFrameBuffer;
  SharedPtr<IYukiOGLRenderBuffer> m_pRenderBuffer;
  SharedPtr<IYukiOGLTexture>      m_pDepthTexture;
  SharedPtr<IYukiOGLTexture>      m_pStencilTexture;
  SharedPtr<IYukiOGLTexture>      m_pColorTexture;

  unsigned m_nWidth;
  unsigned m_nHeight;
};

} // namespace Yuki::Comp
