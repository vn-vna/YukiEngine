#version 460 core

#define MAX_POINT_LIGHT 128

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

uniform mat4 U_ReNormalMatrix;
uniform vec3 U_ViewPosition;

uniform int            U_PointLightCount;
uniform PointLightData U_PointLightData[MAX_POINT_LIGHT];

uniform sampler2D U_MeshTextures;
uniform sampler2D U_MeshAmbient;
uniform sampler2D U_MeshSpecular;
uniform sampler2D U_MeshDiffMap;

layout(binding = 1) uniform PointLightBlock
{
  int            nPointLightCount;
  PointLightData nPointLightData[MAX_POINT_LIGHT];
};

vec3 _calcAmbCol()
{
  float ambStrength = texture(U_MeshAmbient, VS_TexCoord).r;
  vec3  ambMap      = texture(U_MeshAmbient, VS_TexCoord).rgb;
  return ambStrength * ambMap;
}

vec3 _diffPointLight()
{
  vec3 result = vec3(0.0, 0.0, 0.0);

  for (int i = 0; i < U_PointLightCount; ++i)
  {
    vec3  lightDir  = normalize(U_PointLightData[i].position - VS_FragPos).rbg;
    float diffMap   = texture(U_MeshDiffMap, VS_TexCoord).r;
    float diffValue = max(dot(VS_Normal, lightDir), 0.0);
    result += diffValue * diffMap * U_PointLightData[i].color.rgb;
  }

  return result;
}

vec3 _specPointLight()
{
  vec3 result = vec3(0.0, 0.0, 0.0);

  for (int i = 0; i < U_PointLightCount; ++i)
  {
    vec3  lightDir = normalize(U_PointLightData[i].position - VS_FragPos).rbg;
    float specMap  = texture(U_MeshSpecular, VS_TexCoord).r;
    vec3  viewDirection    = normalize(U_ViewPosition - VS_FragPos);
    vec3  reflectDirection = reflect(-lightDir, VS_Normal);

    float specValue = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);
    result += specValue * specMap * U_PointLightData[i].color.rgb;
  }

  return result;
}

void main()
{
  vec4 objColor = texture(U_MeshTextures, VS_TexCoord);
  vec3 val      = _calcAmbCol() + _diffPointLight() + _specPointLight();
  FS_FragColor  = vec4(val * objColor.rgb, objColor.a);
}
