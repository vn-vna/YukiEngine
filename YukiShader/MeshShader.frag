#version 460 core

#define MAX_SHADER 128

in vec3 VS_FragPos;
in vec3 VS_Normal;
in vec2 VS_TexCoord;

out vec4 FS_FragColor;

uniform mat4  U_ReNormalMatrix;
uniform float U_SpecularStrength;
uniform float U_AmbientStrength;
uniform vec3  U_LightPos;
uniform vec4  U_LightColor;
uniform vec3  U_ViewPosition;
uniform float U_LightIntensity;

uniform sampler2D U_MeshTextures;

void main()
{

  // vec4 fragmentColor        = texture(U_MeshTextures, VS_TexCoord);
  vec4 fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);
  vec3 fragNormal    = mat3(U_ReNormalMatrix) * VS_Normal;

  {
    vec4 ambient = U_AmbientStrength * U_LightColor;

    float lightDistance    = length(U_LightPos - VS_FragPos);
    vec3  lightDirection   = normalize(U_LightPos - VS_FragPos);
    vec3  viewDirection    = normalize(U_ViewPosition - VS_FragPos);
    vec3  halfwayDirection = normalize(viewDirection + lightDirection);

    // calculate diffuse
    float diff = max(dot(fragNormal, lightDirection / pow(lightDistance, U_LightIntensity)), 0.0);

    vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 diffuse  = vec4(0.0, 0.0, 0.0, 0.0);

    if (diff > 0)
    {
      diffuse = diff * U_LightColor;

      // calculate specular
      // vec3 reflectDirection   = reflect(-lightDirection, fragNormal);
      // float rdDot             = dot(reflectDirection, viewDirection);
      float hnDot = dot(halfwayDirection, fragNormal);
      float spec  = pow(max(hnDot, 0.0), 128);
      specular    = U_SpecularStrength * spec * U_LightColor;
    }

    fragmentColor *= ambient + diffuse + specular;
  }

  FS_FragColor = fragmentColor;
}