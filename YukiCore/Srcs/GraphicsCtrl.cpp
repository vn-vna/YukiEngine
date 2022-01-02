#include "YukiCore/YukiVE.hpp"
#include "YukiCore/Application.hpp"
#include "YukiCore/Window.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/Error.hpp"

// std
#include <algorithm>

#define YUKI_HANDLE_PTRIF_NNULL(ptr, action) \
  if (!ptr)                                  \
  action

constexpr const char* g_pCreateDebugUtilsMessengerFuncName  = "vkCreateDebugUtilsMessengerEXT";
constexpr const char* g_pDestroyDebugUtilsMessengerFuncName = "vkDestroyDebugUtilsMessengerEXT";

const std::vector<const char*> g_apValidationLayers = {
    "VK_LAYER_KHRONOS_validation"};

const std::vector<const char*> g_aRequiredQueueName = {
    Yuki::Core::YUKI_VK_GRAPHICS_FAMILY_NAME,
    Yuki::Core::YUKI_VK_PRESENT_FAMILY_NAME};

const std::vector<const char*> g_apRequiredDeviceExtension = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME};

#ifdef NDEBUG
const bool g_bEnableValidationLayers = false;
#else
const bool g_bEnableValidationLayers = true;
#endif

VkBool32 VKAPI_CALL      YukiVulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT*, void*);
void                     populateApplicationInfo(VkApplicationInfo*);
void                     populateDebugCreateInfo(VkDebugUtilsMessengerCreateInfoEXT*);
std::vector<const char*> getEnabledExtensions();
uint32_t                 getDeviceScore(VkPhysicalDevice, VkSurfaceKHR);
void                     getDeviceQueueIndices(VkPhysicalDevice, VkSurfaceKHR, Yuki::Core::QueueFamilyIndicesType*);
bool                     isDeviceFullyQueueSupported(Yuki::Core::QueueFamilyIndicesType*);
bool                     isDeviceFullySupportedExtensions(VkPhysicalDevice);
void                     querySwapChainDetails(VkPhysicalDevice, VkSurfaceKHR, Yuki::Core::YukiSwapChainDetailsType*);

VKAPI_ATTR VkBool32 VKAPI_CALL YukiVulkanDebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT             messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void*                                       pUserData)
{
  if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
  {
    Yuki::StringStream sstr{};
    sstr << pCallbackData->pMessage;
    Yuki::Core::GetYukiApp()->GetLogger()->PushErrorMessage(sstr.str());
  }

  return VK_FALSE;
}

void populateApplicationInfo(VkApplicationInfo* appInfo)
{
  appInfo->sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo->apiVersion         = VK_API_VERSION_1_0;
  appInfo->applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo->engineVersion      = VK_MAKE_VERSION(1, 0, 0);
  appInfo->pApplicationName   = "Yuki App";
  appInfo->pEngineName        = "Yuki Engine";
}

void populateDebugCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* createInfo)
{
  VkDebugUtilsMessageSeverityFlagsEXT msgSFlag = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  VkDebugUtilsMessageTypeFlagsEXT msgTFlag = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

  createInfo->sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo->messageSeverity = msgSFlag;
  createInfo->messageType     = msgTFlag;
  createInfo->pfnUserCallback = YukiVulkanDebugCallback;
  createInfo->pUserData       = nullptr;
}

std::vector<const char*> getEnabledExtensions()
{
  uint32_t     glfwExtensionCount = 0;
  const char** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char*> enabledExtension = {glfwExtensions, glfwExtensions + glfwExtensionCount};
  if (g_bEnableValidationLayers)
  {
    enabledExtension.reserve(enabledExtension.size() + 1);
    enabledExtension.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }
  return enabledExtension;
}

