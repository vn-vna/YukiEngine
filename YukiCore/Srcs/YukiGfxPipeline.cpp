#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiGfxPipeline.h"
#include "YukiCore/YukiError.hpp"
#include "YukiCore/YukiLogger.hpp"
#include "YukiCore/YukiWindow.hpp"

namespace Yuki::Core
{

void loadShaderCode(String shaderPath, std::vector<char>& storage);

void loadShaderCode(String shaderPath, std::vector<char>& storage)
{
  std::ifstream inpf{shaderPath, std::ios::ate | std::ios::binary};
  if (!inpf.good())
  {
    THROW_YUKI_ERROR(Debug::YukiShaderCodeBadFileError);
  }
  size_t fileSize = inpf.tellg();

  storage.resize(fileSize);

  inpf.seekg(0);
  inpf.read(storage.data(), fileSize);
  inpf.close();
}

VkShaderModule createShaderModuleFromCode(std::vector<char>& code)
{
  VkShaderModuleCreateInfo smci = {};
  smci.sType                    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  smci.codeSize                 = code.size();
  smci.pCode                    = reinterpret_cast<const uint32_t*>(code.data());

  VkShaderModule shaderModule = nullptr;
  AutoType       device       = Yuki::Core::GetYukiApp()->GetGraphicsController()->GetVkLogicalDevice();
  AutoType       result       = vkCreateShaderModule(device, &smci, nullptr, &shaderModule);
  if (result != VK_SUCCESS)
  {
    THROW_YUKI_ERROR(Debug::YukiShaderCreateModuleError);
  }
  return shaderModule;
}

YukiGfxPipeline::YukiGfxPipeline(const String& vspath, const String& fspath)
    : m_pVertexShader(nullptr),
      m_pFragmentShader(nullptr),
      m_pVkPipelineLayout(nullptr),
      m_strVSFilePath(vspath),
      m_strFSFilePath(fspath)
{}

void YukiGfxPipeline::CreatePipelineStage()
{
  // Vertex shader stage Ci

  VkPipelineShaderStageCreateInfo vsPssci{};
  vsPssci.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vsPssci.stage  = VK_SHADER_STAGE_VERTEX_BIT;
  vsPssci.module = m_pVertexShader;
  vsPssci.pName  = "main";

  // Fragment shader stage Ci

  VkPipelineShaderStageCreateInfo fsPssci{};
  fsPssci.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fsPssci.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
  fsPssci.module = m_pFragmentShader;
  fsPssci.pName  = "main";

  // Merge 2 of above

  VkPipelineShaderStageCreateInfo pssci[] = {vsPssci, fsPssci};

  // Vertex input stage Ci
  VkPipelineVertexInputStateCreateInfo pvisci{};
  pvisci.sType                         = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  pvisci.vertexBindingDescriptionCount = 0;
  pvisci.pVertexBindingDescriptions    = nullptr;
  pvisci.vertexBindingDescriptionCount = 0;
  pvisci.pVertexBindingDescriptions    = nullptr;

  // Input assembly stage Ci
  VkPipelineInputAssemblyStateCreateInfo piasci{};
  piasci.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  piasci.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  piasci.primitiveRestartEnable = VK_FALSE;

  // Create viewport
  glm::vec2  windowSize = Yuki::Core::GetYukiApp()->GetWindow()->GetWindowSize();
  VkViewport viewport{};
  viewport.x        = 0.0f;
  viewport.y        = 0.0f;
  viewport.width    = windowSize.x;
  viewport.height   = windowSize.y;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = Core::GetYukiApp()->GetGraphicsController()->GetVkExtent2D();

  VkPipelineViewportStateCreateInfo pvsci{};
  pvsci.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  pvsci.viewportCount = 1;
  pvsci.pViewports    = &viewport;
  pvsci.scissorCount  = 1;
  pvsci.pScissors     = &scissor;

  // Rasterizer stage Ci
  VkPipelineRasterizationStateCreateInfo prsci{};
  prsci.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  prsci.depthClampEnable        = VK_FALSE;
  prsci.rasterizerDiscardEnable = VK_FALSE;
  prsci.polygonMode             = VK_POLYGON_MODE_FILL;
  prsci.lineWidth               = 1.0f;
  prsci.cullMode                = VK_CULL_MODE_BACK_BIT;
  prsci.frontFace               = VK_FRONT_FACE_CLOCKWISE;
  prsci.depthBiasEnable         = VK_FALSE;
  prsci.depthBiasConstantFactor = 0.0f;
  prsci.depthBiasClamp          = 0.0f;
  prsci.depthBiasSlopeFactor    = 0.0f;

  // Multi sampling
  VkPipelineMultisampleStateCreateInfo pmssci{};
  pmssci.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  pmssci.sampleShadingEnable   = VK_FALSE;
  pmssci.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
  pmssci.minSampleShading      = 1.0f;
  pmssci.pSampleMask           = nullptr;
  pmssci.alphaToCoverageEnable = VK_FALSE;
  pmssci.alphaToOneEnable      = VK_FALSE;

  // Color blending
  VkPipelineColorBlendAttachmentState pcbas{};
  pcbas.colorWriteMask      = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  pcbas.blendEnable         = VK_FALSE;
  pcbas.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
  pcbas.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
  pcbas.colorBlendOp        = VK_BLEND_OP_ADD;
  pcbas.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  pcbas.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  pcbas.alphaBlendOp        = VK_BLEND_OP_ADD;

  VkPipelineColorBlendStateCreateInfo pcbsci{};
  pcbsci.sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  pcbsci.logicOpEnable     = VK_FALSE;
  pcbsci.logicOp           = VK_LOGIC_OP_COPY;
  pcbsci.attachmentCount   = 1;
  pcbsci.pAttachments      = &pcbas;
  pcbsci.blendConstants[0] = 0.0f;
  pcbsci.blendConstants[1] = 0.0f;
  pcbsci.blendConstants[2] = 0.0f;
  pcbsci.blendConstants[3] = 0.0f;


  // Dynamic states Ci
  VkDynamicState dynamicStates[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_LINE_WIDTH};

  VkPipelineDynamicStateCreateInfo pdsci{};
  pdsci.sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  pdsci.dynamicStateCount = 2;
  pdsci.pDynamicStates    = dynamicStates;

  VkPipelineLayoutCreateInfo plci{};
  plci.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  plci.setLayoutCount         = 0;
  plci.pSetLayouts            = nullptr;
  plci.pushConstantRangeCount = 0;
  plci.pPushConstantRanges    = nullptr;

  AutoType logicalDevice = Core::GetYukiApp()->GetGraphicsController()->GetVkLogicalDevice();
  if (vkCreatePipelineLayout(logicalDevice, &plci, nullptr, &m_pVkPipelineLayout) != VK_SUCCESS)
  {
    THROW_YUKI_ERROR(Debug::YukiVulkanCreatePipelineLayoutError);
  }
}

void YukiGfxPipeline::CreateShaderModules()
{
  try
  {
    std::vector<char> vertCode;
    loadShaderCode(m_strVSFilePath.c_str(), vertCode);
    std::vector<char> fragCode;
    loadShaderCode(m_strFSFilePath.c_str(), fragCode);
    m_pVertexShader   = createShaderModuleFromCode(vertCode);
    m_pFragmentShader = createShaderModuleFromCode(fragCode);
  }
  catch (Debug::YukiError& err)
  {
    AutoType& logger = GetYukiApp()->GetLogger();
    logger->PushDebugMessage(err.getErrorMessage());
  }
}

void YukiGfxPipeline::Create()
{
  CreateShaderModules();
  CreatePipelineStage();
}

void YukiGfxPipeline::Destroy()
{
  AutoType device = GetYukiApp()->GetGraphicsController()->GetVkLogicalDevice();
  if (m_pVkPipelineLayout)
  {
    vkDestroyPipelineLayout(device, m_pVkPipelineLayout, nullptr);
  }
  if (m_pVertexShader)
  {
    vkDestroyShaderModule(device, m_pVertexShader, nullptr);
  }
  if (m_pFragmentShader)
  {
    vkDestroyShaderModule(device, m_pFragmentShader, nullptr);
  }
}

SharedPtr<IYukiGfxPipeline> YukiGfxPipeline::CreateYukiGfxPipeline(const String& vspath, const String& fspath)
{
  return {(IYukiGfxPipeline*) new YukiGfxPipeline(vspath, fspath), [](IYukiGfxPipeline* p) { delete p; }};
}

} // namespace Yuki::Core