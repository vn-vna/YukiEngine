/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"

#define DECLARE_YUKI_ERROR(__err_name)                      \
  class YUKIAPI Yuki##__err_name : virtual public YukiError \
  {                                                         \
  public:                                                   \
    Yuki##__err_name(const String& file, const int& line);  \
    virtual ~Yuki##__err_name() = default;                  \
  }

#define THROW_YUKI_ERROR(__err_name) throw Yuki::Debug::Yuki##__err_name(__FILE__, __LINE__)

namespace Yuki::Debug
{

enum class YukiErrCode
{
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
  GLFW_INITIALIZATION_FAILED,
  GLFW_WINDOW_CREATION_FAILED,
  GLAD_LOAD_GLLOADER_FAILED,
  OPENGL_COMPILE_SHADER_ERROR,
  OPENGL_SHADER_PROGRAM_ISNOT_ACTIVED,
  OPENGL_TEXTURE_TYPE_NOT_COMPATIBLE,
  ASSIMP_MODEL_CANT_BE_LOADED,
  SCENE_DUPLICATE_ENTITY_NAME
};

class YUKIAPI YukiError : virtual protected std::exception
{
protected:
  YukiErrCode m_ErrCode;
  String      m_File;
  int         m_nLine;

public:
  YukiError(const YukiErrCode& code, const String& file, const int& line);
  ~YukiError() override = default;

  String             getErrorMessage() const;
  const YukiErrCode& getErrorCode() const;
  void               PushErrorMessage() const;
};

DECLARE_YUKI_ERROR(CreateLogFileError);
DECLARE_YUKI_ERROR(InpCtrlInsertCallbackExistsError);
DECLARE_YUKI_ERROR(InpCtrlRemoveCallbackNExistsError);
DECLARE_YUKI_ERROR(InpCtrlInvokeUndefinedCallbackError);
DECLARE_YUKI_ERROR(InpCtrlKeyCodeInvalidError);
DECLARE_YUKI_ERROR(ThreadAssignmentDuplicateThreadIdError);
DECLARE_YUKI_ERROR(ThreadCreationError);
DECLARE_YUKI_ERROR(ThreadDetachmentNotExistError);
DECLARE_YUKI_ERROR(MutexCreationError);
DECLARE_YUKI_ERROR(MutexWaitAbandoned);
DECLARE_YUKI_ERROR(MutexWaitFunctionFailed);
DECLARE_YUKI_ERROR(GLFWInitError);
DECLARE_YUKI_ERROR(WindowCreationError);
DECLARE_YUKI_ERROR(GladLoadGLLoaderError);
DECLARE_YUKI_ERROR(OGLCompileShaderError);
DECLARE_YUKI_ERROR(OGLShaderProgramIsNotActived);
DECLARE_YUKI_ERROR(OGLTextureTypeNotCompatibleError);
DECLARE_YUKI_ERROR(AssimpModelCantBeLoaded);
DECLARE_YUKI_ERROR(SceneDuplicateEntityName);

} // namespace Yuki::Debug