uint32_t getDeviceScore(VkPhysicalDevice device, VkSurfaceKHR surface)
{
  uint32_t                   score          = 0;
  VkPhysicalDeviceProperties deviceProps    = {};
  VkPhysicalDeviceFeatures   deviceFeatures = {};
  vkGetPhysicalDeviceProperties(device, &deviceProps);
  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  Yuki::Core::QueueFamilyIndicesType queueIndices;
  getDeviceQueueIndices(device, surface, &queueIndices);

  if (!isDeviceFullySupportedExtensions(device) && !isDeviceFullyQueueSupported(&queueIndices))
  {
    return score;
  }

  Yuki::Core::YukiSwapChainDetailsType swapchainDetails = {};
  querySwapChainDetails(device, surface, &swapchainDetails);

  if (swapchainDetails.aSurfaceFormat.empty() || swapchainDetails.aPresentModes.empty())
  {
    return score;
  }

  switch (deviceProps.deviceType)
  {
  case VK_PHYSICAL_DEVICE_TYPE_CPU:
    score += 100;
    break;
  case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
    score += 500;
    break;
  case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
    score += 1000;
    break;
  }

  if (deviceFeatures.geometryShader)
  {
    score += 200;
  }

  score += deviceProps.limits.maxImageDimension2D;

  return score;
}

void getDeviceQueueIndices(VkPhysicalDevice device, VkSurfaceKHR surface, Yuki::Core::QueueFamilyIndicesType* queueIndices)
{
  uint32_t                             queueFamilyCount = 0;
  VkBool32                             presentSupport   = VK_FALSE;
  std::vector<VkQueueFamilyProperties> queueFamilies    = {};

  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
  queueFamilies.resize(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

  for (uint32_t i = 0; i < queueFamilyCount; ++i)
  {
    if (queueFamilies.at(i).queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      queueIndices->emplace(Yuki::Core::YUKI_VK_GRAPHICS_FAMILY_NAME, i);
    }
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
    if (presentSupport)
    {
      queueIndices->emplace(Yuki::Core::YUKI_VK_PRESENT_FAMILY_NAME, i);
    }
  }
}

bool isDeviceFullyQueueSupported(Yuki::Core::QueueFamilyIndicesType* queueIndices)
{
  for (const AutoType& requiredFlag : g_aRequiredQueueName)
  {
    if (queueIndices->find(requiredFlag) == queueIndices->end())
      return false;
  }
  return true;
}

bool isDeviceFullySupportedExtensions(VkPhysicalDevice device)
{
  uint32_t                           deviceExtensionCount      = 0;
  std::vector<VkExtensionProperties> availableDeviceExtensions = {};

  vkEnumerateDeviceExtensionProperties(device, nullptr, &deviceExtensionCount, nullptr);
  availableDeviceExtensions.resize(deviceExtensionCount);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &deviceExtensionCount, availableDeviceExtensions.data());

  std::set<const char*> extensionChecker{g_apRequiredDeviceExtension.begin(), g_apRequiredDeviceExtension.end()};

  for (AutoType& extensionProperty : availableDeviceExtensions)
  {
    extensionChecker.erase(extensionProperty.extensionName);
  }

  return extensionChecker.empty();
}

void querySwapChainDetails(VkPhysicalDevice device, VkSurfaceKHR surface, Yuki::Core::YukiSwapChainDetailsType* swapchainDetails)
{
  memset(swapchainDetails, 0, sizeof(Yuki::Core::YukiSwapChainDetailsType));
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &(swapchainDetails->tCapabilities));

  uint32_t formatCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

  if (formatCount != 0)
  {
    swapchainDetails->aSurfaceFormat.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, swapchainDetails->aSurfaceFormat.data());
  }

  uint32_t presentModeCount;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

  if (presentModeCount != 0)
  {
    swapchainDetails->aPresentModes.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, swapchainDetails->aPresentModes.data());
  }
}

