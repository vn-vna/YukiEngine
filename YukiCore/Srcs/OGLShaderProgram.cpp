#include "YukiCore/Headers.hpp"

#include "Private/POGLShaderProgram.hpp"

Yuki::String loadShaderSourceFromFile(const Yuki::String& path);
const unsigned
createShaderFromSource(GLenum shaderTypem, const Yuki::String& shaderSource);

Yuki::String loadShaderSourceFromFile(const Yuki::String& path)
{
  Yuki::StringStream sstr {};
  Yuki::String       line;
  std::ifstream      ipf {path};
  while (std::getline(ipf, line))
  {
    sstr << line << "\n";
  }
  sstr << "\n\0";
  return sstr.str();
}

const unsigned
createShaderFromSource(GLenum shaderType, const Yuki::String& shaderSource)
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
    std::memset(errStr, 0x00, sizeof(errStr));
    glGetShaderInfoLog(shader, 512, nullptr, errStr);
    Yuki::StringStream sstr;
    sstr << errStr;
    Yuki::Core::GetYukiApp()->GetLogger()->PushErrorMessage(sstr.str());
    THROW_YUKI_ERROR(OGLCompileShaderError);
  }
  return shader;
}

namespace Yuki::Core
{

OGLShaderProgram::OGLShaderProgram(const String& shaderName)
    : m_nSPId()
{
  m_VSShaderFile = shaderName + ".vert";
  m_FSShaderFile = shaderName + ".frag";
  m_GSShaderFile = shaderName + ".geom";
}

OGLShaderProgram::~OGLShaderProgram() = default;

unsigned OGLShaderProgram::GetID()
{
  return m_nSPId;
}

void OGLShaderProgram::BindObject()
{
  glUseProgram(m_nSPId);
}

void OGLShaderProgram::Create()
{
  String vsSrc = loadShaderSourceFromFile(m_VSShaderFile);
  String fsSrc = loadShaderSourceFromFile(m_FSShaderFile);

  int status;

  unsigned vs = createShaderFromSource(GL_VERTEX_SHADER, vsSrc);
  unsigned fs = createShaderFromSource(GL_FRAGMENT_SHADER, fsSrc);

  unsigned pid = glCreateProgram();
  glAttachShader(pid, vs);
  glAttachShader(pid, fs);
  // glAttachShader(pid, gs);
  glLinkProgram(pid);
  glGetProgramiv(pid, GL_LINK_STATUS, &status);
  if (!status)
  {
    char errStr[512];
    std::memset(errStr, 0x00, sizeof(errStr));
    glGetProgramInfoLog(pid, 512, nullptr, errStr);
    Yuki::StringStream sstr;
    sstr << errStr;
    Yuki::Core::GetYukiApp()->GetLogger()->PushErrorMessage(sstr.str());
  }

  m_nSPId = pid;
}

void OGLShaderProgram::Destroy()
{
  glDeleteProgram(m_nSPId);
}

bool OGLShaderProgram::OnUse()
{
  int activeProgram;
  glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgram);
  return activeProgram == m_nSPId;
}

unsigned OGLShaderProgram::GetUniformLocation(const String& prop)
{
  if (this->OnUse())
  {
    return glGetUniformLocation(m_nSPId, prop.c_str());
  }
  THROW_YUKI_ERROR(OGLShaderProgramIsNotActived);
}

unsigned OGLShaderProgram::GetUniformBlockIndex(const String& block)
{
  if (this->OnUse())
  {
    return glGetUniformBlockIndex(m_nSPId, block.c_str());
  }
  THROW_YUKI_ERROR(OGLShaderProgramIsNotActived);
}

void OGLShaderProgram::UniformMatrix(
    const String& prop, const Mat2F& mat, bool transpose
)
{
  try
  {
    glUniformMatrix2fv(
        GetUniformLocation(prop), 1, transpose ? GL_TRUE : GL_FALSE,
        glm::value_ptr(mat)
    );
  }
  catch (Debug::Errors& yer)
  {
    yer.PushErrorMessage();
  }
}

void OGLShaderProgram::UniformMatrix(
    const String& prop, const Mat3F& mat, bool transpose
)
{
  try
  {
    glUniformMatrix3fv(
        GetUniformLocation(prop), 1, transpose ? GL_TRUE : GL_FALSE,
        glm::value_ptr(mat)
    );
  }
  catch (Debug::Errors& yer)
  {
    yer.PushErrorMessage();
  }
}

void OGLShaderProgram::UniformMatrix(
    const String& prop, const Mat4F& mat, bool transpose
)
{
  try
  {
    glUniformMatrix4fv(
        GetUniformLocation(prop), 1, transpose ? GL_TRUE : GL_FALSE,
        glm::value_ptr(mat)
    );
  }
  catch (Debug::Errors& yer)
  {
    yer.PushErrorMessage();
  }
}

void OGLShaderProgram::UniformVector(const String& prop, const Vec2F& vec)
{
  try
  {
    glUniform2fv(GetUniformLocation(prop), 1, glm::value_ptr(vec));
  }
  catch (Debug::Errors& yer)
  {
    yer.PushErrorMessage();
  }
}

void OGLShaderProgram::UniformVector(const String& prop, const Vec3F& vec)
{
  try
  {
    glUniform3fv(GetUniformLocation(prop), 1, glm::value_ptr(vec));
  }
  catch (Debug::Errors& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void OGLShaderProgram::UniformVector(const String& prop, const Vec4F& vec)
{
  try
  {
    glUniform4fv(GetUniformLocation(prop), 1, glm::value_ptr(vec));
  }
  catch (Debug::Errors& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void OGLShaderProgram::UniformValue(const String& prop, bool value)
{
  try
  {
    glUniform1i(GetUniformLocation(prop), value ? 1 : 0);
  }
  catch (Debug::Errors& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void OGLShaderProgram::UniformValue(const String& prop, int value)
{
  try
  {
    glUniform1i(GetUniformLocation(prop), value);
  }
  catch (Debug::Errors& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

void OGLShaderProgram::UniformValue(const String& prop, float value)
{
  try
  {
    glUniform1f(GetUniformLocation(prop), value);
  }
  catch (Debug::Errors& yer)
  {
    GetYukiApp()->GetLogger()->PushErrorMessage(yer.getErrorMessage());
  }
}

SharedPtr<IOGLShaderProgram> CreateGLShaderProgram(const String& shaderName)
{
  return CreateInterfaceInstance<IOGLShaderProgram, OGLShaderProgram>(shaderName
  );
}

} // namespace Yuki::Core
