#version 460 core

#define MAX_SHADER 128

in vec3           GS_FragPos;
in vec3           GS_Normal;
in vec4           GS_VertexColor;
in vec2           GS_TexCoord;
flat in uint      GS_Flags;

out vec4          FS_FragColor;

uniform float     U_SpecularStrength;
uniform float     U_AmbientStrength;
uniform vec3      U_LightPos;
uniform vec4      U_LightColor;
uniform vec3      U_ViewPosition;
uniform float     U_LightIntensity;

uniform sampler2D U_MeshTextures;

void main() 
{
  bool flagEnableTexture    = GS_Flags        % 2 == 1;
  bool flagEnableLighting   = (GS_Flags / 2)  % 2 == 1;
  bool flagEnableVertColor  = (GS_Flags / 4)  % 2 == 1;
  
  vec4 fragmentColor        = vec4(1.0, 1.0, 1.0, 1.0);

  if (flagEnableTexture)
  {
    fragmentColor           *= texture(U_MeshTextures, GS_TexCoord);
  }

  if (flagEnableVertColor)
  {
    fragmentColor           *= GS_VertexColor;
  }

  if (flagEnableLighting)
  {
    vec4 ambient            = U_AmbientStrength * U_LightColor;

    float lightDistance     = length(U_LightPos - GS_FragPos); 
    vec3 lightDirection     = normalize(U_LightPos - GS_FragPos);
    float diff              = max(dot(GS_Normal, lightDirection / pow(lightDistance, U_LightIntensity)), 0.0);
    vec4 diffuse            = diff * U_LightColor;

    vec3 viewDirection      = normalize(U_ViewPosition - GS_FragPos);
    vec3 reflectDirection   = reflect(-lightDirection, GS_Normal);

    float spec              = pow(max(dot(reflectDirection, viewDirection), 0.0), 32);
    vec4 specular           = U_SpecularStrength * spec * U_LightColor;

    fragmentColor           *= ambient + diffuse + specular;
  }

  FS_FragColor              = fragmentColor;
}