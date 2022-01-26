#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiCore/YukiThread.hpp"

#include <glm/glm.hpp>

namespace Yuki::Core
{

class YUKIAPI IYukiOGLObject : public IYukiObject
{
public:
  virtual const unsigned& GetID()      = 0;
  virtual void            BindObject() = 0;
  virtual bool            OnUse()      = 0;
};

class YUKIAPI IYukiOGLVertexBuffer : public IYukiOGLObject
{
public:
  virtual void SetBufferData(std::vector<float>& data, size_t offset = 0)  = 0;
  virtual void SetBufferData(float* pData, size_t size, size_t offset = 0) = 0;
};

class YUKIAPI IYukiOGLVertexArray : public IYukiOGLObject
{
public:
  virtual void SetVertexBuffer(const SharedPtr<IYukiOGLVertexBuffer>& buffer, int bindIndex, size_t offset, size_t stride)            = 0;
  virtual void EnableAttribute(const unsigned& attrib)                                                                                = 0;
  virtual void SetAttributeFormat(const unsigned& attrib, const unsigned& size, const size_t& offset, const bool& normalized = false) = 0;
  virtual void AttributeBinding(const unsigned& attrib, const unsigned& binding)                                                      = 0;
};

class YUKIAPI IYukiOGLShaderProgram : public IYukiOGLObject
{
public:
  virtual void UniformMatrix(const AsciiString& prop, const glm::mat2& mat, bool transopse = false) = 0;
  virtual void UniformMatrix(const AsciiString& prop, const glm::mat3& mat, bool transopse = false) = 0;
  virtual void UniformMatrix(const AsciiString& prop, const glm::mat4& mat, bool transopse = false) = 0;

  virtual void UniformVector(const AsciiString& prop, const glm::vec2& vec) = 0;
  virtual void UniformVector(const AsciiString& prop, const glm::vec3& vec) = 0;
  virtual void UniformVector(const AsciiString& prop, const glm::vec4& vec) = 0;

  virtual void UniformValue(const AsciiString& prop, const bool& value)  = 0;
  virtual void UniformValue(const AsciiString& prop, const int& value)   = 0;
  virtual void UniformValue(const AsciiString& prop, const float& value) = 0;
};

SharedPtr<IYukiOGLVertexBuffer> YUKIAPI  CreateGLVertexBuffer();
SharedPtr<IYukiOGLShaderProgram> YUKIAPI CreateGLShaderProgram(const String& shaderName);

} // namespace Yuki::Core
