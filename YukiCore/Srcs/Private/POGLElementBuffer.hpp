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

#include "PObjects.hpp"

namespace Yuki::Core
{

class YukiOGLElementBuffer final : virtual public IOGLElementBuffer,
                                   virtual public YukiSharedObject
{
public:
  YukiOGLElementBuffer();
  ~YukiOGLElementBuffer() override;

  bool     OnUse();
  unsigned GetID() override;
  void     BindObject() override;
  void     SetBufferData(Vector<unsigned>& data) override;
  void     SetBufferData(unsigned* pData, size_t size) override;
  void     DrawElements(PrimitiveTopology topology, unsigned start, unsigned count) override;
  void     DrawAllElements(PrimitiveTopology topology) override;

  void Create() override;
  void Destroy() override;

private:
  unsigned m_nEboID;
  unsigned m_nElementCount;
};

} // namespace Yuki::Core
