/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiObject.hpp"
#include "YukiDebug/YukiLogger.hpp"

#include <glm/glm.hpp>

namespace Yuki::Core
{

// Describe how does the mesh will be rendered.
enum class PrimitiveTopology
{
  // Vertices 0 and 1 are considered a line. Vertices 2 and 3 are
  // considered a line. And so on. If the user specifies a non-even
  // number of vertices, then the extra vertex is ignored.
  LINES          = GL_LINES,
  // The adjacent vertices are considered lines. Thus, if you pass
  // n vertices, you will get n-1 lines. If the user only specifies
  // 1 vertex, the drawing command is ignored.
  LINE_STRIP     = GL_LINE_STRIP,
  // As line strips, except that the first and last vertices are
  // also used as a line. Thus, you get n lines for n input vertices.
  // If the user only specifies 1 vertex, the drawing command is ignored.
  // The line between the first and last vertices happens after all
  // of the previous lines in the sequence.
  LINE_LOOP      = GL_LINE_LOOP,
  // Vertices 0, 1, and 2 form a triangle. Vertices 3, 4, and 5 form
  // a triangle. And so on.
  TRIANGLE_LIST  = GL_TRIANGLES,
  // Every group of 3 adjacent vertices forms a triangle. The face
  // direction of the strip is determined by the winding of the
  // first triangle. Each successive triangle will have its effective
  // face order reversed, so the system compensates for that by testing
  // it in the opposite way. A vertex stream of n length will generate
  // n-2 triangles.
  TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
  // The first vertex is always held fixed. From there on, every group
  // of 2 adjacent vertices form a triangle with the first. So with a
  // vertex stream, you get a list of triangles like so:
  // (0, 1, 2) (0, 2, 3), (0, 3, 4), etc. A vertex stream of n length
  // will generate n-2 triangles.
  TRIANGLE_FAN   = GL_TRIANGLE_FAN,
  // This will cause OpenGL to interpret each individual vertex in the
  // stream as a point.
  POINT_LIST     = GL_POINTS,
  // Vertices 0-3 form a quad, vertices 4-7 form another, and so on.
  // The vertex stream must be a number of vertices divisible by 4 to work.
  //
  // Have been removed from core OpenGL 3.1 and above (they are only
  // deprecated in OpenGL 3.0). It is recommended that you not use this
  // functionality in your programs.
  QUAD_LIST      = GL_QUADS,
  // Similar to triangle strips, a quad strip uses adjacent edges to
  // form the next quad. In the case of quads, the third and fourth
  // vertices of one quad are used as the edge of the next quad. So
  // vertices 0-3 are a quad, 2-5 are a quad, and so on. A vertex
  // stream of n length will generate (n - 2) / 2 quads. As with triangle
  // strips, the winding order of quads is changed for every other quad.
  // Have been removed from core OpenGL 3.1 and above (they are only
  // deprecated in OpenGL 3.0). It is recommended that you not use this
  // functionality in your programs.
  QUAD_STRIP     = GL_QUAD_STRIP
};

// Type of texture
enum class TextureType
{
  // mages in this texture all are 1-dimensional. They have width,
  // but no height or depth.
  TEXTURE_1D                   = GL_TEXTURE_1D,
  // Images in this texture all are 2-dimensional. They have width
  // and height, but no depth.
  TEXTURE_2D                   = GL_TEXTURE_2D,
  // Images in this texture all are 3-dimensional. They have width,
  // height, and depth.
  TEXTURE_3D                   = GL_TEXTURE_3D,
  // The image in this texture (only one image. No mipmapping) is
  // 2-dimensional. Texture coordinates used for these textures are
  // not normalized.
  TEXTURE_RECTANGLE            = GL_TEXTURE_RECTANGLE,
  // The image in this texture (only one image. No mipmapping) is
  // 1-dimensional. The storage for this data comes from a Buffer
  // Object.
  TEXTURE_BUFFER               = GL_TEXTURE_BUFFER,
  // Images in this texture all are 1-dimensional. However, it contains
  // multiple sets of 1-dimensional images, all within one texture.
  // The array length is part of the texture's size.
  TEXTURE_1D_ARRAY             = GL_TEXTURE_1D_ARRAY,
  // Images in this texture all are 2-dimensional. However, it contains
  // multiple sets of 2-dimensional images, all within one texture. The
  // array length is part of the texture's size.
  TEXTURE_2D_ARRAY             = GL_TEXTURE_2D_ARRAY,
  // There are exactly 6 distinct sets of 2D images, each image being
  // of the same size and must be of a square size. These images act
  // as 6 faces of a cube.
  TEXTURE_CUBE_MAP             = GL_TEXTURE_CUBE_MAP,
  // Images in this texture are all cube maps. It contains multiple sets
  // of cube maps, all within one texture. The array length * 6 (number
  // of cube faces) is part of the texture size.
  TEXTURE_CUBE_MAP_ARRAY       = GL_TEXTURE_CUBE_MAP_ARRAY,
  // The image in this texture (only one image. No mipmapping) is
  // 2-dimensional. Each pixel in these images contains multiple samples
  // instead of just one value.
  TEXTURE_2D_MULTISAMPLE       = GL_TEXTURE_2D_MULTISAMPLE,
  // Combines 2D array and 2D multisample types. No mipmapping.
  TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};

// The texture minifying function is used whenever the level-of-detail
// function used when sampling from the texture determines that the
// texture should be minified. There are six defined minifying functions.
// Two of them use either the nearest texture elements or a weighted
// average of multiple texture elements to compute the texture value.
// The other four use mipmaps.
enum class TextureMinFilter
{
  // Returns the value of the texture element that is nearest (in
  // Manhattan distance) to the specified texture coordinates.
  NEAREST                = GL_NEAREST,
  // Returns the weighted average of the texture elements that are
  // closest to the specified texture coordinates. These can include
  // items wrapped or repeated from other parts of a texture, depending
  // on the values of GL_TEXTURE_WRAP_S and GL_TEXTURE_WRAP_T, and on
  // the exact mapping.
  LINEAR                 = GL_LINEAR,
  // Chooses the mipmap that most closely matches the size of the pixel
  // being textured and uses the GL_NEAREST criterion (the texture
  // element closest to the specified texture coordinates) to produce a
  // texture value.
  NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
  // Chooses the mipmap that most closely matches the size of the pixel
  // being textured and uses the GL_LINEAR criterion (a weighted average
  // of the four texture elements that are closest to the specified
  // texture coordinates) to produce a texture value.
  LINEAR_MIPMAP_NEAREST  = GL_LINEAR_MIPMAP_NEAREST,
  // Chooses the two mipmaps that most closely match the size of the
  // pixel being textured and uses the GL_NEAREST criterion (the
  // texture element closest to the specified texture coordinates ) to
  // produce a texture value from each mipmap. The final texture value
  // is a weighted average of those two values.
  NEAREST_MIPMAP_LINEAR  = GL_NEAREST_MIPMAP_LINEAR,
  // Chooses the two mipmaps that most closely match the size of the
  // pixel being textured and uses the GL_LINEAR criterion (a weighted
  // average of the texture elements that are closest to the specified
  // texture coordinates) to produce a texture value from each mipmap.
  // The final texture value is a weighted average of those two values.
  LINEAR_MIPMAP_LINEAR   = GL_LINEAR_MIPMAP_LINEAR,
};

// The texture magnification function is used whenever the
// level-of-detail function used when sampling from the texture
// determines that the texture should be magified.
enum class TextureMagFilter
{
  // Returns the value of the texture element that is nearest (in
  // Manhattan distance) to the specified texture coordinates.
  NEAREST = GL_NEAREST,
  // Returns the weighted average of the texture elements that are
  // closest to the specified texture coordinates. These can include
  // items wrapped or repeated from other parts of a texture, depending
  // on the values of GL_TEXTURE_WRAP_S and GL_TEXTURE_WRAP_T, and on
  // the exact mapping.
  LINEAR  = GL_LINEAR
};

// Specifies the mode used to read from
// depth-stencil format textures.
enum class TextureDepthStencilMode
{
  // If the depth stencil mode is DEPTH_COMPONENT, then reads
  // from depth-stencil format textures will return the depth
  // component of the texel in Rt and the stencil component will
  // be discarded.
  DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
  // If the depth stencil mode is GL_STENCIL_INDEX then the
  // stencil component is returned in Rt and the depth component
  // is discarded. The initial value is GL_DEPTH_COMPONENT.
  STENCIL_INDEX   = GL_STENCIL_INDEX
};

// Specifies the comparison operator used when
// GL_TEXTURE_COMPARE_MODE is set to
// GL_COMPARE_REF_TO_TEXTURE
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

// Specifies the texture comparison mode for currently
// bound depth textures.
enum class TextureCompareMode
{
  COMPARE_REF_TO_TEXTURE = GL_COMPARE_REF_TO_TEXTURE,
  NONE                   = GL_NONE
};

enum class PixelCompressedInternalFormat
{
  COMPRESSED_RED                     = GL_COMPRESSED_RED,
  COMPRESSED_RG                      = GL_COMPRESSED_RG,
  COMPRESSED_RGB                     = GL_COMPRESSED_RGB,
  COMPRESSED_RGBA                    = GL_COMPRESSED_RGBA,
  COMPRESSED_SRGB                    = GL_COMPRESSED_SRGB,
  COMPRESSED_SRGB_ALPHA              = GL_COMPRESSED_SRGB_ALPHA,
  COMPRESSED_RED_RGTC1               = GL_COMPRESSED_RED_RGTC1,
  COMPRESSED_SIGNED_RED_RGTC1        = GL_COMPRESSED_SIGNED_RED_RGTC1,
  COMPRESSED_RG_RGTC2                = GL_COMPRESSED_RG_RGTC2,
  COMPRESSED_SIGNED_RG_RGTC2         = GL_COMPRESSED_SIGNED_RG_RGTC2,
  COMPRESSED_RGBA_BPTC_UNORM         = GL_COMPRESSED_RGBA_BPTC_UNORM,
  COMPRESSED_SRGB_ALPHA_BPTC_UNORM   = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
  COMPRESSED_RGB_BPTC_SIGNED_FLOAT   = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
  COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,
};

// Sized Internal Formats
enum class PixelInternalFormat
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

// Pixel format
enum class PixelBasedInternalFormat
{
  RED             = GL_RED,
  RG              = GL_RG,
  RGB             = GL_RGB,
  BGR             = GL_BGR,
  RGBA            = GL_RGBA,
  DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
  STENCIL_INDEX   = GL_STENCIL_INDEX
};

// Format of a vertex to passed into VBO
typedef struct StVertexFormat
{
  Vec3F position;
  Vec3F normal;
  Vec2F texcoord;

  StVertexFormat(
      const Vec3F& _position,
      const Vec3F& _normal,
      const Vec2F& _texcoord)
      : position(_position), normal(_normal), texcoord(_texcoord) {}

  StVertexFormat()
      : position(0, 0, 0), normal(0, 0, 0), texcoord(0, 0) {}

} VertexData, VertexFormat;

// Index data format
typedef struct StIndexData
{
  PrimitiveTopology topology;
  Vector<unsigned>  data;
} IndexData, IndexFormat;

// This object is only used once in Application. This is the class
// controls every graphics actions.
class IYukiGfxControl : virtual public IYukiObject
{
public:
};

// OpenGL Object:
// OpenGL Object abstraction.
class IYukiOGLObject : virtual public IYukiObject
{
public:
  virtual unsigned GetID()      = 0;
  virtual void     BindObject() = 0;
};

// OpenGL Object:
// Vertex Buffer Object abstraction.
class IYukiOGLVertexBuffer : virtual public IYukiOGLObject
{
public:
  virtual void SetBufferData(Vector<float>& data)       = 0;
  virtual void SetBufferData(float* pData, size_t size) = 0;
};

// OpenGL Object:
// Element Buffer Object abstraction.
class IYukiOGLElementBuffer : virtual public IYukiOGLObject
{
public:
  virtual void SetBufferData(Vector<unsigned>& data)                                    = 0;
  virtual void SetBufferData(unsigned* pData, size_t size)                              = 0;
  virtual void DrawElements(PrimitiveTopology topology, unsigned start, unsigned count) = 0;
  virtual void DrawAllElements(PrimitiveTopology topology)                              = 0;
};

// OpenGL Object:
// Shader Program abstraction.
class IYukiOGLShaderProgram : virtual public IYukiOGLObject
{
public:
  virtual void UniformMatrix(const String& prop, const Mat2F& mat, bool transopse = false) = 0;
  virtual void UniformMatrix(const String& prop, const Mat3F& mat, bool transopse = false) = 0;
  virtual void UniformMatrix(const String& prop, const Mat4F& mat, bool transopse = false) = 0;

