#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiCore/YukiThread.hpp"

#include <glm/glm.hpp>

namespace Yuki::Core
{

/// <summary>
/// Describe how does the mesh will be rendered.
/// </summary>
enum class PrimitiveTopology
{
  /// <summary>
  /// Vertices 0 and 1 are considered a line. Vertices 2 and 3 are
  /// considered a line. And so on. If the user specifies a non-even
  /// number of vertices, then the extra vertex is ignored.
  /// </summary>
  LINES          = GL_LINES,
  /// <summary>
  /// The adjacent vertices are considered lines. Thus, if you pass
  /// n vertices, you will get n-1 lines. If the user only specifies
  /// 1 vertex, the drawing command is ignored.
  /// </summary>
  LINE_STRIP     = GL_LINE_STRIP,
  /// <summary>
  /// As line strips, except that the first and last vertices are
  /// also used as a line. Thus, you get n lines for n input vertices.
  /// If the user only specifies 1 vertex, the drawing command is ignored.
  /// The line between the first and last vertices happens after all
  /// of the previous lines in the sequence.
  /// </summary>
  LINE_LOOP      = GL_LINE_LOOP,
  /// <summary>
  /// Vertices 0, 1, and 2 form a triangle. Vertices 3, 4, and 5 form
  /// a triangle. And so on.
  /// </summary>
  TRIANGLE_LIST  = GL_TRIANGLES,
  /// <summary>
  /// Every group of 3 adjacent vertices forms a triangle. The face
  /// direction of the strip is determined by the winding of the
  /// first triangle. Each successive triangle will have its effective
  /// face order reversed, so the system compensates for that by testing
  /// it in the opposite way. A vertex stream of n length will generate
  /// n-2 triangles.
  /// </summary>
  TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
  /// <summary>
  /// The first vertex is always held fixed. From there on, every group
  /// of 2 adjacent vertices form a triangle with the first. So with a
  /// vertex stream, you get a list of triangles like so:
  /// (0, 1, 2) (0, 2, 3), (0, 3, 4), etc. A vertex stream of n length
  /// will generate n-2 triangles.
  /// </summary>
  TRIANGLE_FAN   = GL_TRIANGLE_FAN,
  /// <summary>
  /// This will cause OpenGL to interpret each individual vertex in the
  /// stream as a point.
  /// </summary>
  POINT_LIST     = GL_POINTS,
  /// <summary>
  /// Vertices 0-3 form a quad, vertices 4-7 form another, and so on.
  /// The vertex stream must be a number of vertices divisible by 4 to work.
  ///
  /// Have been removed from core OpenGL 3.1 and above (they are only
  /// deprecated in OpenGL 3.0). It is recommended that you not use this
  /// functionality in your programs.
  /// </summary>
  QUAD_LIST      = GL_QUADS,
  /// <summary>
  /// Similar to triangle strips, a quad strip uses adjacent edges to
  /// form the next quad. In the case of quads, the third and fourth
  /// vertices of one quad are used as the edge of the next quad. So
  /// vertices 0-3 are a quad, 2-5 are a quad, and so on. A vertex
  /// stream of n length will generate (n - 2) / 2 quads. As with triangle
  /// strips, the winding order of quads is changed for every other quad.
  ///
  /// Have been removed from core OpenGL 3.1 and above (they are only
  /// deprecated in OpenGL 3.0). It is recommended that you not use this
  /// functionality in your programs.
  /// </summary>
  QUAD_STRIP     = GL_QUAD_STRIP
};

/// <summary>
/// Type of texture
/// </summary>
enum class TextureType
{
  /// <summary>
  /// mages in this texture all are 1-dimensional. They have width,
  /// but no height or depth.
  /// </summary>
  TEXTURE_1D                   = GL_TEXTURE_1D,
  /// <summary>
  /// Images in this texture all are 2-dimensional. They have width
  /// and height, but no depth.
  /// </summary>
  TEXTURE_2D                   = GL_TEXTURE_2D,
  /// <summary>
  /// Images in this texture all are 3-dimensional. They have width,
  /// height, and depth.
  /// </summary>
  TEXTURE_3D                   = GL_TEXTURE_3D,
  /// <summary>
  /// The image in this texture (only one image. No mipmapping) is
  /// 2-dimensional. Texture coordinates used for these textures are
  /// not normalized.
  /// </summary>
  TEXTURE_RECTANGLE            = GL_TEXTURE_RECTANGLE,
  /// <summary>
  /// The image in this texture (only one image. No mipmapping) is
  /// 1-dimensional. The storage for this data comes from a Buffer
  /// Object.
  /// </summary>
  TEXTURE_BUFFER               = GL_TEXTURE_BUFFER,
  /// <summary>
  /// Images in this texture all are 1-dimensional. However, it contains
  /// multiple sets of 1-dimensional images, all within one texture.
  /// The array length is part of the texture's size.
  /// </summary>
  TEXTURE_1D_ARRAY             = GL_TEXTURE_1D_ARRAY,
  /// <summary>
  /// Images in this texture all are 2-dimensional. However, it contains
  /// multiple sets of 2-dimensional images, all within one texture. The
  /// array length is part of the texture's size.
  /// </summary>
  TEXTURE_2D_ARRAY             = GL_TEXTURE_2D_ARRAY,
  /// <summary>
  /// There are exactly 6 distinct sets of 2D images, each image being
  /// of the same size and must be of a square size. These images act
  /// as 6 faces of a cube.
  /// </summary>
  TEXTURE_CUBE_MAP             = GL_TEXTURE_CUBE_MAP,
  /// <summary>
  /// Images in this texture are all cube maps. It contains multiple sets
  /// of cube maps, all within one texture. The array length * 6 (number
  /// of cube faces) is part of the texture size.
  /// </summary>
  TEXTURE_CUBE_MAP_ARRAY       = GL_TEXTURE_CUBE_MAP_ARRAY,
  /// <summary>
  /// The image in this texture (only one image. No mipmapping) is
  /// 2-dimensional. Each pixel in these images contains multiple samples
  /// instead of just one value.
  /// </summary>
  TEXTURE_2D_MULTISAMPLE       = GL_TEXTURE_2D_MULTISAMPLE,
  /// <summary>
  /// Combines 2D array and 2D multisample types. No mipmapping.
  /// </summary>
  TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};

/// <summary>
/// The texture minifying function is used whenever the level-of-detail
/// function used when sampling from the texture determines that the
/// texture should be minified. There are six defined minifying functions.
/// Two of them use either the nearest texture elements or a weighted
/// average of multiple texture elements to compute the texture value.
/// The other four use mipmaps.
/// </summary>
enum class TextureMinFilter
{
  /// <summary>
  /// Returns the value of the texture element that is nearest (in
  /// Manhattan distance) to the specified texture coordinates.
  /// </summary>
  NEAREST                = GL_NEAREST,
  /// <summary>
  /// Returns the weighted average of the texture elements that are
  /// closest to the specified texture coordinates. These can include
  /// items wrapped or repeated from other parts of a texture, depending
  /// on the values of GL_TEXTURE_WRAP_S and GL_TEXTURE_WRAP_T, and on
  /// the exact mapping.
  /// </summary>
  LINEAR                 = GL_LINEAR,
  /// <summary>
  /// Chooses the mipmap that most closely matches the size of the pixel
  /// being textured and uses the GL_NEAREST criterion (the texture
  /// element closest to the specified texture coordinates) to produce a
  /// texture value.
  /// </summary>
  NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
  /// <summary>
  /// Chooses the mipmap that most closely matches the size of the pixel
  /// being textured and uses the GL_LINEAR criterion (a weighted average
  /// of the four texture elements that are closest to the specified
  /// texture coordinates) to produce a texture value.
  /// </summary>
  LINEAR_MIPMAP_NEAREST  = GL_LINEAR_MIPMAP_NEAREST,
  /// <summary>
  /// Chooses the two mipmaps that most closely match the size of the
  /// pixel being textured and uses the GL_NEAREST criterion (the
  /// texture element closest to the specified texture coordinates ) to
  /// produce a texture value from each mipmap. The final texture value
  /// is a weighted average of those two values.
  /// </summary>
  NEAREST_MIPMAP_LINEAR  = GL_NEAREST_MIPMAP_LINEAR,
  /// <summary>
  /// Chooses the two mipmaps that most closely match the size of the
  /// pixel being textured and uses the GL_LINEAR criterion (a weighted
  /// average of the texture elements that are closest to the specified
  /// texture coordinates) to produce a texture value from each mipmap.
  /// The final texture value is a weighted average of those two values.
  /// </summary>
  LINEAR_MIPMAP_LINEAR   = GL_LINEAR_MIPMAP_LINEAR,
};

/// <summary>
/// The texture magnification function is used whenever the
/// level-of-detail function used when sampling from the texture
/// determines that the texture should be magified.
/// </summary>
enum class TextureMagFilter
{
  /// <summary>
  /// Returns the value of the texture element that is nearest (in
  /// Manhattan distance) to the specified texture coordinates.
  /// </summary>
  NEAREST = GL_NEAREST,
  /// <summary>
  /// Returns the weighted average of the texture elements that are
  /// closest to the specified texture coordinates. These can include
  /// items wrapped or repeated from other parts of a texture, depending
  /// on the values of GL_TEXTURE_WRAP_S and GL_TEXTURE_WRAP_T, and on
  /// the exact mapping.
  /// </summary>
  LINEAR  = GL_LINEAR
};

/// <summary>
/// Specifies the mode used to read from
/// depth-stencil format textures.
/// </summary>
enum class TextureDepthStencilMode
{
  /// <summary>
  /// If the depth stencil mode is DEPTH_COMPONENT, then reads
  /// from depth-stencil format textures will return the depth
  /// component of the texel in Rt and the stencil component will
  /// be discarded.
  /// </summary>
  DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
  /// <summary>
  /// If the depth stencil mode is GL_STENCIL_INDEX then the
  /// stencil component is returned in Rt and the depth component
  /// is discarded. The initial value is GL_DEPTH_COMPONENT.
  /// </summary>
  STENCIL_INDEX   = GL_STENCIL_INDEX
};

/// <summary>
/// Specifies the comparison operator used when
/// GL_TEXTURE_COMPARE_MODE is set to
/// GL_COMPARE_REF_TO_TEXTURE
/// </summary>
enum class TextureCompareFunc
{
  LEQUAL   = GL_LEQUAL,
  GEQUAL   = GL_GEQUAL,
  LESS     = GL_LESS,
  GREATER  = GL_GREATER,
  EQUAL    = GL_EQUAL,
  NOTEQUAL = GL_NOTEQUAL,
  ALWAYS   = GL_ALWAYS,
  NEVER    = GL_NEVER
};

/// <summary>
/// Specifies the texture comparison mode for currently
/// bound depth textures.
/// </summary>
enum class TextureCompareMode
{
  COMPARE_REF_TO_TEXTURE = GL_COMPARE_REF_TO_TEXTURE,
  NONE                   = GL_NONE
};

/// <summary>
/// Sized Internal Formats
/// </summary>
enum class TextureInternalFormat
{
  R8             = GL_R8,
  R8_SNORM       = GL_R8_SNORM,
  R16            = GL_R16,
  R16_SNORM      = GL_R16_SNORM,
  RG8            = GL_RG8,
  RG8_SNORM      = GL_RG8_SNORM,
  RG16           = GL_RG16,
  RG16_SNORM     = GL_RG16_SNORM,
  R3_G3_B2       = GL_R3_G3_B2,
  RGB4           = GL_RGB4,
  RGB5           = GL_RGB5,
  RGB8           = GL_RGB8,
  RGB8_SNORM     = GL_RGB8_SNORM,
  RGB10          = GL_RGB10,
  RGB12          = GL_RGB12,
  RGB16_SNORM    = GL_RGB16_SNORM,
  RGBA2          = GL_RGBA2,
  RGBA4          = GL_RGBA4,
  RGB5_A1        = GL_RGB5_A1,
  RGBA8          = GL_RGBA8,
  RGBA8_SNORM    = GL_RGBA8_SNORM,
  RGB10_A2       = GL_RGB10_A2,
  RGB10_A2UI     = GL_RGB10_A2UI,
  RGBA12         = GL_RGBA12,
  RGBA16         = GL_RGBA16,
  SRGB8          = GL_SRGB8,
  SRGB8_ALPHA8   = GL_SRGB8_ALPHA8,
  R16F           = GL_R16F,
  RG16F          = GL_RG16F,
  RGB16F         = GL_RGB16F,
  RGBA16F        = GL_RGBA16F,
  R32F           = GL_R32F,
  RG32F          = GL_RG32F,
  RGB32F         = GL_RGB32F,
  RGBA32F        = GL_RGBA32F,
  R11F_G11F_B10F = GL_R11F_G11F_B10F,
  RGB9_E5        = GL_RGB9_E5,
  R8I            = GL_R8I,
  R8UI           = GL_R8UI,
  R16I           = GL_R16I,
  R16UI          = GL_R16UI,
  R32I           = GL_R32I,
  R32UI          = GL_R32UI,
  RG8I           = GL_RG8I,
  RG8UI          = GL_RG8UI,
  RG16I          = GL_RG16I,
  RG16UI         = GL_RG16UI,
  RG32I          = GL_RG32I,
  RG32UI         = GL_RG32UI,
  RGB8I          = GL_RGB8I,
  RGB8UI         = GL_RGB8UI,
  RGB16I         = GL_RGB16I,
  RGB16UI        = GL_RGB16UI,
  RGB32I         = GL_RGB32I,
  RGB32UI        = GL_RGB32UI,
  RGBA8I         = GL_RGBA8I,
  RGBA8UI        = GL_RGBA8UI,
  RGBA16I        = GL_RGBA16I,
  RGBA16UI       = GL_RGBA16UI,
  RGBA32I        = GL_RGBA32I,
};

/// <summary>
/// Flag of each vertices. Use | to combine them. [Count Right-to-left]
/// <para> - Bit 0: Enable texture </para>
/// <para> - Bit 1: Enable texture </para>
/// <para> - Bit 2 - 7: Reserve </para>
/// </summary>
enum class VertexFlag
{
  /// <summary>
  /// Allow shader to use texture coordinate value.
  /// </summary>
  ENABLE_TEXTURE   = 1,
  /// <summary>
  /// Allow shader to calculate lightning of vertex.
  /// </summary>
  ENABLE_LIGHTNING = 2,
};

/// <summary>
/// Format of a vertex to passed into VBO
/// </summary>
typedef struct StVertexFormat
{
  glm::vec3 position;
  glm::vec4 color;
  glm::vec2 texcoord;
  unsigned  texID;

  StVertexFormat(
      const glm::vec3& _position,
      const glm::vec4& _color,
      const glm::vec2& _texcoord,
      const unsigned&  _texID)
      : position(_position), color(_color), texcoord(_texcoord), texID(_texID) {}

} VertexData, VertexFormat;

/// <summary>
/// Index data format
/// </summary>
typedef struct StIndexData
{
  PrimitiveTopology      topology;
  std::vector<unsigned>& data;
} IndexData, IndexFormat;

/// <summary>
/// This object is only used once in Application. This is the class
/// controls every graphics actions.
/// </summary>
class YUKIAPI IYukiGfxControl : public IYukiObject
{
public:
};

/// <summary>
/// OpenGL Object abstraction.
/// </summary>
class YUKIAPI IYukiOGLObject : public IYukiObject
{
public:
  virtual const unsigned& GetID()      = 0;
  virtual void            BindObject() = 0;
};

/// <summary>
/// Vertex Buffer Object abstraction.
/// </summary>
class YUKIAPI IYukiOGLVertexBuffer : public IYukiOGLObject
{
public:
  virtual void SetBufferData(std::vector<float>& data)  = 0;
  virtual void SetBufferData(float* pData, size_t size) = 0;
};

/// <summary>
/// Element Buffer Object abstraction.
/// </summary>
class YUKIAPI IYukiOGLElementBuffer : public IYukiOGLObject
{
public:
  virtual void SetBufferData(std::vector<unsigned>& data)  = 0;
  virtual void SetBufferData(unsigned* pData, size_t size) = 0;
  virtual void DrawElements(
      Core::PrimitiveTopology topology, const unsigned& start, const unsigned& count) = 0;
  virtual void DrawAllElements(
      Core::PrimitiveTopology topology) = 0;
};

/// <summary>
/// Vertex Array Object abstraction.
/// </summary>
class YUKIAPI IYukiOGLVertexArray : public IYukiOGLObject
{
public:
  virtual void EnableAttribute(const unsigned& attrib)                           = 0;
  virtual void AttributeBinding(const unsigned& attrib, const unsigned& binding) = 0;
  virtual void SetAttributeFormat(
      const unsigned& attrib, const unsigned& size, const size_t& offset, const bool& normalized = false) = 0;
  virtual void SetVertexBuffer(
      const SharedPtr<IYukiOGLVertexBuffer>& buffer, int bindIndex, size_t offset, size_t stride) = 0;
};

/// <summary>
/// Shader Program abstraction.
/// </summary>
class YUKIAPI IYukiOGLShaderProgram : public IYukiOGLObject
{
public:
  virtual void UniformMatrix(const AsciiString& prop, const glm::mat2& mat, bool transopse = false) = 0;
  virtual void UniformMatrix(const AsciiString& prop, const glm::mat3& mat, bool transopse = false) = 0;
  virtual void UniformMatrix(const AsciiString& prop, const glm::mat4& mat, bool transopse = false) = 0;

