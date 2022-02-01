#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

in vec4 VS_VertexColor[];
in vec2 VS_TexCoord[];
in uint VS_Flags[];

out vec3 GS_Normal;
out vec4 GS_VertexColor;
out vec2 GS_TexCoord;

void main()
{
  vec3 a        = (gl_in[1].gl_Position - gl_in[0].gl_Position).xyz;
  vec3 b        = (gl_in[2].gl_Position - gl_in[0].gl_Position).xyz;
  vec3 normal   = normalize(cross(b, a));
  
  for (int i = 0; i < gl_in.length() ; ++i)
  {
    gl_Position         = gl_in[i].gl_Position;
    GS_Normal       = normal;
    GS_VertexColor  = VS_VertexColor[i];
    GS_TexCoord     = VS_TexCoord[i];
    EmitVertex();
  }
  EndPrimitive();
}