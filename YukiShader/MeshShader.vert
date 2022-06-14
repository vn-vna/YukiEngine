#version 460 core

layout(location = 0) in vec3 IA_VertexPos;
layout(location = 1) in vec3 IA_Normal;
layout(location = 2) in vec2 IA_TexCoord;

out vec3 VS_FragPos;
out vec3 VS_Normal;
out vec2 VS_TexCoord;

uniform mat4 U_ModelMatrix;
uniform mat4 U_ViewMatrix;
uniform mat4 U_ProjectionMatrix;

void main()
{
  gl_Position = U_ProjectionMatrix * U_ViewMatrix * U_ModelMatrix * vec4(IA_VertexPos, 1.0);
  VS_FragPos  = (U_ModelMatrix * vec4(IA_VertexPos, 1.0)).xyz;
  VS_Normal   = IA_Normal;
  VS_TexCoord = IA_TexCoord;
}