  virtual void UniformVector(const AsciiString& prop, const glm::vec2& vec) = 0;
  virtual void UniformVector(const AsciiString& prop, const glm::vec3& vec) = 0;
  virtual void UniformVector(const AsciiString& prop, const glm::vec4& vec) = 0;

  virtual void UniformValue(const AsciiString& prop, const bool& value)  = 0;
  virtual void UniformValue(const AsciiString& prop, const int& value)   = 0;
  virtual void UniformValue(const AsciiString& prop, const float& value) = 0;
};

/// <summary>
/// OpenGL Texture abstraction.
/// </summary>
class YUKIAPI IYukiOGLTexture : public IYukiOGLObject
{
public:
  virtual void SetTextureMinFilter(const TextureMinFilter& minFilter)          = 0;
  virtual void SetTextureMagFilter(const TextureMagFilter& magFilter)          = 0;
  virtual void SetDepthStencilTextureMode(const TextureDepthStencilMode& mode) = 0;
  virtual void SetTextureBaseLevel(const int& baseLevel)                       = 0;
  virtual void SetTextureCompareFunc(const TextureCompareFunc& compareFunc)    = 0;
  virtual void SetTextureCompareMode(const TextureCompareMode& compareMode)    = 0;
  virtual void SetTextureLodBias(const float& bias)                            = 0;

