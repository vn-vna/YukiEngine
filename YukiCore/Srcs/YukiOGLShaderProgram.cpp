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

  unsigned GetUniformLocation(const AsciiString& prop);

public:
  YukiOGLShaderProgram(const String& shaderName);
  virtual ~YukiOGLShaderProgram();

  const unsigned& GetID() override;
  void            BindObject() override;
  void            Create() override;
  void            Destroy() override;
  bool            OnUse() override;
  void            UniformMatrix(const AsciiString& prop, const glm::mat2& mat, bool transpose = false) override;
  void            UniformMatrix(const AsciiString& prop, const glm::mat3& mat, bool transpose = false) override;
  void            UniformMatrix(const AsciiString& prop, const glm::mat4& mat, bool transpose = false) override;
  void            UniformVector(const AsciiString& prop, const glm::vec2& vec) override;
  void            UniformVector(const AsciiString& prop, const glm::vec3& vec) override;
  void            UniformVector(const AsciiString& prop, const glm::vec4& vec) override;
  void            UniformValue(const AsciiString& prop, const bool& value) override;
  void            UniformValue(const AsciiString& prop, const int& value) override;
  void            UniformValue(const AsciiString& prop, const float& value) override;
};

} // namespace Yuki::Core

Yuki::AsciiString loadShaderSourceFromFile(const Yuki::String& path);
const unsigned    createShaderFromSource(GLenum shaderTypem, const Yuki::AsciiString& shaderSource);

Yuki::AsciiString loadShaderSourceFromFile(const Yuki::String& path)
{
  Yuki::AsciiStringStream sstr{};
  Yuki::AsciiString       line;
  std::ifstream           ipf{path};
  while (std::getline(ipf, line))
  {
    sstr << line << "\n";
  }
  sstr << "\n\0";
  return sstr.str();
}

const unsigned createShaderFromSource(GLenum shaderType, const Yuki::AsciiString& shaderSource)
{

  const char* pSource = shaderSource.c_str();
  int         status;

  unsigned shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &pSource, nullptr);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (!status)
  {
    char errStr[512];
    ZeroMemory(errStr, sizeof(errStr));
    glGetShaderInfoLog(shader, 512, nullptr, errStr);
    Yuki::StringStream sstr;
    sstr << errStr;
    Yuki::Core::GetYukiApp()->GetLogger()->PushErrorMessage(sstr.str());
    THROW_YUKI_ERROR(Yuki::Debug::YukiOGLCompileShaderError);
  }
  return shader;
}

namespace Yuki::Core
{

YukiOGLShaderProgram::YukiOGLShaderProgram(const String& shaderName)
    : m_nSPId()
{
  m_VSShaderFile = shaderName + L".vert";
  m_FSShaderFile = shaderName + L".frag";
}

YukiOGLShaderProgram::~YukiOGLShaderProgram()
{}

const unsigned& YukiOGLShaderProgram::GetID()
{
  return m_nSPId;
}

void YukiOGLShaderProgram::BindObject()
{
  glUseProgram(m_nSPId);
}

void YukiOGLShaderProgram::Create()
{
  AsciiString vsSrc = loadShaderSourceFromFile(m_VSShaderFile);
  AsciiString fsSrc = loadShaderSourceFromFile(m_FSShaderFile);
  int         status;

  unsigned vs = createShaderFromSource(GL_VERTEX_SHADER, vsSrc);
  unsigned fs = createShaderFromSource(GL_FRAGMENT_SHADER, fsSrc);

  unsigned pid = glCreateProgram();
  glAttachShader(pid, vs);
  glAttachShader(pid, fs);
  glLinkProgram(pid);
  glGetProgramiv(pid, GL_LINK_STATUS, &status);
  if (!status)
  {
    char errStr[512];
    ZeroMemory(errStr, sizeof(errStr));
    glGetProgramInfoLog(pid, 512, nullptr, errStr);
    Yuki::StringStream sstr;
    sstr << errStr;
    Yuki::Core::GetYukiApp()->GetLogger()->PushErrorMessage(sstr.str());
  }

  m_nSPId = pid;
}

void YukiOGLShaderProgram::Destroy()
{
  glDeleteProgram(m_nSPId);
}

bool YukiOGLShaderProgram::OnUse()
{
  int activeProgram;
  glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgram);
  return activeProgram == m_nSPId;
}


unsigned YukiOGLShaderProgram::GetUniformLocation(const AsciiString& prop)
{
  if (OnUse())
  {
    return glGetUniformLocation(m_nSPId, prop.c_str());
  }
  else
  {
    THROW_YUKI_ERROR(Debug::YukiOGLShaderProgramIsNotActived);
  }
}

void YukiOGLShaderProgram::UniformMatrix(const AsciiString& prop, const glm::mat2& mat, bool transpose)
{
  try
  {
    glUniformMatrix2fv(GetUniformLocation(prop), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
  }
  catch (Debug::YukiError& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void YukiOGLShaderProgram::UniformMatrix(const AsciiString& prop, const glm::mat3& mat, bool transpose)
{
  try
  {
    glUniformMatrix3fv(GetUniformLocation(prop), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
  }
  catch (Debug::YukiError& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void YukiOGLShaderProgram::UniformMatrix(const AsciiString& prop, const glm::mat4& mat, bool transpose)
{
  try
  {
    glUniformMatrix4fv(GetUniformLocation(prop), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
  }
  catch (Debug::YukiError& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void YukiOGLShaderProgram::UniformVector(const AsciiString& prop, const glm::vec2& vec)
{
  try
  {
    glUniform2fv(GetUniformLocation(prop), 1, glm::value_ptr(vec));
  }
  catch (Debug::YukiError& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void YukiOGLShaderProgram::UniformVector(const AsciiString& prop, const glm::vec3& vec)
{
  try
  {
    glUniform3fv(GetUniformLocation(prop), 1, glm::value_ptr(vec));
  }
  catch (Debug::YukiError& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void YukiOGLShaderProgram::UniformVector(const AsciiString& prop, const glm::vec4& vec)
{
  try
  {
    glUniform4fv(GetUniformLocation(prop), 1, glm::value_ptr(vec));
  }
  catch (Debug::YukiError& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void YukiOGLShaderProgram::UniformValue(const AsciiString& prop, const bool& value)
{
  try
  {
    glUniform1i(GetUniformLocation(prop), value ? 1 : 0);
  }
  catch (Debug::YukiError& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void YukiOGLShaderProgram::UniformValue(const AsciiString& prop, const int& value)
{
  try
  {
    glUniform1i(GetUniformLocation(prop), value);
  }
  catch (Debug::YukiError& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void YukiOGLShaderProgram::UniformValue(const AsciiString& prop, const float& value)
{
  try
  {
    glUniform1f(GetUniformLocation(prop), value);
  }
  catch (Debug::YukiError& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

SharedPtr<IYukiOGLShaderProgram> CreateGLShaderProgram(const String& shaderName)
{
  return {(IYukiOGLShaderProgram*) new YukiOGLShaderProgram(shaderName), std::default_delete<IYukiOGLShaderProgram>()};
}

} // namespace Yuki::Core