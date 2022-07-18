#version 460 core

#define MAX_SHADER 128

struct PointLightData
{
  vec3  color;
  vec3  position;
  float intensity;
};

in vec3 VS_FragPos;
in vec3 VS_Normal;
in vec2 VS_TexCoord;

out vec4 FS_FragColor;

uniform mat4           U_ReNormalMatrix;
uniform vec3           U_ViewPosition;
uniform PointLightData U_LightData;

uniform sampler2D U_MeshTextures;
uniform sampler2D U_MeshAmbient;
uniform sampler2D U_MeshSpecular;
uniform sampler2D U_MeshDiffMap;

vec3 calculateAmbientColor(vec4 objColor)
{
  float ambStrength = texture(U_MeshAmbient, VS_TexCoord).r;
  vec3  ambMap      = texture(U_MeshAmbient, VS_TexCoord).rgb;
  vec3  ambColor    = ambStrength * U_LightData.color;
  return ambColor * ambMap * objColor.rgb * U_LightData.color.rgb;
}

vec3 calculateDiffuseColor(vec4 objColor)
{
  vec3  lightDirection = normalize(U_LightData.position - VS_FragPos).rbg;
  float diffMap        = texture(U_MeshDiffMap, VS_TexCoord).r;
  float diffValue      = max(dot(VS_Normal, lightDirection), 0.0);
  return diffValue * diffMap * objColor.rgb * U_LightData.color.rgb;
}

vec3 calculateSpecular(vec4 objColor)
{
  vec3  lightDirection   = normalize(U_LightData.position - VS_FragPos).rbg;
  float specMap          = texture(U_MeshSpecular, VS_TexCoord).r;
  vec3  viewDirection    = normalize(U_ViewPosition - VS_FragPos);
  vec3  reflectDirection = reflect(-lightDirection, VS_Normal);

  float specValue = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);
  return specValue * specMap * objColor.rgb * U_LightData.color.rgb;
}

void main()
{
  vec4 objColor = texture(U_MeshTextures, VS_TexCoord);
  vec3 val = calculateAmbientColor(objColor) + calculateDiffuseColor(objColor) +
             calculateSpecular(objColor);
  FS_FragColor = vec4(val, objColor.a);
}
