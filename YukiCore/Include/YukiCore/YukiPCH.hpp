#pragma once

// #pragma warning(disable : 4251)
// #pragma warning(disable : 4275)
// #pragma warning(disable : 26812)

// Windows headers
#if defined(_WIN32) || defined(WIN32)
#  define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#endif

// OpenGL header
#include <glad/glad.h>

// Window manager
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
#include <unordered_map>
#include <set>
#include <iosfwd>
#include <filesystem>

#if defined(_WIN32) || defined(WIN32)
#  ifdef YUKICORE_EXPORTS
#    define YUKIAPI __declspec(dllexport)
#  else
#    define YUKIAPI __declspec(dllimport)
#  endif // YUKICORE_EXPORTS
#elif defined(__linux) || defined(_linux_)
#  define YUKIAPI
#endif


#define AutoType auto

namespace Yuki
{

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;

template <typename T>
using Vector = std::vector<T>;

template <typename K, typename V>
using UnorderedMap = std::unordered_map<K, V>;

template <typename K, typename V>
using Map = std::map<K, V>;

using String       = std::string;
using StringStream = std::stringstream;

typedef char           Char, *CharPtr, &CharRef;
typedef const char*    ConstCharPtr;
typedef wchar_t        WChar, *WCharPtr, &WCharRef;
typedef const wchar_t* WConstCharPtr;

} // namespace Yuki
