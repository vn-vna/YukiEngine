#pragma once

#include "YukiComp/YukiLights.hpp"

namespace Yuki::Comp
{

class YukiDirectionalLight : public virtual IYukiDirectionalLight
{
protected:
    glm::vec3 m_tDirection;
    glm::vec4 m_tColor;
    float     m_nIntensity;

public:
    YukiDirectionalLight();
    virtual ~YukiDirectionalLight() = default;

    const glm::vec4& GetColor() override;
    const float&     GetIntensity() override;
    const glm::vec3& GetDirection() override;

    void SetDirection(const glm::vec3& direction) override;
    void SetColor(const glm::vec4& color) override;
    void SetIntensity(const float& intensity) override;

    friend SharedPtr<IYukiDirectionalLight> CreateDirectionalLight();
};

} // namespace Yuki::Comp