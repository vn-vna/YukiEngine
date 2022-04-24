#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

class YukiOGLElementBuffer final : virtual public IYukiOGLElementBuffer,
                                   virtual public YukiObject
{
protected:
  unsigned m_nEboID;
  unsigned m_nElementCount;

public:
  YukiOGLElementBuffer();
  ~YukiOGLElementBuffer() override;

  bool            OnUse();
  const unsigned& GetID() override;
  void            BindObject() override;
  void            SetBufferData(Vector<unsigned>& data) override;
  void            SetBufferData(unsigned* pData, size_t size) override;
  void            DrawElements(PrimitiveTopology topology, unsigned start, unsigned count) override;
  void            DrawAllElements(PrimitiveTopology topology) override;
  void            Create() override;
  void            Destroy() override;
};

} // namespace Yuki::Core