namespace Yuki::Core
{

YukiGfxControl::YukiGfxControl()
    : m_pVkInstance(nullptr),
      m_pDebugMessenger(nullptr),
      m_pSelectedPhysicalDevice(VK_NULL_HANDLE),
      m_pLogicalDevice(VK_NULL_HANDLE),
      m_pGraphicsQueue(nullptr),
      m_pVkWin32Surface(nullptr),
      m_apPhysicalDeviceList(),
      m_tSwapChainDetails()
{
}

void YukiGfxControl::CreateVulkanInstance()
{
  CheckValidationLayerSupport();
  std::vector<const char*> enabledExtension = getEnabledExtensions();

  VkApplicationInfo                  appInfo         = {};
  VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
  VkInstanceCreateInfo               createInfo      = {};

  populateApplicationInfo(&appInfo);
  populateDebugCreateInfo(&debugCreateInfo);

  createInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo        = &appInfo;
  createInfo.enabledExtensionCount   = (uint32_t) enabledExtension.size();
  createInfo.ppEnabledExtensionNames = enabledExtension.data();

  if (g_bEnableValidationLayers)
  {
    createInfo.enabledLayerCount   = (uint32_t) g_apValidationLayers.size();
    createInfo.ppEnabledLayerNames = g_apValidationLayers.data();
    createInfo.pNext               = &debugCreateInfo;
  }
  else
  {
    createInfo.pNext               = nullptr;
    createInfo.enabledLayerCount   = 0;
    createInfo.ppEnabledLayerNames = nullptr;
  }

  AutoType result = vkCreateInstance(&createInfo, nullptr, &m_pVkInstance);
  if (result != VK_SUCCESS)
  {
    THROW_YUKI_ERROR(Debug::YukiVulkanCreateInstanceError);
  }

  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  std::vector<VkExtensionProperties> extensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

#ifndef NDEBUG
  StringStream sstr{};
  sstr << extensionCount << " Available vulkan extension(s) found:\n";
  for (const auto& extension : extensions)
  {
    sstr << '\t' << extension.extensionName << '\n';
  }
  GetYukiApp()->GetLogger()->PushDebugMessage(sstr.str());
#endif // !NDEBUG
}

void YukiGfxControl::CheckValidationLayerSupport()
{
  if (g_bEnableValidationLayers)
  {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    bool layerFound;
    for (const char* layerName : g_apValidationLayers)
    {
      layerFound = false;
      for (const auto& layerProperties : availableLayers)
      {
        if (strcmp(layerName, layerProperties.layerName) == 0)
        {
          layerFound = true;
          break;
        }
      }
      if (!layerFound)
      {
        THROW_YUKI_ERROR(Debug::YukiVulkanValidateLayerError);
      }
    }
  }
}

void YukiGfxControl::SetupVulkanDebugMessenger()
{
  if (g_bEnableValidationLayers)
  {
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    populateDebugCreateInfo(&createInfo);

    AutoType createFunc = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_pVkInstance, g_pCreateDebugUtilsMessengerFuncName);
    if (!createFunc)
    {
      THROW_YUKI_ERROR(Debug::YukiVulkanGetFuncPtrCreateDebugMessageFuncError);
    }
    AutoType result = createFunc(m_pVkInstance, &createInfo, nullptr, &m_pDebugMessenger);
    if (result != VK_SUCCESS)
    {
      THROW_YUKI_ERROR(Debug::YukiVulkanCreateDebugMessengerError);
    }
  }
}

void YukiGfxControl::DestroyVulkanDebugMessenger()
{
  if (g_bEnableValidationLayers)
  {
    AutoType destroyFunc = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_pVkInstance, g_pDestroyDebugUtilsMessengerFuncName);
    if (!destroyFunc)
    {
      THROW_YUKI_ERROR(Debug::YukiVulkanGetFuncPtrDestroyDebugMessageFuncError);
    }
    destroyFunc(m_pVkInstance, m_pDebugMessenger, nullptr);
  }
}

void YukiGfxControl::CreateWin32Surface()
{
  VkWin32SurfaceCreateInfoKHR createInfo = {};
  createInfo.sType                       = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  createInfo.hwnd                        = Yuki::Core::GetYukiApp()->GetWindow()->GetWindowHandler();
  createInfo.hinstance                   = GetModuleHandle(NULL);

  AutoType result = vkCreateWin32SurfaceKHR(m_pVkInstance, &createInfo, nullptr, &m_pVkWin32Surface);
  if (result != VK_SUCCESS)
  {
    THROW_YUKI_ERROR(Debug::YukiVulkanCreateWin32SurfaceKHRError);
  }

#ifndef NDEBUG
  GetYukiApp()->GetLogger()->PushDebugMessage(L"Create Vulkan Win32 Surface KHR successfully\n");
#endif // !NDEBUG
}

