#version 460 core

layout (location = 0) in vec3 IA_VertexPos;
layout (location = 1) in vec4 IA_VertexColor;
layout (location = 2) in vec2 IA_TexCoord;

// Flags:
// Bit 0:         Enable texture
// Bit 1:         Enable lighting 
// Bit 2- 7:      Reserve
layout (location = 3) in uint IA_Flags;

out vec3 VS_FragPos;
out vec4 VS_VertexColor;
out vec2 VS_TexCoord;
out uint VS_Flags;

uniform mat4 U_ModelMatrix;
uniform mat4 U_ViewMatrix;
uniform mat4 U_PresentationMatrix;

void main() 
{
  gl_Position     = U_PresentationMatrix * U_ViewMatrix * U_ModelMatrix * vec4(IA_VertexPos, 1.0);
  VS_FragPos      = (U_ModelMatrix * vec4(IA_VertexPos, 1.0)).xyz;
  VS_VertexColor  = IA_VertexColor;
  VS_TexCoord     = IA_TexCoord;
  VS_Flags        = IA_Flags;
}