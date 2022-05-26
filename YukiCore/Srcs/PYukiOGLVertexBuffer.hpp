/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiDebug/YukiError.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

class YukiOGLVertexBuffer final : virtual public IYukiOGLVertexBuffer,
                                  virtual public YukiObject
{
public:
  YukiOGLVertexBuffer();
  ~YukiOGLVertexBuffer() override;

  bool     OnUse();
  unsigned GetID() override;
  void     BindObject() override;
  void     SetBufferData(Vector<float>& data) override;
  void     SetBufferData(float* pData, size_t size) override;
  void     Create() override;
  void     Destroy() override;

private:
  unsigned m_nVboID;
};

} // namespace Yuki::Core
