#pragma once

#include "YukiCore/YukiVE.hpp"
#include "YukiCore/YukiObject.hpp"
#include "Logger.hpp"

namespace Yuki::Core
{

constexpr AutoType YUKI_VK_GRAPHICS_FAMILY_NAME = "YUKI_VK_GRAPHICS_FAMILY_NAME";
constexpr AutoType YUKI_VK_PRESENT_FAMILY_NAME  = "YUKI_VK_PRESENT_FAMILY_NAME";

using DeviceAndScoreType     = std::pair<VkPhysicalDevice, uint32_t>;
using PhysicalDeviceListType = std::vector<DeviceAndScoreType>;
using QueueFamilyIndicesType = std::map<const char*, uint32_t>;
using SwapChainImgArrayType  = std::vector<VkImage>;

typedef struct YUKIAPI StYukiSwapChainDetails
{
  VkSurfaceCapabilitiesKHR        tCapabilities;
  std::vector<VkSurfaceFormatKHR> aSurfaceFormat;
  std::vector<VkPresentModeKHR>   aPresentModes;
} YukiSwapChainDetailsType;

class YUKIAPI IYukiGfxControl : public IYukiObject
{
protected:
  virtual void CreateVulkanInstance()         = 0;
  virtual void CheckValidationLayerSupport()  = 0;
  virtual void SetupVulkanDebugMessenger()    = 0;
  virtual void CreateWin32Surface()           = 0;
  virtual void SelectSurfaceSwapChainFormat() = 0;
  virtual void SelectCompatiblePresentMode()  = 0;
  virtual void SelectSwapExtent()             = 0;
  virtual void CreatePhysicalDeviceList()     = 0;
  virtual void SelectPhysicalDevice()         = 0;
  virtual void CreateVulkanLogicalDevice()    = 0;
  virtual void CreateVulkanSwapChain()        = 0;
  virtual void GetSwapChainImage()            = 0;
  virtual void DestroyVkSwapChainKHR()        = 0;
  virtual void DestroyVkLogicalDevice()       = 0;
  virtual void DestroyVkSurfaceKHR()          = 0;
  virtual void DestroyVulkanDebugMessenger()  = 0;
  virtual void DestroyVkInstance()            = 0;

public:
  IYukiGfxControl()          = default;
  virtual ~IYukiGfxControl() = default;
};

class YUKIAPI YukiGfxControl : public IYukiGfxControl
{
protected:
  VkInstance               m_pVkInstance;
  VkDebugUtilsMessengerEXT m_pDebugMessenger;
  VkPhysicalDevice         m_pSelectedPhysicalDevice;
  VkDevice                 m_pLogicalDevice;
  VkQueue                  m_pGraphicsQueue;
  VkQueue                  m_pPresentQueue;
  VkSurfaceKHR             m_pVkWin32Surface;
  QueueFamilyIndicesType   m_aCrrPhysicalDeviceQueueIndices;
  PhysicalDeviceListType   m_apPhysicalDeviceList;
  YukiSwapChainDetailsType m_tSwapChainDetails;
  VkSurfaceFormatKHR       m_tCompatibleSurfaceFormat;
  VkPresentModeKHR         m_eCompatiblePresentMode;
  VkExtent2D               m_tVkExtent2D;
  VkSwapchainKHR           m_pVkSwapChain;
  SwapChainImgArrayType    m_apSwapChainImages;

  void CreateVulkanInstance() override;
  void CheckValidationLayerSupport() override;
  void SetupVulkanDebugMessenger() override;
  void CreateWin32Surface() override;
  void SelectSurfaceSwapChainFormat() override;
  void SelectCompatiblePresentMode() override;
  void SelectSwapExtent() override;
  void CreatePhysicalDeviceList() override;
  void SelectPhysicalDevice() override;
  void CreateVulkanLogicalDevice() override;
  void CreateVulkanSwapChain() override;
  void GetSwapChainImage() override;
  void DestroyVkSwapChainKHR() override;
  void DestroyVkLogicalDevice() override;
  void DestroyVkSurfaceKHR() override;
  void DestroyVulkanDebugMessenger() override;
  void DestroyVkInstance() override;

public:
  YukiGfxControl();
  virtual ~YukiGfxControl() = default;

  void Create() override;
  void Awake() override;
  void Update() override;
  void Render() override;
  void Destroy() override;

  static SharedPtr<IYukiGfxControl> CreateYukiGfxController();
};


} // namespace Yuki::Core