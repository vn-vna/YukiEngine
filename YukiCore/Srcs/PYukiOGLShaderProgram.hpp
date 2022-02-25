#pragma once
#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiDebug/YukiError.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace Yuki::Core
{

class YukiOGLShaderProgram : public IYukiOGLShaderProgram
{
protected:
  unsigned m_nSPId;
  String   m_VSShaderFile;
  String   m_FSShaderFile;
  String   m_GSShaderFile;

  unsigned GetUniformLocation(const String& prop);

public:
  YukiOGLShaderProgram(const String& shaderName);
  virtual ~YukiOGLShaderProgram();

  bool            OnUse();
  const unsigned& GetID() override;
  void            BindObject() override;
  void            Create() override;
  void            Destroy() override;
  void            UniformMatrix(const String& prop, const glm::mat2& mat, bool transpose = false) override;
  void            UniformMatrix(const String& prop, const glm::mat3& mat, bool transpose = false) override;
  void            UniformMatrix(const String& prop, const glm::mat4& mat, bool transpose = false) override;
  void            UniformVector(const String& prop, const glm::vec2& vec) override;
  void            UniformVector(const String& prop, const glm::vec3& vec) override;
  void            UniformVector(const String& prop, const glm::vec4& vec) override;
  void            UniformValue(const String& prop, const bool& value) override;
  void            UniformValue(const String& prop, const int& value) override;
  void            UniformValue(const String& prop, float value) override;
};

} // namespace Yuki::Core