  virtual const TextureType             GetTextureType()             = 0;
  virtual const TextureMinFilter        GetTextureMinFilter()        = 0;
  virtual const TextureMagFilter        GetTextureMagFilter()        = 0;
  virtual const TextureDepthStencilMode GetDepthStencilTextureMode() = 0;
  virtual const int                     GetTextureBaseLevel()        = 0;
  virtual const TextureCompareFunc      GetTextureCompareFunc()      = 0;
  virtual const TextureCompareMode      GetTextureCompareMode()      = 0;
  virtual const float                   GetTextureLodBias()          = 0;

  virtual void GenerateMipMap()                  = 0;
  virtual void BindTexture(const unsigned& slot) = 0;
};

SharedPtr<IYukiGfxControl> YUKIAPI       CreateGraphicsController();
SharedPtr<IYukiOGLVertexBuffer> YUKIAPI  CreateGLVertexBuffer();
SharedPtr<IYukiOGLElementBuffer> YUKIAPI CreateGLElementBuffer();
SharedPtr<IYukiOGLShaderProgram> YUKIAPI CreateGLShaderProgram(const String& shaderName);
SharedPtr<IYukiOGLVertexArray> YUKIAPI   CreateGLVertexArray();
SharedPtr<IYukiOGLTexture> YUKIAPI       CreateGLTexture(const TextureType& type);

} // namespace Yuki::Core
