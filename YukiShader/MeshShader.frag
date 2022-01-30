#version 460 core

in vec4 VS_Out_VertexColor;
in vec4 VS_Out_TexCoord;

out vec4 FS_Out_FragColor;

void main() 
{
  FS_Out_FragColor = VS_Out_VertexColor;
}