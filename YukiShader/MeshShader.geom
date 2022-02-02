#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;


in vec3 VS_FragPos[];
in vec4 VS_VertexColor[];
in vec2 VS_TexCoord[];
in uint VS_Flags[];

out vec3 GS_FragPos;
out vec3 GS_Normal;
out vec4 GS_VertexColor;
out vec2 GS_TexCoord;
out uint GS_Flags;

void main()
{
  vec3 a        = (VS_FragPos[1] - VS_FragPos[0]).xyz;
  vec3 b        = (VS_FragPos[2] - VS_FragPos[0]).xyz;
  vec3 normal   = normalize(cross(b, a));
  
  for (int i = 0; i < gl_in.length() ; ++i)
  {
    gl_Position         = gl_in[i].gl_Position;
    GS_FragPos          = VS_FragPos[i];
    GS_Normal           = normal;
    GS_VertexColor      = VS_VertexColor[i];
    GS_TexCoord         = VS_TexCoord[i];
    GS_Flags            = VS_Flags[i];
    EmitVertex();
  }
  EndPrimitive();
}