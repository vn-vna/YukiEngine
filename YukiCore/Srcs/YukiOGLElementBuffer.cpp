#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Core
{

class YukiOGLElementBuffer : public IYukiOGLElementBuffer
{
protected:
  unsigned m_nEboID;

public:
  YukiOGLElementBuffer();
  virtual ~YukiOGLElementBuffer();

  const unsigned& GetID() override;
  void            BindObject() override;
  bool            OnUse() override;
  void            SetBufferData(std::vector<unsigned>& data) override;
  void            SetBufferData(unsigned* pData, size_t size) override;
  void            Create() override;
  void            Destroy() override;
};

} // namespace Yuki::Core

namespace Yuki::Core
{

YukiOGLElementBuffer::YukiOGLElementBuffer()
    : m_nEboID()
{}

YukiOGLElementBuffer::~YukiOGLElementBuffer() = default;

const unsigned& YukiOGLElementBuffer::GetID()
{
  return m_nEboID;
}

void YukiOGLElementBuffer::BindObject()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nEboID);
}

bool YukiOGLElementBuffer::OnUse()
{
  int crrEbo;
  glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &crrEbo);
  return m_nEboID == crrEbo;
}

void YukiOGLElementBuffer::SetBufferData(std::vector<unsigned>& data)
{
  SetBufferData(data.data(), data.size() * sizeof(unsigned));
}

void YukiOGLElementBuffer::SetBufferData(unsigned* pData, size_t size)
{
  glNamedBufferData(m_nEboID, size, pData, GL_STATIC_DRAW);
}

void YukiOGLElementBuffer::Create()
{
  glCreateBuffers(1, &m_nEboID);
}

void YukiOGLElementBuffer::Destroy()
{
  glDeleteBuffers(1, &m_nEboID);
}

SharedPtr<IYukiOGLElementBuffer> YUKIAPI CreateGLElementBuffer()
{
  return {(IYukiOGLElementBuffer*) new YukiOGLElementBuffer, std::default_delete<IYukiOGLElementBuffer>()};
}

} // namespace Yuki::Core