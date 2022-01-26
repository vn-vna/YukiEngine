#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiThread.hpp"
#include "YukiDebug/YukiError.hpp"

namespace Yuki::Core
{

class YukiOGLVertexBuffer : public IYukiOGLVertexBuffer
{
protected:
  unsigned m_nVboID;

public:
  YukiOGLVertexBuffer();
  virtual ~YukiOGLVertexBuffer();

  const unsigned& GetID() override;
  void            BindObject() override;
  bool            OnUse() override;
  void            SetBufferData(std::vector<float>& data, size_t offset = 0) override;
  void            SetBufferData(float* pData, size_t size, size_t offset = 0) override;
  void            Create() override;
  void            Destroy() override;
};

} // namespace Yuki::Core

namespace Yuki::Core
{

YukiOGLVertexBuffer::YukiOGLVertexBuffer()
    : m_nVboID()
{}

YukiOGLVertexBuffer::~YukiOGLVertexBuffer() = default;

const unsigned& YukiOGLVertexBuffer::GetID()
{
  return m_nVboID;
}

bool YukiOGLVertexBuffer::OnUse()
{
  int crrVB;
  glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &crrVB);
  return crrVB == m_nVboID;
}

void YukiOGLVertexBuffer::BindObject()
{
  glBindBuffer(GL_ARRAY_BUFFER, m_nVboID);
}

void YukiOGLVertexBuffer::SetBufferData(std::vector<float>& data, size_t offset)
{
  SetBufferData(data.data(), data.size() * sizeof(float), offset);
}

void YukiOGLVertexBuffer::SetBufferData(float* pData, size_t size, size_t offset)
{
  glGetNamedBufferSubData(m_nVboID, offset, size, pData);
}

void YukiOGLVertexBuffer::Create()
{
  glCreateBuffers(1, &m_nVboID);
}

void YukiOGLVertexBuffer::Destroy()
{
  glDeleteBuffers(1, &m_nVboID);
}

SharedPtr<IYukiOGLVertexBuffer> CreateGLVertexBuffer()
{
  return {(IYukiOGLVertexBuffer*) new YukiOGLVertexBuffer, std::default_delete<IYukiOGLVertexBuffer>()};
}

} // namespace Yuki::Core
