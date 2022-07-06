#include "YukiCore/Headers.hpp"
#include "YukiDebug/Errors.hpp"
#include "YukiCore/Application.hpp"

#define MAKE_ERROR_DEFINITION(__err_name, __err_code)                     \
  Yuki##__err_name::Yuki##__err_name(const String& file, const int& line) \
      : std::runtime_error("yuki-rte"),                                   \
        Errors(YukiErrCode::__err_code, file, line)                    \
  {}

#define YUKI_CORE_ERROR   "[YUKI CORE]"
#define YUKI_GLFW_ERROR   "[GLFW]"
#define YUKI_OPENGL_ERROR "[OPENGL]"
#define YUKI_GLAD_ERROR   "[GLAD]"

#define CHECK_CASE_OF_ERROR(__err_code, __caused_by)                          \
  case YukiErrCode::__err_code:                                               \
    sstr << __caused_by " >> " #__err_code " << .Please Check your system\n"; \
    break

namespace Yuki::Debug
{

using Core::GetYukiApp;

Errors::Errors(const YukiErrCode& code, const String& file,
                     const int& line)
    : std::runtime_error("yuki-rte"),
      m_File(file),
      m_nLine(line),
      m_ErrCode(code)
{}

String Errors::getErrorMessage() const
{
  StringStream sstr = {};
  sstr << "[YUKI ERROR REPORT]\n\t[RTE at file: " << m_File << " - line "
       << m_nLine << "] -> ";
  switch (m_ErrCode)
  {
    // clang-format off
    CHECK_CASE_OF_ERROR(YUKI_APP_CREATED,                         YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_LOGGER_CREATE_LOGFILE_ERROR,         YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_INSERT_CALLBACK_EXISTS,      YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_REMOVE_CALLBACK_NEXIST,      YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_INVOKE_UNDEFINED_CALLBACK,   YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_KEYCODE_INVALID,             YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_THREAD_ATTACHMENT_DUPLICATE_ID,      YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_THREAD_CREATION_FAILED,              YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_THREAD_DETACHMENT_NEXIST,            YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_MUTEX_CREATION_FAILED,               YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_MUTEX_WAIT_ABANDONED,                YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_MUTEX_WAIT_FUNC_FAILED,              YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_TPOOL_ALREADY_STARTED,               YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_TPOOL_MANAGER_DUPLICATE,             YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_TPOOL_MANAGER_NEXIST,                YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(GLFW_INITIALIZATION_FAILED,               YUKI_GLFW_ERROR);
    CHECK_CASE_OF_ERROR(GLFW_WINDOW_CREATION_FAILED,              YUKI_GLFW_ERROR);
    CHECK_CASE_OF_ERROR(GLAD_LOAD_GLLOADER_FAILED,                YUKI_GLAD_ERROR);
    CHECK_CASE_OF_ERROR(OPENGL_COMPILE_SHADER_ERROR,              YUKI_OPENGL_ERROR);
    CHECK_CASE_OF_ERROR(OPENGL_SHADER_PROGRAM_ISNOT_ACTIVED,      YUKI_OPENGL_ERROR);
    CHECK_CASE_OF_ERROR(OPENGL_TEXTURE_TYPE_NOT_COMPATIBLE,       YUKI_OPENGL_ERROR);
    CHECK_CASE_OF_ERROR(ASSIMP_MODEL_CANT_BE_LOADED,              YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(SCENE_DUPLICATE_ENTITY_NAME,              YUKI_CORE_ERROR);
    // clang-format on
  }
  return sstr.str();
}

const YukiErrCode& Errors::getErrorCode() const
{
  return m_ErrCode;
}

void Errors::PushErrorMessage() const
{
  GetYukiApp()->GetLogger()->PushErrorMessage(this->getErrorMessage());
}

// clang-format off
MAKE_ERROR_DEFINITION(AppCreated,                                 YUKI_APP_CREATED)
MAKE_ERROR_DEFINITION(CreateLogFileError,                         YUKI_LOGGER_CREATE_LOGFILE_ERROR)
MAKE_ERROR_DEFINITION(InpCtrlInsertCallbackExistsError,           YUKI_INPCTRL_INSERT_CALLBACK_EXISTS)
MAKE_ERROR_DEFINITION(InpCtrlRemoveCallbackNExistsError,          YUKI_INPCTRL_REMOVE_CALLBACK_NEXIST)
MAKE_ERROR_DEFINITION(InpCtrlInvokeUndefinedCallbackError,        YUKI_INPCTRL_INVOKE_UNDEFINED_CALLBACK)
MAKE_ERROR_DEFINITION(InpCtrlKeyCodeInvalidError,                 YUKI_INPCTRL_KEYCODE_INVALID)
MAKE_ERROR_DEFINITION(ThreadAssignmentDuplicateThreadIdError,     YUKI_THREAD_ATTACHMENT_DUPLICATE_ID)
MAKE_ERROR_DEFINITION(ThreadCreationError,                        YUKI_THREAD_CREATION_FAILED)
MAKE_ERROR_DEFINITION(ThreadDetachmentNotExistError,              YUKI_THREAD_DETACHMENT_NEXIST)
MAKE_ERROR_DEFINITION(MutexCreationError,                         YUKI_MUTEX_CREATION_FAILED)
MAKE_ERROR_DEFINITION(MutexWaitAbandoned,                         YUKI_MUTEX_WAIT_ABANDONED)
MAKE_ERROR_DEFINITION(MutexWaitFunctionFailed,                    YUKI_MUTEX_WAIT_FUNC_FAILED)
MAKE_ERROR_DEFINITION(ThreadPoolAlreadyStarted,                   YUKI_TPOOL_ALREADY_STARTED)
MAKE_ERROR_DEFINITION(ThreadPoolManagerDuplicateKey,              YUKI_TPOOL_MANAGER_DUPLICATE)
MAKE_ERROR_DEFINITION(ThreadPoolManagerNExistsKey,                YUKI_TPOOL_MANAGER_NEXIST)
MAKE_ERROR_DEFINITION(GLFWInitError,                              GLFW_INITIALIZATION_FAILED)
MAKE_ERROR_DEFINITION(WindowCreationError,                        GLFW_WINDOW_CREATION_FAILED)
MAKE_ERROR_DEFINITION(GladLoadGLLoaderError,                      GLAD_LOAD_GLLOADER_FAILED)
MAKE_ERROR_DEFINITION(OGLCompileShaderError,                      OPENGL_COMPILE_SHADER_ERROR)
MAKE_ERROR_DEFINITION(OGLShaderProgramIsNotActived,               OPENGL_SHADER_PROGRAM_ISNOT_ACTIVED)
MAKE_ERROR_DEFINITION(OGLTextureTypeNotCompatibleError,           OPENGL_TEXTURE_TYPE_NOT_COMPATIBLE)
MAKE_ERROR_DEFINITION(AssimpModelCantBeLoaded,                    ASSIMP_MODEL_CANT_BE_LOADED)
MAKE_ERROR_DEFINITION(SceneDuplicateEntityName,                   SCENE_DUPLICATE_ENTITY_NAME)
// clang-format on

} // namespace Yuki::Debug
