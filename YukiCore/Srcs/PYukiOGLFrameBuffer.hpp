/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#include "YukiCore/Srcs/PYukiObject.hpp"
#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Core
{

class YukiOGLFrameBuffer final : virtual public IYukiOGLFrameBuffer,
                                 virtual public YukiObject
{
public:
  YukiOGLFrameBuffer();
  ~YukiOGLFrameBuffer() override;

  unsigned GetID() override;
  void     BindObject() override;
  bool     BufferOK() override;

  void AttachTextureColor(SharedPtr<IYukiOGLTexture> tex, unsigned position, unsigned level) override;
  void AttachTextureDepth(SharedPtr<IYukiOGLTexture> tex, unsigned level) override;
  void AttachTextureStencil(SharedPtr<IYukiOGLTexture> tex, unsigned level) override;
  void AttachTextureDepthStencil(SharedPtr<IYukiOGLTexture> tex, unsigned level) override;
  
  void AttachRenderBufferColor(SharedPtr<IYukiOGLRenderBuffer> rbo, unsigned position = 0) override;
  void AttachRenderBufferDepth(SharedPtr<IYukiOGLRenderBuffer> rbo) override;
  void AttachRenderBufferStencil(SharedPtr<IYukiOGLRenderBuffer> rbo) override;
  void AttachRenderBufferDepthStencil(SharedPtr<IYukiOGLRenderBuffer> rbo) override;

  void Create() override;
  void Destroy() override;

private:
  unsigned m_nFboID;
};

} // namespace Yuki::Core