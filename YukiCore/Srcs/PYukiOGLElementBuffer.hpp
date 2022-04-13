#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"

#include "PYukiObject.hpp"

namespace Yuki::Core
{

class YukiOGLElementBuffer : virtual public IYukiOGLElementBuffer,
                             virtual public YukiObject
{
protected:
  unsigned m_nEboID;
  unsigned m_nElementCount;

public:
  YukiOGLElementBuffer();
  virtual ~YukiOGLElementBuffer();

  bool            OnUse();
  const unsigned& GetID() override;
  void            BindObject() override;
  void            SetBufferData(Vector<unsigned>& data) override;
  void            SetBufferData(unsigned* pData, size_t size) override;
  void            DrawElements(Core::PrimitiveTopology topology, const unsigned& start, const unsigned& count) override;
  void            DrawAllElements(Core::PrimitiveTopology topology) override;
  void            Create() override;
  void            Destroy() override;
};

} // namespace Yuki::Core