  virtual void UniformVector(const String& prop, const Vec2F& vec) = 0;
  virtual void UniformVector(const String& prop, const Vec3F& vec) = 0;
  virtual void UniformVector(const String& prop, const Vec4F& vec) = 0;

  virtual void UniformValue(const String& prop, bool value)  = 0;
  virtual void UniformValue(const String& prop, int value)   = 0;
  virtual void UniformValue(const String& prop, float value) = 0;
};

// OpenGL Object:
// OpenGL Texture abstraction.
class IYukiOGLTexture : virtual public IYukiOGLObject
{
public:
  virtual void SetTextureMinFilter(TextureMinFilter minFilter)          = 0;
  virtual void SetTextureMagFilter(TextureMagFilter magFilter)          = 0;
  virtual void SetDepthStencilTextureMode(TextureDepthStencilMode mode) = 0;
  virtual void SetTextureBaseLevel(int baseLevel)                       = 0;
  virtual void SetTextureCompareFunc(TextureCompareFunc compareFunc)    = 0;
  virtual void SetTextureCompareMode(TextureCompareMode compareMode)    = 0;
  virtual void SetTextureLodBias(float bias)                            = 0;

  virtual void SetStorageData1D(PixelInternalFormat internalFormat, int level, const Vec1I& size) = 0;
  virtual void SetStorageData2D(PixelInternalFormat internalFormat, int level, const Vec2F& size) = 0;
  virtual void SetStorageData3D(PixelInternalFormat internalFormat, int level, const Vec3F& size) = 0;