void YukiGfxControl::SelectSurfaceSwapChainFormat()
{
  bool found_compatible = false;
  for (const AutoType& format : m_tSwapChainDetails.aSurfaceFormat)
  {
    if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
    {
      m_tCompatibleSurfaceFormat = format;
      found_compatible           = true;
      break;
    }
  }

  if (!found_compatible)
  {
    m_tCompatibleSurfaceFormat = m_tSwapChainDetails.aSurfaceFormat.at(0);
  }
}

void YukiGfxControl::SelectCompatiblePresentMode()
{
  bool found_compatible = false;
  for (const AutoType& present : m_tSwapChainDetails.aPresentModes)
  {
    if (present == VK_PRESENT_MODE_MAILBOX_KHR)
    {
      m_eCompatiblePresentMode = present;
      found_compatible         = true;
      break;
    }
  }

  if (!found_compatible)
  {
    m_eCompatiblePresentMode = VK_PRESENT_MODE_FIFO_KHR;
  }
}

void YukiGfxControl::SelectSwapExtent()
{
  if (m_tSwapChainDetails.tCapabilities.currentExtent.width != UINT32_MAX)
  {
    m_tVkExtent2D = m_tSwapChainDetails.tCapabilities.currentExtent;
  }
  else
  {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(GetYukiApp()->GetWindow()->GetGLFWWindow(), &windowWidth, &windowHeight);

    m_tVkExtent2D.width = std::clamp(
        m_tSwapChainDetails.tCapabilities.minImageExtent.width,
        (uint32_t) windowWidth,
        m_tSwapChainDetails.tCapabilities.maxImageExtent.width);

    m_tVkExtent2D.height = std::clamp(
        m_tSwapChainDetails.tCapabilities.minImageExtent.height,
        (uint32_t) windowWidth,
        m_tSwapChainDetails.tCapabilities.maxImageExtent.height);
  }
}

void YukiGfxControl::CreatePhysicalDeviceList()
{
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(m_pVkInstance, &deviceCount, nullptr);
  if (deviceCount == 0)
  {
    THROW_YUKI_ERROR(Debug::YukiVulkanNoSupportedPhysicalDeviceFoundError);
  }

  std::vector<VkPhysicalDevice> rawPhysicalDeviceList(deviceCount);
  vkEnumeratePhysicalDevices(m_pVkInstance, &deviceCount, rawPhysicalDeviceList.data());

  m_apPhysicalDeviceList.reserve(deviceCount);

  for (AutoType device : rawPhysicalDeviceList)
  {
    m_apPhysicalDeviceList.emplace_back(device, getDeviceScore(device, m_pVkWin32Surface));
  }

  AutoType deviceSortFunc = [](DeviceAndScoreType& pa, DeviceAndScoreType& pb) {
    return pa.second > pb.second;
  };
  std::sort(m_apPhysicalDeviceList.data(), m_apPhysicalDeviceList.data() + m_apPhysicalDeviceList.size(), deviceSortFunc);
}

void YukiGfxControl::SelectPhysicalDevice()
{
  CreatePhysicalDeviceList();
  AutoType deviceWillSelect = m_apPhysicalDeviceList.begin();
  if (deviceWillSelect->second == 0)
  {
    THROW_YUKI_ERROR(Debug::YukiVulkanNoSupportedPhysicalDeviceFoundError);
  }
  m_pSelectedPhysicalDevice = deviceWillSelect->first;

  getDeviceQueueIndices(m_pSelectedPhysicalDevice, m_pVkWin32Surface, &m_aCrrPhysicalDeviceQueueIndices);
  querySwapChainDetails(m_pSelectedPhysicalDevice, m_pVkWin32Surface, &m_tSwapChainDetails);

#ifndef NDEBUG
  // Report selected device
  VkPhysicalDeviceProperties deviceProperties = {};
  vkGetPhysicalDeviceProperties(m_pSelectedPhysicalDevice, &deviceProperties);
  StringStream sstr{};
  sstr << "Selected Physical device"
       << "\n\tSelected device " << deviceProperties.deviceName
       << "\n\tAPI Version: " << deviceProperties.apiVersion
       << "\n\tDriver version: " << deviceProperties.driverVersion
       << "\n\tDevice rating: " << deviceWillSelect->second
       << "\n";
  GetYukiApp()->GetLogger()->PushDebugMessage(sstr.str());
#endif // !NDEBUG
}

