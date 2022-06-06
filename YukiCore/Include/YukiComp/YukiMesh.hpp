/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiObject.hpp"
#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Comp
{

using Core::IYukiOGLTexture;
using Core::IYukiOGLElementBuffer;
using Core::IYukiOGLVertexBuffer;
using Core::IYukiOGLShaderProgram;
using Core::IYukiOGLVertexArray;
using Core::PrimitiveTopology;

typedef struct StVertexFormat
{
  Vec3F position;
  Vec3F normal;
  Vec2F texcoord;

  StVertexFormat(const Vec3F& _position, const Vec3F& _normal, const Vec2F& _texcoord)
      : position(_position), normal(_normal), texcoord(_texcoord)
  {}

  StVertexFormat() : position(0, 0, 0), normal(0, 0, 0), texcoord(0, 0) {}

} MeshVertexFormat;

// Index data format
typedef struct StIndexData
{
  PrimitiveTopology topology;
  Vector<unsigned>  data;
} MeshIndexData;

/**
 * Struct that use to destruct the model matrix to separate properties.
 */
typedef struct StTransformationInfo
{
  Vec3F       scale;
  QuaternionF rotation;
  Vec3F       translation;
  Vec3F       skew;
} TransformationInfo;


/**
 * Every mesh need a specific material to be rendered.
 * Maybe plastic, metal, or something else
 * @TODO Material class need to be improved in the future.
 */
class IYukiMeshMaterial
{
public:
  virtual float GetSpecularStrength() = 0;
  virtual float GetAmbientStrength()  = 0;

  virtual void SetSpecularStrength(float strength) = 0;
  virtual void SetAmbientStrength(float strength)  = 0;
};

/**
 * A 3D game often load the models from external 3D modeling programs.
 * Class IYukiMesh is here to store them in a "pretty" structure that will be used by
 * IYukiModel
 * @TODO Mesh class is very simple now, it must be improved much more.
 */
class IYukiMesh : virtual public Core::IYukiObject
{
public:
  virtual SharedPtr<IYukiOGLTexture>       GetMeshTexture() const        = 0;
  virtual SharedPtr<IYukiOGLElementBuffer> GetElementBuffer() const      = 0;
  virtual SharedPtr<IYukiOGLVertexBuffer>  GetVertexBuffer() const       = 0;
  virtual SharedPtr<IYukiOGLShaderProgram> GetShaderProgram() const      = 0;
  virtual SharedPtr<IYukiOGLVertexArray>   GetVertexArray() const        = 0;
  virtual SharedPtr<IYukiMeshMaterial>     GetMaterial() const           = 0;
  virtual const PrimitiveTopology&         GetTopology() const           = 0;
  virtual const String&                    GetName() const               = 0;
  virtual const Mat4F&                     GetMeshMatrix() const         = 0;
  virtual const Vector<MeshVertexFormat>&  GetVertexData() const         = 0;
  virtual const MeshIndexData&             GetIndexData() const          = 0;
  virtual TransformationInfo               GetTransformationInfo() const = 0;

  virtual void SetMaterial(SharedPtr<IYukiMeshMaterial> material)  = 0;
  virtual void SetMeshMatrix(const Mat4F& matrix)                  = 0;
  virtual void SetTranslation(const Vec3F& position)               = 0;
  virtual void SetRotation(const Vec3F& axis, float rotationAngle) = 0;
  virtual void SetScale(const Vec3F& scaleVector)                  = 0;
  virtual void TranslateMesh(const Vec3F& direction)               = 0;
  virtual void RotateMesh(const Vec3F& axis, float rotationAngle)  = 0;
  virtual void ScaleMesh(const Vec3F& scaleVector)                 = 0;

  virtual void RenderMesh(SharedPtr<IYukiCamera> camera) const = 0;
};

/**
 * This function is used to created a new interface instance of a Mesh
 * @param vertexData an array of VertexFormat that stores vertices info of the mesh
 * @param indexData indices data of the mesh
 * @param texture can be NO_TEXTURE
 * @param material a material
 * @param meshName provide a name for it
 * @return an interface instance for the mesh
 */
SharedPtr<IYukiMesh> CreateYukiMesh(Vector<MeshVertexFormat>& vertexData, MeshIndexData& indexData,
    SharedPtr<Core::IYukiOGLTexture> texture, SharedPtr<IYukiMeshMaterial> material, const String& meshName);

/**
 * Thif function is used to create a new material and return it's interface instance
 * @param specular Specular strength
 * @param ambient Ambient strength
 * @return an interface instance of the material
 * @TODO Provide a method to create material from ambient map or specular map in the future.
 */
SharedPtr<IYukiMeshMaterial> CreateMaterial(float specular, float ambient);

// Initialize the default shader for mesh rendering
void InitializeMeshShader();
void InitializeMeshDefaultTextures();

// Destroy the default shader for mesh rendering
void ReleaseMeshShader();
void ReleaseMeshDefaultTextures();

} // namespace Yuki::Comp
