#version 460 core

in vec3 GS_FragPos;
in vec3 GS_Normal;
in vec4 GS_VertexColor;
in vec2 GS_TexCoord;
flat in uint GS_Flags;

out vec4 FS_FragColor;

uniform float U_AmbientStrength;
uniform vec3 U_LightPos;
uniform vec4 U_LightColor;

void main() 
{
  bool flagEnableTexture      = GS_Flags % 2 == 1;
  bool flagEnableLighting     = (GS_Flags / 2) % 2 == 1;
  
  if (flagEnableLighting)
  {
    vec4 ambient = U_AmbientStrength * U_LightColor;

    vec3 lightDirection = normalize(U_LightPos - GS_FragPos);
    float diff = max(abs(dot(GS_Normal, lightDirection)), 0.0);
    vec4 diffuse = diff * U_LightColor;

    FS_FragColor = (ambient + diffuse) * GS_VertexColor;
  }
}