  virtual void SetStorageData1D(PixelBasedInternalFormat internalFormat, int level, const Vec1I& size) = 0;
  virtual void SetStorageData2D(PixelBasedInternalFormat internalFormat, int level, const Vec2F& size) = 0;
  virtual void SetStorageData3D(PixelBasedInternalFormat internalFormat, int level, const Vec3F& size) = 0;

  virtual void SetTextureData1D(uint8_t* pixels, int level, PixelBasedInternalFormat imageFormat, const Vec1I& offset, const Vec1I& len)  = 0;
  virtual void SetTextureData2D(uint8_t* pixels, int level, PixelBasedInternalFormat imageFormat, const Vec2I& offset, const Vec2I& size) = 0;
  virtual void SetTextureData3D(uint8_t* pixels, int level, PixelBasedInternalFormat imageFormat, const Vec3I& offset, const Vec3I& size) = 0;

  virtual const TextureType             GetTextureType()             = 0;
  virtual const TextureMinFilter        GetTextureMinFilter()        = 0;
  virtual const TextureMagFilter        GetTextureMagFilter()        = 0;
  virtual const TextureDepthStencilMode GetDepthStencilTextureMode() = 0;
  virtual const int                     GetTextureBaseLevel()        = 0;
  virtual const TextureCompareFunc      GetTextureCompareFunc()      = 0;
  virtual const TextureCompareMode      GetTextureCompareMode()      = 0;
  virtual const float                   GetTextureLodBias()          = 0;

