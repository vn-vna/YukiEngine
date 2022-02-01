#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiCore/YukiThread.hpp"

#include <glm/glm.hpp>

namespace Yuki::Core
{

enum class PrimitiveTopology
{
  TRIANGLE_LIST  = GL_TRIANGLES,
  TRIANGLE_FAN   = GL_TRIANGLE_FAN,
  TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
  QUAD_LIST      = GL_QUADS,
  QUAD_STRIP     = GL_QUAD_STRIP,
  LINES          = GL_LINES,
  LINE_STRIP     = GL_LINE_STRIP,
  LINE_LOOP      = GL_LINE_LOOP,
  POINT_LIST     = GL_POINTS
};

typedef struct StVertexFormat
{
  glm::vec3 position;
  glm::vec4 color;
  glm::vec2 texcoord;
  unsigned  texID;

  StVertexFormat(const glm::vec3& _position, const glm::vec4& _color, const glm::vec2& _texcoord, const unsigned& _texID)
      : position(_position), color(_color), texcoord(_texcoord), texID(_texID) {}

} VertexData, VertexFormat;

typedef struct StIndexData
{
  PrimitiveTopology      topology;
  std::vector<unsigned>& data;
} IndexData, IndexFormat;

class YUKIAPI IYukiGfxControl : public IYukiObject
{
public:
};

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
  virtual void SetBufferData(std::vector<float>& data)  = 0;
  virtual void SetBufferData(float* pData, size_t size) = 0;
};

class YUKIAPI IYukiOGLElementBuffer : public IYukiOGLObject
{
public:
  virtual void SetBufferData(std::vector<unsigned>& data)  = 0;
  virtual void SetBufferData(unsigned* pData, size_t size) = 0;
  virtual void DrawElements(
      Core::PrimitiveTopology topology, const unsigned& start, const unsigned& count) = 0;
  virtual void DrawAllElements(
      Core::PrimitiveTopology topology) = 0;
};

class YUKIAPI IYukiOGLVertexArray : public IYukiOGLObject
{
public:
  virtual void EnableAttribute(const unsigned& attrib)                           = 0;
  virtual void AttributeBinding(const unsigned& attrib, const unsigned& binding) = 0;
  virtual void SetAttributeFormat(
      const unsigned& attrib, const unsigned& size, const size_t& offset, const bool& normalized = false) = 0;
  virtual void SetVertexBuffer(
      const SharedPtr<IYukiOGLVertexBuffer>& buffer, int bindIndex, size_t offset, size_t stride) = 0;
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
SharedPtr<IYukiOGLElementBuffer> YUKIAPI CreateGLElementBuffer();
SharedPtr<IYukiOGLShaderProgram> YUKIAPI CreateGLShaderProgram(const String& shaderName);
SharedPtr<IYukiOGLVertexArray> YUKIAPI   CreateGLVertexArray();

} // namespace Yuki::Core
