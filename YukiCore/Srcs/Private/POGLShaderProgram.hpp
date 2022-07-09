/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/Headers.hpp"
#include "YukiCore/Application.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiDebug/Errors.hpp"

#include "PObjects.hpp"

// glm
#include "glm/gtc/type_ptr.hpp"

namespace Yuki::Core
{

class OGLShaderProgram final : virtual public IOGLShaderProgram,
                               virtual public YukiSharedObject
{
public:
  explicit OGLShaderProgram(const String& shaderName);
  ~OGLShaderProgram() override;

  bool     OnUse();
  unsigned GetID() override;
  void     BindObject() override;
  void     Create() override;
  void     Destroy() override;
  void     UniformMatrix(const String& prop, const Mat2F& mat, bool transpose) override;
  void     UniformMatrix(const String& prop, const Mat3F& mat, bool transpose) override;
  void     UniformMatrix(const String& prop, const Mat4F& mat, bool transpose) override;
  void     UniformVector(const String& prop, const Vec2F& vec) override;
  void     UniformVector(const String& prop, const Vec3F& vec) override;
  void     UniformVector(const String& prop, const Vec4F& vec) override;
  void     UniformValue(const String& prop, bool value) override;
  void     UniformValue(const String& prop, int value) override;
  void     UniformValue(const String& prop, float value) override;

private:
  unsigned GetUniformLocation(const String& prop);

private:
  unsigned m_nSPId;
  String   m_VSShaderFile;
  String   m_FSShaderFile;
  String   m_GSShaderFile;
};

} // namespace Yuki::Core
