/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiObject.hpp"

// std
#include <thread>

namespace Yuki::Core
{

using CallbackFuncType = std::function<void()>;
using Thread           = std::thread;
using ThreadID         = std::thread::id;

class YUKIAPI IYukiThreadPool
{
public:
  virtual void Start()                                    = 0;
  virtual void Join()                                     = 0;
  virtual void PushAction(const CallbackFuncType& action) = 0;
  virtual void Terminate()                                = 0;
};

unsigned YUKIAPI                   GetHardwareConcurrency();
SharedPtr<IYukiThreadPool> YUKIAPI CreateThreadPool(int poolSize = -1, long long invokeInterval = 30);

} // namespace Yuki::Core
