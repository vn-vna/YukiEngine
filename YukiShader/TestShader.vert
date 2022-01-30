#version 460

layout (location = 0) in vec3 IA_IN_VertexPosition;

void main(void) 
{
  gl_Position = vec4(IA_IN_VertexPosition, 1.00);
}
