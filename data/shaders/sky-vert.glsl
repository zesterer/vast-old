#version 130

in vec3 vert_pos;
in vec3 vert_col;
in vec3 vert_norm;
in vec2 vert_uv;

smooth out vec4 frag_pos;

uniform mat4 uni_proj_mat;
uniform mat4 uni_spin_mat;
uniform samplerCube uni_cubemap;

void main()
{
	gl_Position = uni_proj_mat * uni_spin_mat * vec4(vert_pos, 1);
	frag_pos = vec4(vert_pos, 0);
}
