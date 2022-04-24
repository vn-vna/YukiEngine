#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiDebug/YukiError.hpp"

#include "PYukiObject.hpp"

// glm
#include <glm/gtc/type_ptr.hpp>

namespace Yuki::Core
{

class YukiOGLShaderProgram final : virtual public IYukiOGLShaderProgram,
                                   virtual public YukiObject
{
protected:
  unsigned m_nSPId;
  String   m_VSShaderFile;
  String   m_FSShaderFile;
  String   m_GSShaderFile;

  unsigned GetUniformLocation(const String& prop);

public:
  explicit YukiOGLShaderProgram(const String& shaderName);
  ~YukiOGLShaderProgram() override;

  bool            OnUse();
  const unsigned& GetID() override;
  void            BindObject() override;
  void            Create() override;
  void            Destroy() override;
  void            UniformMatrix(const String& prop, const Mat2F& mat, bool transpose) override;
  void            UniformMatrix(const String& prop, const Mat3F& mat, bool transpose) override;
  void            UniformMatrix(const String& prop, const Mat4F& mat, bool transpose) override;
  void            UniformVector(const String& prop, const Vec2F& vec) override;
  void            UniformVector(const String& prop, const Vec3F& vec) override;
  void            UniformVector(const String& prop, const Vec4F& vec) override;
  void            UniformValue(const String& prop, bool value) override;
  void            UniformValue(const String& prop, int value) override;
  void            UniformValue(const String& prop, float value) override;
};

} // namespace Yuki::Core