#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiGfxPipeline.h"
#include "YukiCore/YukiError.hpp"
#include "YukiCore/YukiLogger.hpp"

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
      m_strVSFilePath(vspath),
      m_strFSFilePath(fspath)
{}

void YukiGfxPipeline::Create()
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

void YukiGfxPipeline::Destroy()
{
  AutoType device = GetYukiApp()->GetGraphicsController()->GetVkLogicalDevice();
  if (m_pVertexShader)
  {
    vkDestroyShaderModule(device, m_pVertexShader, nullptr);
  }
  if (m_pFragmentShader)
  {
    vkDestroyShaderModule(device, m_pFragmentShader, nullptr);
  }
}

SharedPtr<IYukiGfxPipeline> YukiGfxPipeline::CreateGfxPipeline(const String& vspath, const String& fspath)
{
  return {(IYukiGfxPipeline*) new YukiGfxPipeline(vspath, fspath), [](IYukiGfxPipeline* p) { delete p; }};
}

} // namespace Yuki::Core