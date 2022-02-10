#include "YukiCore/YukiPCH.hpp"

#include "PYukiOGLVertexBuffer.hpp"

namespace Yuki::Core
{

YukiOGLVertexBuffer::YukiOGLVertexBuffer()
    : m_nVboID(),
      m_nRequired(0)
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

void YukiOGLVertexBuffer::SetBufferData(std::vector<float>& data)
{
    SetBufferData(data.data(), data.size() * sizeof(float));
}

void YukiOGLVertexBuffer::SetBufferData(float* pData, size_t size)
{
    glNamedBufferData(m_nVboID, size, pData, GL_STATIC_DRAW);
}

void YukiOGLVertexBuffer::Create()
{
    if (m_nRequired <= 0)
    {
        glCreateBuffers(1, &m_nVboID);
        m_nRequired = 0;
    }
    ++m_nRequired;
}

void YukiOGLVertexBuffer::Destroy()
{
    --m_nRequired;
    if (m_nRequired == 0)
    {
        glDeleteBuffers(1, &m_nVboID);
    }
}

SharedPtr<IYukiOGLVertexBuffer> CreateGLVertexBuffer()
{
    return {(IYukiOGLVertexBuffer*) new YukiOGLVertexBuffer, std::default_delete<IYukiOGLVertexBuffer>()};
}

} // namespace Yuki::Core