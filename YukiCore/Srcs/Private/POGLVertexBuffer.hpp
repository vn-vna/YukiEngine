/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiDebug/Errors.hpp"

#include "PObjects.hpp"

namespace Yuki::Core
{

class YukiOGLVertexBuffer final : virtual public IYukiOGLVertexBuffer,
                                  virtual public YukiSharedObject
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
