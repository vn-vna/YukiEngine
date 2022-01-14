#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"

namespace Yuki::Core
{

class YUKIAPI IYukiGfxPipeline : public IYukiObject
{
public:
  IYukiGfxPipeline()          = default;
  virtual ~IYukiGfxPipeline() = default;
};

class YUKIAPI YukiGfxPipeline : public IYukiGfxPipeline
{
protected:
  VkShaderModule m_pVertexShader;
  VkShaderModule m_pFragmentShader;
  String         m_strVSFilePath;
  String         m_strFSFilePath;


public:
  YukiGfxPipeline(const String& vspath, const String& fspath);
  virtual ~YukiGfxPipeline() = default;

  void Create() override;
  void Destroy() override;

  static SharedPtr<IYukiGfxPipeline> CreateGfxPipeline(const String& vspath, const String& fspath);
};

} // namespace Yuki::Core