/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

// #pragma warning(disable : 4251)
// #pragma warning(disable : 4275)
// #pragma warning(disable : 26812)

// Windows headers
#include <deque>
#if defined(_WIN32) || defined(WIN32)
#  define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#  include <Pdh.h>
#  include <Psapi.h>
#elif defined(linux) || defined(__linux) || defined(__linux__)
#  include <sys/types.h>
#  include <sys/sysinfo.h>
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
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <iosfwd>
#include <filesystem>
#include <atomic>

// glm types
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x4.hpp>
#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat3x4.hpp>
#include <glm/mat4x2.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>

#if defined(_WIN32) || defined(WIN32)
#  ifdef YUKICORE_EXPORTS
#    define YUKIAPI __declspec(dllexport)
#  else
#    define YUKIAPI __declspec(dllimport)
#  endif // YUKICORE_EXPORTS
#elif defined(__linux) || defined(_linux_)
#  define YUKIAPI
#endif


#define AutoType       auto
#define YUKI_NODISCARD [[nodiscard]]

namespace Yuki
{

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;

template <typename T>
using Vector = std::vector<T, std::allocator<T>>;

template <typename T>
using Queue = std::queue<T, std::deque<T>>;

template <typename T>
using Stack = std::stack<T, std::deque<T>>;

template <typename K, typename V>
using UnorderedMap = std::unordered_map<K, V>;

template <typename K, typename V>
using Map = std::map<K, V>;

template <typename T>
using UnorderedSet = std::unordered_set<T>;

template <typename T>
using Set = std::set<T>;

template <typename T, int SIZE>
using Array = std::array<T, SIZE>;

template <typename T>
using Atomic = std::atomic<T>;

template <typename T>
using Function = std::function<T>;

using String       = std::string;
using StringStream = std::stringstream;

using FileStream       = std::fstream;
using InputFileStream  = std::ifstream;
using OutputFileStream = std::ofstream;

typedef char           Char, *CharPtr, &CharRef;
typedef const char*    ConstCharPtr;
typedef wchar_t        WChar, *WCharPtr, &WCharRef;
typedef const wchar_t* WConstCharPtr;

typedef Function<void()> VoidNParamFunc, VoidNParamCallback;

typedef glm::vec1    Vec1F;
typedef glm::vec2    Vec2F;
typedef glm::vec3    Vec3F;
typedef glm::vec4    Vec4F;
typedef glm::mat2x2  Mat2x2F, Mat2F;
typedef glm::mat2x3  Mat2x3F;
typedef glm::mat2x4  Mat2x4F;
typedef glm::mat3x2  Mat3x2F;
typedef glm::mat3x3  Mat3x3F, Mat3F;
typedef glm::mat3x4  Mat3x4F;
typedef glm::mat4x2  Mat4x2F;
typedef glm::mat4x3  Mat4x3F;
typedef glm::mat4x4  Mat4x4F, Mat4F;
typedef glm::ivec1   Vec1I;
typedef glm::ivec2   Vec2I;
typedef glm::ivec3   Vec3I;
typedef glm::ivec4   Vec4I;
typedef glm::imat2x2 Mat2x2I, Mat2I;
typedef glm::imat2x3 Mat2x3I;
typedef glm::imat2x4 Mat2x4I;
typedef glm::imat3x2 Mat3x2I, Mat3I;
typedef glm::imat3x3 Mat3x3I;
typedef glm::imat3x4 Mat3x4I;
typedef glm::imat4x2 Mat4x2I, Mat4I;
typedef glm::imat4x3 Mat4x3I;
typedef glm::imat4x4 Mat4x4I;
typedef glm::umat2x2 Mat2x2UI, Mat2UI;
typedef glm::umat2x3 Mat2x3UI;
typedef glm::umat2x4 Mat2x4UI;
typedef glm::umat3x2 Mat3x2UI, Mat3UI;
typedef glm::umat3x3 Mat3x3UI;
typedef glm::umat3x4 Mat3x4UI;
typedef glm::umat4x2 Mat4x2UI, Mat4UI;
typedef glm::umat4x3 Mat4x3UI;
typedef glm::umat4x4 Mat4x4UI;
typedef glm::quat    QuaternionF;

} // namespace Yuki
