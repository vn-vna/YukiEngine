#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiWindow.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiGfxPipeline.h"
#include "YukiDebug/YukiError.hpp"

namespace Yuki::Core
{

class YukiOGLVertexBuffer : public IYukiOGLVertexBuffer
{
protected:
  unsigned m_pVboID;

public:
  YukiOGLVertexBuffer();
  virtual ~YukiOGLVertexBuffer();

  void GetID() override;
  void BindObject() override;

  void Create() override;
  void Destroy() override;
   
  void LockYukiObj() override;
  void UnlockYukiObj() override;
};

} // namespace Yuki::Core

namespace Yuki::Core
{

YukiOGLVertexBuffer::YukiOGLVertexBuffer()
    : m_pVboID()
{}

} // namespace Yuki::Core