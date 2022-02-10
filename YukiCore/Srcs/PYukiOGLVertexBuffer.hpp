#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiThread.hpp"
#include "YukiDebug/YukiError.hpp"

namespace Yuki::Core
{

class YukiOGLVertexBuffer : public virtual IYukiOGLVertexBuffer
{
protected:
    unsigned m_nVboID;
    int      m_nRequired;

public:
    YukiOGLVertexBuffer();
    virtual ~YukiOGLVertexBuffer();

    bool            OnUse();
    const unsigned& GetID() override;
    void            BindObject() override;
    void            SetBufferData(std::vector<float>& data) override;
    void            SetBufferData(float* pData, size_t size) override;
    void            Create() override;
    void            Destroy() override;
};

} // namespace Yuki::Core