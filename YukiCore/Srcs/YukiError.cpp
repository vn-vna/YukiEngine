#include "YukiCore/YukiPCH.hpp"
#include "YukiDebug/YukiError.hpp"

#define MAKE_ERROR_DEFINATION(__err_name, __err_code)              \
  __err_name## ::__err_name##(const String& file, const int& line) \
      : YukiError(YukiErrCode::__err_code##, file, line)           \
  {}

#define YUKI_CORE_ERROR   L"[YUKI CORE]"
#define YUKI_GLFW_ERROR   L"[GLFW]"
#define YUKI_OPENGL_ERROR L"[OPENGL]"
#define YUKI_GLAD_ERROR   L"[GLAD]"

#define CHECK_CASE_OF_ERROR(__err_code, __caused_by)                            \
  case YukiErrCode::__err_code##:                                               \
    sstr << __caused_by L" >> " L#__err_code L"<< .Please Check your system\n"; \
    break

namespace Yuki::Debug
{

YukiError::YukiError(const YukiErrCode& code, const String& file, const int& line)
    : std::runtime_error("[RTE]"),
      m_File(file),
      m_nLine(line),
      m_ErrCode(code)
{}

String YukiError::getErrorMessage() const
{
  StringStream sstr = {};
  sstr << "[YUKI ERROR REPORT]\n\t[RTE at file: " << m_File << " - line " << m_nLine << "] -> ";
  switch (m_ErrCode)
  {
    // clang-format off
    CHECK_CASE_OF_ERROR(YUKI_APP_RECREATION_ERROR,              YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_APP_NOT_CREATED_ERROR,             YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_APP_INSTANCE_ALREADY_EXISTS,       YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_GFXCTRL_RECREATION_ERROR,          YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_GFXCTRL_NOT_CREATED_ERROR,         YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_WINDOW_RECREATION_ERROR,           YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_WINDOW_NOT_CREATED_ERROR,          YUKI_CORE_ERROR);

    CHECK_CASE_OF_ERROR(YUKI_LOGGER_CREATE_LOGFILE_ERROR,       YUKI_CORE_ERROR);

    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_INSERT_CALLBACK_EXISTS,    YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_REMOVE_CALLBACK_NEXIST,    YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_INVOKE_UNDEFINED_CALLBACK, YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_KEYCODE_INVALID,           YUKI_CORE_ERROR);

    CHECK_CASE_OF_ERROR(YUKI_THREAD_ATTACHMENT_DUPLICATE_ID,    YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_THREAD_CREATION_FAILED,            YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_THREAD_DETACHMENT_NEXIST,          YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_MUTEX_CREATION_FAILED,             YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_MUTEX_WAIT_ABANDONED,              YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_MUTEX_WAIT_FUNC_FAILED,            YUKI_CORE_ERROR);

    CHECK_CASE_OF_ERROR(YUKI_ENTITY_BIND_MESH_EXISTS,           YUKI_CORE_ERROR);          
    CHECK_CASE_OF_ERROR(YUKI_ENTITY_UNBIND_MESH_NEXISTS,        YUKI_CORE_ERROR);  
    CHECK_CASE_OF_ERROR(YUKI_ENTITY_BIND_UNDEFINED_MESH,        YUKI_CORE_ERROR);

    CHECK_CASE_OF_ERROR(GLFW_INITIALIZATION_FAILED,             YUKI_GLFW_ERROR);
    CHECK_CASE_OF_ERROR(GLFW_WINDOW_CREATION_FAILED,            YUKI_GLFW_ERROR);

    CHECK_CASE_OF_ERROR(GLAD_LOAD_GLLOADER_FAILED,              YUKI_GLAD_ERROR);

    CHECK_CASE_OF_ERROR(OPENGL_COMPILE_SHADER_ERROR,            YUKI_OPENGL_ERROR);
    CHECK_CASE_OF_ERROR(OPENGL_SHADER_PROGRAM_ISNOT_ACTIVED,    YUKI_OPENGL_ERROR);
    CHECK_CASE_OF_ERROR(OPENGL_TEXTURE_TYPE_NOT_COMPATIBLE,     YUKI_OPENGL_ERROR);
    // clang-format on
  }
  return sstr.str();
}

const YukiErrCode& YukiError::getErrorCode() const
{
  return m_ErrCode;
}

// clang-format off
MAKE_ERROR_DEFINATION(YukiApplicationRecreationError,               YUKI_APP_RECREATION_ERROR)           
MAKE_ERROR_DEFINATION(YukiApplicationNotCreatedError,               YUKI_APP_NOT_CREATED_ERROR)
MAKE_ERROR_DEFINATION(YukiApplicationInstanceExistsError,           YUKI_APP_INSTANCE_ALREADY_EXISTS) 
MAKE_ERROR_DEFINATION(YukiGfxControlRecreationError,                YUKI_GFXCTRL_RECREATION_ERROR)           
MAKE_ERROR_DEFINATION(YukiGfxControlNotCreatedError,                YUKI_GFXCTRL_NOT_CREATED_ERROR)
MAKE_ERROR_DEFINATION(YukiWindowRecreationError,                    YUKI_WINDOW_RECREATION_ERROR)           
MAKE_ERROR_DEFINATION(YukiWindowNotCreatedError,                    YUKI_WINDOW_NOT_CREATED_ERROR)

MAKE_ERROR_DEFINATION(YukiCreateLogFileError,                       YUKI_LOGGER_CREATE_LOGFILE_ERROR)

MAKE_ERROR_DEFINATION(YukiInpCtrlInsertCallbackExistsError,         YUKI_INPCTRL_INSERT_CALLBACK_EXISTS)
MAKE_ERROR_DEFINATION(YukiInpCtrlRemoveCallbackNExistsError,        YUKI_INPCTRL_REMOVE_CALLBACK_NEXIST)
MAKE_ERROR_DEFINATION(YukiInpCtrlInvokeUndefinedCallbackError,      YUKI_INPCTRL_INVOKE_UNDEFINED_CALLBACK)
MAKE_ERROR_DEFINATION(YukiInpCtrlKeyCodeInvalidError,               YUKI_INPCTRL_KEYCODE_INVALID)

MAKE_ERROR_DEFINATION(YukiThreadAssignmentDuplicateThreadIdError,   YUKI_THREAD_ATTACHMENT_DUPLICATE_ID)
MAKE_ERROR_DEFINATION(YukiThreadCreationError,                      YUKI_THREAD_CREATION_FAILED)
MAKE_ERROR_DEFINATION(YukiThreadDetachmentNotExistError,            YUKI_THREAD_DETACHMENT_NEXIST)
MAKE_ERROR_DEFINATION(YukiMutexCreationError,                       YUKI_MUTEX_CREATION_FAILED)
MAKE_ERROR_DEFINATION(YukiMutexWaitAbandoned,                       YUKI_MUTEX_WAIT_ABANDONED)
MAKE_ERROR_DEFINATION(YukiMutexWaitFunctionFailed,                  YUKI_MUTEX_WAIT_FUNC_FAILED)

MAKE_ERROR_DEFINATION(YukiEntityBindMeshExistsError,                YUKI_ENTITY_BIND_MESH_EXISTS)
MAKE_ERROR_DEFINATION(YukiEntityUnbindMeshNExistsError,             YUKI_ENTITY_UNBIND_MESH_NEXISTS)
MAKE_ERROR_DEFINATION(YukiEntityBindUndefinedMeshError,             YUKI_ENTITY_BIND_UNDEFINED_MESH)

MAKE_ERROR_DEFINATION(YukiGLFWInitError,                            GLFW_INITIALIZATION_FAILED)
MAKE_ERROR_DEFINATION(YukiWindowCreationError,                      GLFW_WINDOW_CREATION_FAILED)

MAKE_ERROR_DEFINATION(YukiGladLoadGLLoaderError,                    GLAD_LOAD_GLLOADER_FAILED)

MAKE_ERROR_DEFINATION(YukiOGLCompileShaderError,                    OPENGL_COMPILE_SHADER_ERROR)
MAKE_ERROR_DEFINATION(YukiOGLShaderProgramIsNotActived,             OPENGL_SHADER_PROGRAM_ISNOT_ACTIVED)
MAKE_ERROR_DEFINATION(YukiOGLTextureTypeNotCompatibleError,         OPENGL_TEXTURE_TYPE_NOT_COMPATIBLE)
// clang-format on

} // namespace Yuki::Debug