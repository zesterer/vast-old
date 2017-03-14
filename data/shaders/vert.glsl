#version 130

in vec3 vert_pos;
in vec3 vert_col;
in vec3 vert_norm;
in vec2 vert_uv;

smooth out vec4 frag_pos;
smooth out vec4 frag_norm;
smooth out vec3 frag_col;
smooth out vec2 frag_uv;

uniform mat4 uni_proj_mat;
uniform mat4 uni_view_mat;
uniform mat4 uni_mod_mat;
uniform vec3 uni_color;
uniform sampler2D uni_texture;

void main()
{
	vec4 world_pos = uni_mod_mat * vec4(vert_pos, 1);
	gl_Position = uni_proj_mat * uni_view_mat * world_pos;

	frag_pos = world_pos;
	frag_col = vert_col;
	frag_norm = vec4(vert_norm, 0);
	frag_uv = vert_uv;
}
