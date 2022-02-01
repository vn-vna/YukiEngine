#version 460 core

in vec3 GS_Normal;
in vec4 GS_VertexColor;
in vec2 GS_TexCoord;

out vec4 FS_FragColor;

uniform float U_AmbientStrength;

void main() 
{
  FS_FragColor = U_AmbientStrength * GS_VertexColor;
}