void YukiGfxControl::CreateVulkanLogicalDevice()
{
  float                                queuePrioty  = 1.0f;
  uint32_t                             queueCount   = 1;
  VkDeviceQueueCreateFlags             dqCreateFlag = 0;
  std::vector<VkDeviceQueueCreateInfo> deviceQueueCreateInfo;

  deviceQueueCreateInfo.reserve(g_apValidationLayers.size());
  for (AutoType& requiredQueueFlagBit : g_aRequiredQueueName)
  {
    VkDeviceQueueCreateInfo dqci = {
        VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        nullptr,
        dqCreateFlag,
        m_aCrrPhysicalDeviceQueueIndices.at(requiredQueueFlagBit),
        queueCount, &queuePrioty};
    deviceQueueCreateInfo.emplace_back(dqci);
  }

  VkPhysicalDeviceFeatures physicalDeviceFeature = {};
  VkDeviceCreateInfo       deviceCreateInfo      = {};
  deviceCreateInfo.sType                         = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  deviceCreateInfo.pQueueCreateInfos             = deviceQueueCreateInfo.data();
  deviceCreateInfo.queueCreateInfoCount          = (uint32_t) deviceQueueCreateInfo.size();
  deviceCreateInfo.pEnabledFeatures              = &physicalDeviceFeature;
  deviceCreateInfo.enabledExtensionCount         = (uint32_t) g_apRequiredDeviceExtension.size();
  deviceCreateInfo.ppEnabledExtensionNames       = g_apRequiredDeviceExtension.data();

  if (g_bEnableValidationLayers)
  {
    deviceCreateInfo.enabledLayerCount   = static_cast<uint32_t>(g_apValidationLayers.size());
    deviceCreateInfo.ppEnabledLayerNames = g_apValidationLayers.data();
  }
  else
  {
    deviceCreateInfo.enabledLayerCount   = 0;
    deviceCreateInfo.ppEnabledLayerNames = nullptr;
  }

  AutoType result = vkCreateDevice(m_pSelectedPhysicalDevice, &deviceCreateInfo, nullptr, &m_pLogicalDevice);
  if (result != VK_SUCCESS)
  {
    THROW_YUKI_ERROR(Debug::YukiVulkanCreateLogicalDeviceError);
  }

#ifndef NDEBUG
  GetYukiApp()->GetLogger()->PushDebugMessage(L"Create Vulkan Logical device successfully\n");
#endif // !NDEBUG

  vkGetDeviceQueue(m_pLogicalDevice, m_aCrrPhysicalDeviceQueueIndices.at(YUKI_VK_GRAPHICS_FAMILY_NAME), 0, &m_pGraphicsQueue);
  vkGetDeviceQueue(m_pLogicalDevice, m_aCrrPhysicalDeviceQueueIndices.at(YUKI_VK_PRESENT_FAMILY_NAME), 0, &m_pPresentQueue);
}

