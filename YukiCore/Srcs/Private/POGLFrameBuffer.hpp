/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "PObjects.hpp"
#include "YukiCore/Graphics.hpp"

namespace Yuki::Core
{

class YukiOGLFrameBuffer final : virtual public IOGLFrameBuffer,
                                 virtual public YukiSharedObject
{
public:
  YukiOGLFrameBuffer();
  ~YukiOGLFrameBuffer() override;

  bool IsEnabledStencilTesting() override;
  bool IsEnabledBlendMode() override;
  bool IsEnabledAlphaTest() override;
  bool IsEnabledDepthTest() override;
  bool IsEnabledDither() override;
  bool IsEnabledHistogram() override;
  bool IsEnabledLineSmooth() override;

  void EnableStencilTesting() override;
  void EnableBlendMode() override;
  void EnableAlphaTest() override;
  void EnableDepthTest() override;
  void EnableDither() override;
  void EnableHistogram() override;
  void EnableLineSmooth() override;

  void DisableStencilTesting() override;
  void DisableBlendMode() override;
  void DisableAlphaTest() override;
  void DisableDepthTest() override;
  void DisableDither() override;
  void DisableHistogram() override;
  void DisableLineSmooth() override;

  unsigned GetID() override;
  void     BindObject() override;
  bool     BufferOK() override;

  void AttachTextureColor(SharedPtr<IOGLTexture> tex, unsigned position,
                          unsigned level) override;
  void AttachTextureDepth(SharedPtr<IOGLTexture> tex, unsigned level) override;
  void AttachTextureStencil(SharedPtr<IOGLTexture> tex,
                            unsigned               level) override;
  void AttachTextureDepthStencil(SharedPtr<IOGLTexture> tex,
                                 unsigned               level) override;

  void AttachRenderBufferColor(SharedPtr<IOGLRenderBuffer> rbo,
                               unsigned position = 0) override;
  void AttachRenderBufferDepth(SharedPtr<IOGLRenderBuffer> rbo) override;
  void AttachRenderBufferStencil(SharedPtr<IOGLRenderBuffer> rbo) override;
  void AttachRenderBufferDepthStencil(SharedPtr<IOGLRenderBuffer> rbo) override;

  void Create() override;
  void Awake() override;
  void Render() override;
  void Update() override;
  void Destroy() override;

private:
  unsigned m_nFboID;
  bool     m_bStencilTesting;
  bool     m_bBlendMode;
  bool     m_bAlphaTest;
  bool     m_bDepthTest;
  bool     m_bDither;
  bool     m_bHistogram;
  bool     m_bLineSmooth;
};

} // namespace Yuki::Core
