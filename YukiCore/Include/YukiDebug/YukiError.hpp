#pragma once

#include "YukiCore/YukiPCH.hpp"

#define DECLARE_YUKI_ERROR(__err_name)                 \
  class YUKIAPI __err_name## : public YukiError        \
  {                                                    \
  public:                                              \
    __err_name##(const String& file, const int& line); \
    virtual ~__err_name##() = default;                 \
  }

#define THROW_YUKI_ERROR(__err_name) throw __err_name##(__FILEW__, __LINE__)

namespace Yuki::Debug
{

enum class YUKIAPI YukiErrCode
{
  YUKI_APP_RECREATION_ERROR,
  YUKI_APP_NOT_CREATED_ERROR,
  YUKI_APP_INSTANCE_ALREADY_EXISTS,
  YUKI_GFXCTRL_NOT_CREATED_ERROR,
  YUKI_GFXCTRL_RECREATION_ERROR,
  YUKI_WINDOW_NOT_CREATED_ERROR,
  YUKI_WINDOW_RECREATION_ERROR,
  YUKI_LOGGER_CREATE_LOGFILE_ERROR,
  YUKI_INPCTRL_INSERT_CALLBACK_EXISTS,
  YUKI_INPCTRL_REMOVE_CALLBACK_NEXIST,
  YUKI_INPCTRL_INVOKE_UNDEFINED_CALLBACK,
  YUKI_INPCTRL_KEYCODE_INVALID,
  YUKI_THREAD_ATTACHMENT_DUPLICATE_ID,
  YUKI_THREAD_CREATION_FAILED,
  YUKI_THREAD_DETACHMENT_NEXIST,
  YUKI_MUTEX_CREATION_FAILED,
  YUKI_MUTEX_WAIT_ABANDONED,
  YUKI_MUTEX_WAIT_FUNC_FAILED,
  YUKI_ENTITY_BIND_MESH_EXISTS,
  YUKI_ENTITY_UNBIND_MESH_NEXISTS,
  YUKI_ENTITY_BIND_UNDEFINED_MESH,
  GLFW_INITIALIZATION_FAILED,
  GLFW_WINDOW_CREATION_FAILED,
  GLAD_LOAD_GLLOADER_FAILED,
  OPENGL_COMPILE_SHADER_ERROR,
  OPENGL_SHADER_PROGRAM_ISNOT_ACTIVED,
  OPENGL_TEXTURE_TYPE_NOT_COMPATIBLE,
  ASSIMP_LOAD_MODEL_FAILED,
};

class YUKIAPI YukiError : public std::runtime_error
{
protected:
  YukiErrCode m_ErrCode;
  String      m_File;
  int         m_nLine;

public:
  YukiError(const YukiErrCode& code, const String& file, const int& line);
  virtual ~YukiError() = default;

  String             getErrorMessage() const;
  const YukiErrCode& getErrorCode() const;
};

DECLARE_YUKI_ERROR(YukiApplicationRecreationError);
DECLARE_YUKI_ERROR(YukiApplicationNotCreatedError);
DECLARE_YUKI_ERROR(YukiApplicationInstanceExistsError);
DECLARE_YUKI_ERROR(YukiGfxControlRecreationError);
DECLARE_YUKI_ERROR(YukiGfxControlNotCreatedError);
DECLARE_YUKI_ERROR(YukiWindowRecreationError);
DECLARE_YUKI_ERROR(YukiWindowNotCreatedError);

DECLARE_YUKI_ERROR(YukiCreateLogFileError);

DECLARE_YUKI_ERROR(YukiInpCtrlInsertCallbackExistsError);
DECLARE_YUKI_ERROR(YukiInpCtrlRemoveCallbackNExistsError);
DECLARE_YUKI_ERROR(YukiInpCtrlInvokeUndefinedCallbackError);
DECLARE_YUKI_ERROR(YukiInpCtrlKeyCodeInvalidError);

DECLARE_YUKI_ERROR(YukiThreadAssignmentDuplicateThreadIdError);
DECLARE_YUKI_ERROR(YukiThreadCreationError);
DECLARE_YUKI_ERROR(YukiThreadDetachmentNotExistError);
DECLARE_YUKI_ERROR(YukiMutexCreationError);
DECLARE_YUKI_ERROR(YukiMutexWaitAbandoned);
DECLARE_YUKI_ERROR(YukiMutexWaitFunctionFailed);

DECLARE_YUKI_ERROR(YukiEntityBindMeshExistsError);
DECLARE_YUKI_ERROR(YukiEntityUnbindMeshNExistsError);
DECLARE_YUKI_ERROR(YukiEntityBindUndefinedMeshError);

DECLARE_YUKI_ERROR(YukiGLFWInitError);
DECLARE_YUKI_ERROR(YukiWindowCreationError);

DECLARE_YUKI_ERROR(YukiGladLoadGLLoaderError);

DECLARE_YUKI_ERROR(YukiOGLCompileShaderError);
DECLARE_YUKI_ERROR(YukiOGLShaderProgramIsNotActived);
DECLARE_YUKI_ERROR(YukiOGLTextureTypeNotCompatibleError);

DECLARE_YUKI_ERROR(YukiAssimpLoadModelFailed);

} // namespace Yuki::Debug