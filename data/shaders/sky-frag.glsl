#version 130

out vec3 pixel_color;

smooth in vec4 frag_pos;
smooth in vec4 frag_norm;
smooth in vec3 frag_col;
smooth in vec2 frag_uv;

uniform mat4 uni_proj_mat;
uniform mat4 uni_view_mat;
uniform vec3 uni_cam_pos;
uniform samplerCube uni_cubemap;

void main()
{
	// Geometry
	vec3 world_norm = normalize((frag_norm).xyz);
	vec3 cam_pos = (uni_view_mat * frag_pos).xyz;

	// Surface color
	vec3 surface_color = texture(uni_cubemap, normalize(frag_pos.xyz - uni_cam_pos)).rgb * frag_col;

	// Final pixel color
	pixel_color = surface_color;
}