  virtual void GenerateMipMap()           = 0;
  virtual void BindTexture(unsigned slot) = 0;
};

// OpenGL Object:
// Render Buffer abstraction
class IYukiOGLRenderBuffer : virtual public IYukiOGLObject
{
public:
  virtual void SetBufferStorage(PixelInternalFormat internalFormat, const Vec2I& size)                          = 0;
  virtual void SetBufferStorageMultiSamples(PixelInternalFormat internalFormat, const Vec2I& size, int samples) = 0;
};

// OpenGL Container:
// Vertex Array Object abstraction.
class IYukiOGLVertexArray : virtual public IYukiOGLObject
{
public:
  virtual void EnableAttribute(unsigned attrib)                                                                     = 0;
  virtual void AttributeBinding(unsigned attrib, unsigned binding)                                                  = 0;
  virtual void SetAttributeFormat(unsigned size, unsigned attrib, size_t offset, bool normalized = false)           = 0;
  virtual void SetVertexBuffer(SharedPtr<IYukiOGLVertexBuffer> buffer, int bindIndex, size_t offset, size_t stride) = 0;
  virtual void SetElementBuffer(SharedPtr<IYukiOGLElementBuffer> buffer)                                            = 0;
};

// OpenGL Container
// Frame Buffer Object abstraction
class IYukiOGLFrameBuffer : virtual public IYukiOGLObject
{
public:
  virtual bool BufferOK() = 0;

  virtual void AttachTextureColor(SharedPtr<IYukiOGLTexture> tex, unsigned position = 0, unsigned level = 0) = 0;
  virtual void AttachTextureDepth(SharedPtr<IYukiOGLTexture> tex, unsigned level = 0)                        = 0;
  virtual void AttachTextureStencil(SharedPtr<IYukiOGLTexture> tex, unsigned level = 0)                      = 0;
  virtual void AttachTextureDepthStencil(SharedPtr<IYukiOGLTexture> tex, unsigned level = 0)                 = 0;

  virtual void AttachRenderBufferColor(SharedPtr<IYukiOGLRenderBuffer> rbo, unsigned position = 0) = 0;
  virtual void AttachRenderBufferDepth(SharedPtr<IYukiOGLRenderBuffer> rbo)                        = 0;
  virtual void AttachRenderBufferStencil(SharedPtr<IYukiOGLRenderBuffer> rbo)                      = 0;
  virtual void AttachRenderBufferDepthStencil(SharedPtr<IYukiOGLRenderBuffer> rbo)                 = 0;
};

SharedPtr<IYukiGfxControl>       CreateGraphicsController();
SharedPtr<IYukiOGLVertexBuffer>  CreateGLVertexBuffer();
SharedPtr<IYukiOGLElementBuffer> CreateGLElementBuffer();
SharedPtr<IYukiOGLShaderProgram> CreateGLShaderProgram(const String& shaderName);
SharedPtr<IYukiOGLVertexArray>   CreateGLVertexArray();
SharedPtr<IYukiOGLTexture>       CreateGLTexture(TextureType type);
SharedPtr<IYukiOGLRenderBuffer>  CreateRegnderBuffer();
SharedPtr<IYukiOGLFrameBuffer>   CreateFrameBuffer();

} // namespace Yuki::Core
