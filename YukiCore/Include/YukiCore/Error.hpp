#pragma once

#include "YukiCore/YukiVE.hpp"

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
  YUKI_LOGGER_CREATE_LOGFILE_ERROR,
  YUKI_INPCTRL_INSERT_CALLBACK_EXISTS,
  YUKI_INPCTRL_REMOVE_CALLBACK_NEXIST,
  UIKI_INPCTRL_INVOKE_UNDEFINED_CALLBACK,
  GLFW_INITIALIZATION_FAILED,
  GLFW_WINDOW_CREATION_FAILED,
  VULKAN_CREATE_INSTANCE_FAILED,
  VULKAN_CHECK_VALIDATION_LAYER_FAILED,
  VULKAN_GETFUNCPTR_CREATE_DEBUG_MESSAGE_FUNC_FAILED,
  VULKAN_GETFUNCPTR_DESTROY_DEBUG_MESSAGE_FUNC_FAILED,
  VULKAN_CREATE_DEBUG_MESSENGER_FAILED,
  VULKAN_NO_SUPPORTED_PHYSICAL_DEVICE_FOUND,
  VULKAN_CREATE_LOGICAL_DEVICE_FAILED,
  VULKAN_CREATE_WIN32_SURFACE_KHR_FAILED,
  VULKAN_CREATE_SWAPCHAIN_FAILED,
  VULKAN_CREATE_SWAPCHAIN_IMAGE_VIEW_FAILED
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

DECLARE_YUKI_ERROR(YukiCreateLogFileError);
DECLARE_YUKI_ERROR(YukiInpCtrlInsertCallbackExistsError);
DECLARE_YUKI_ERROR(YukiInpCtrlRemoveCallbackNExistsError);
DECLARE_YUKI_ERROR(YukiInpCtrlInvokeUndefinedCallbackError);
DECLARE_YUKI_ERROR(YukiGLFWInitError);
DECLARE_YUKI_ERROR(YukiWindowCreationError);
DECLARE_YUKI_ERROR(YukiVulkanCreateInstanceError);
DECLARE_YUKI_ERROR(YukiVulkanValidateLayerError);
DECLARE_YUKI_ERROR(YukiVulkanGetFuncPtrCreateDebugMessageFuncError);
DECLARE_YUKI_ERROR(YukiVulkanGetFuncPtrDestroyDebugMessageFuncError);
DECLARE_YUKI_ERROR(YukiVulkanCreateDebugMessengerError);
DECLARE_YUKI_ERROR(YukiVulkanNoSupportedPhysicalDeviceFoundError);
DECLARE_YUKI_ERROR(YukiVulkanCreateLogicalDeviceError);
DECLARE_YUKI_ERROR(YukiVulkanCreateWin32SurfaceKHRError);
DECLARE_YUKI_ERROR(YukiVulkanCreateSwapChainError);
DECLARE_YUKI_ERROR(YukiVulkanCreateSwapChainImageViewError);

} // namespace Yuki::Debug