#pragma once

#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#pragma warning(disable : 26812)

// Windows headers
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// Window manager
#define VK_USE_PLATFORM_WIN32_KHR // Specific Win32 KHR platform
#define GLFW_INCLUDE_VULKAN       // Make GLFW compatible with vulkan
#define GLFW_EXPOSE_NATIVE_WIN32  // Use GLFW native Win32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// C++ standards
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <sstream>
#include <memory>
#include <string>
#include <stdexcept>
#include <functional>
#include <vector>
#include <map>
#include <set>
#include <iosfwd>

#ifdef YUKICORE_EXPORTS
#  define YUKIAPI __declspec(dllexport)
#else
#  define YUKIAPI __declspec(dllimport)
#endif // YUKICORE_EXPORTS

#define AutoType auto

namespace Yuki
{

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;

using String            = std::wstring;
using StringStream      = std::wstringstream;
using AsciiString       = std::string;
using AsciiStringStream = std::stringstream;

typedef char           AsciiChar, *AsciiCharPtr, &AsciiCharRef;
typedef const char*    ConstAsciiCharPtr;
typedef wchar_t        WChar, *WCharPtr, &WCharRef;
typedef const wchar_t* WConstCharPtr;

} // namespace Yuki