void YukiGfxControl::CreateVulkanSwapChain()
{

  uint32_t minImgCount = m_tSwapChainDetails.tCapabilities.minImageCount + 1;
  if (m_tSwapChainDetails.tCapabilities.maxImageCount > 0 &&
      minImgCount > m_tSwapChainDetails.tCapabilities.maxImageCount)
  {
    minImgCount = m_tSwapChainDetails.tCapabilities.maxImageCount;
  }

  VkSwapchainCreateInfoKHR createInfo = {};
  createInfo.sType                    = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.surface                  = m_pVkWin32Surface;
  createInfo.minImageCount            = minImgCount;
  createInfo.imageFormat              = m_tCompatibleSurfaceFormat.format;
  createInfo.imageColorSpace          = m_tCompatibleSurfaceFormat.colorSpace;
  createInfo.imageExtent              = m_tVkExtent2D;
  createInfo.imageArrayLayers         = 1;
  createInfo.imageUsage               = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  if (m_aCrrPhysicalDeviceQueueIndices.at(YUKI_VK_GRAPHICS_FAMILY_NAME) !=
      m_aCrrPhysicalDeviceQueueIndices.at(YUKI_VK_PRESENT_FAMILY_NAME))
  {
    uint32_t queueIndices[]          = {m_aCrrPhysicalDeviceQueueIndices.at(YUKI_VK_GRAPHICS_FAMILY_NAME),
        m_aCrrPhysicalDeviceQueueIndices.at(YUKI_VK_PRESENT_FAMILY_NAME)};
    createInfo.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = (uint32_t) ARRAYSIZE(queueIndices);
    createInfo.pQueueFamilyIndices   = queueIndices;
  }
  else
  {
    createInfo.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0;
    createInfo.pQueueFamilyIndices   = nullptr;
  }

  createInfo.preTransform   = m_tSwapChainDetails.tCapabilities.currentTransform;
  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  createInfo.presentMode    = m_eCompatiblePresentMode;
  createInfo.clipped        = VK_TRUE;
  createInfo.oldSwapchain   = VK_NULL_HANDLE;

  AutoType result = vkCreateSwapchainKHR(m_pLogicalDevice, &createInfo, nullptr, &m_pVkSwapChain);
  if (result != VK_SUCCESS)
  {
    THROW_YUKI_ERROR(Debug::YukiVulkanCreateSwapChainError);
  }
#ifndef NDEBUG
  GetYukiApp()->GetLogger()->PushDebugMessage(L"Created Vulkan Swapchain\n");
#endif // !NDEBUG
}

void YukiGfxControl::GetSwapChainImage()
{
  uint32_t imageCount = 0;
  vkGetSwapchainImagesKHR(m_pLogicalDevice, m_pVkSwapChain, &imageCount, nullptr);
  m_apSwapChainImages.resize(imageCount);
  vkGetSwapchainImagesKHR(m_pLogicalDevice, m_pVkSwapChain, &imageCount, m_apSwapChainImages.data());
}

void YukiGfxControl::DestroyVkSwapChainKHR()
{
  if (!m_pLogicalDevice && !m_pVkSwapChain)
    vkDestroySwapchainKHR(m_pLogicalDevice, m_pVkSwapChain, nullptr);
}

void YukiGfxControl::DestroyVkLogicalDevice()
{
  if (!m_pLogicalDevice)
    vkDestroyDevice(m_pLogicalDevice, nullptr);
}

void YukiGfxControl::DestroyVkSurfaceKHR()
{
  if (!m_pVkWin32Surface && !m_pVkInstance)
    vkDestroySurfaceKHR(m_pVkInstance, m_pVkWin32Surface, nullptr);
}

void YukiGfxControl::DestroyVkInstance()
{
  if (!m_pVkInstance)
    vkDestroyInstance(m_pVkInstance, nullptr);
}

void YukiGfxControl::Create()
{
  CreateVulkanInstance();
  SetupVulkanDebugMessenger();
  CreateWin32Surface();
  SelectPhysicalDevice();
  SelectSurfaceSwapChainFormat();
  SelectCompatiblePresentMode();
  SelectSwapExtent();
  CreateVulkanLogicalDevice();
  CreateVulkanSwapChain();
  GetSwapChainImage();
}

void YukiGfxControl::Awake()
{
}

void YukiGfxControl::Update()
{
}

void YukiGfxControl::Render()
{
}

void YukiGfxControl::Destroy()
{
  DestroyVkSwapChainKHR();
  DestroyVkLogicalDevice();
  DestroyVkSurfaceKHR();
  DestroyVulkanDebugMessenger();
  DestroyVkInstance();
}

SharedPtr<IYukiGfxControl> YukiGfxControl::CreateYukiGfxController()
{
  return {(IYukiGfxControl*) (new YukiGfxControl()), [](IYukiGfxControl* p) { delete p; }};
}

} // namespace Yuki::Core