#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiLogger.hpp"
#include "YukiCore/YukiThread.hpp"

namespace Yuki::Core
{

class YUKIAPI IYukiOGLObject : public IYukiObject, public IYukiProtectedObject
{
public:
  IYukiOGLObject()          = default;
  virtual ~IYukiOGLObject() = default;

  virtual void GetID()      = 0;
  virtual void BindObject() = 0;
};

class YUKIAPI IYukiOGLVertexBuffer : public IYukiOGLObject
{
public:
};

} // namespace Yuki::Core
