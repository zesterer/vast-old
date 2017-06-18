#version 130

out vec3 pixel_color;

smooth in vec4 frag_pos;

uniform mat4 uni_proj_mat;
uniform mat4 uni_spin_mat;
uniform samplerCube uni_cubemap;

void main()
{
	// Surface color
	vec3 surface_color = texture(uni_cubemap, normalize(frag_pos.xyz)).rgb;

	// Final pixel color
	pixel_color = surface_color;
}
