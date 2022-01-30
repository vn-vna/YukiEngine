#version 460 core

layout (location = 0) in vec3 IA_In_VertexPos;
layout (location = 1) in vec4 IA_In_VertexColor;
layout (location = 2) in vec3 IA_In_TexCoord;
layout (location = 3) in uint IA_In_TexureID;

out vec4 VS_Out_VertexColor;
out vec3 VS_Out_TexCoord;

uniform mat4 U_ModelMatrix;
uniform mat4 U_ViewMatrix;
uniform mat4 U_PresentationMatrix;

void main() 
{
  gl_Position = U_PresentationMatrix * U_ViewMatrix * U_ModelMatrix * vec4(IA_In_VertexPos, 1.0);
  VS_Out_VertexColor = IA_In_VertexColor;
  VS_Out_TexCoord = IA_In_TexCoord;
}