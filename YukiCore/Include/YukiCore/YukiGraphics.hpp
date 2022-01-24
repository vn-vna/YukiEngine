#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiLogger.hpp"
#include "YukiCore/YukiThread.hpp"

namespace Yuki::Core
{

class YUKIAPI IYukiGfxControl : public IYukiObject
{
protected:
public:
  IYukiGfxControl()          = default;
  virtual ~IYukiGfxControl() = default;

  virtual SharedPtr<IYukiShaderProgram> GetGfxPipeline() = 0;
};

class YUKIAPI YukiGfxControl : public IYukiGfxControl
{
protected:
  SharedPtr<IYukiThread>        m_pVkInitThread;
  SharedPtr<IYukiThread>        m_pVkDestroyThread;
  SharedPtr<IYukiShaderProgram> m_pGfxPipeline;

public:
  YukiGfxControl();
  virtual ~YukiGfxControl() = default;
  SharedPtr<IYukiShaderProgram> GetGfxPipeline() override;

  void Create() override;
  void Awake() override;
  void Update() override;
  void Render() override;
  void Destroy() override;

  static SharedPtr<IYukiGfxControl> CreateYukiGfxController();
};


class YUKIAPI IYukiShaderProgram : public IYukiObject
{
public:
  IYukiShaderProgram()          = default;
  virtual ~IYukiShaderProgram() = default;
};

class YUKIAPI YukiShaderProgram : public IYukiShaderProgram
{
protected:
  String m_strVSFilePath;
  String m_strFSFilePath;

public:
  YukiShaderProgram(const String& vspath, const String& fspath);
  virtual ~YukiShaderProgram() = default;

  static SharedPtr<IYukiShaderProgram> CreateYukiGfxPipeline(const String& vspath, const String& fspath);
};

} // namespace Yuki::Core