#version 130

out vec3 pixel_color;

smooth in vec4 frag_pos;
smooth in vec4 frag_norm;
smooth in vec3 frag_col;
smooth in vec2 frag_uv;

uniform mat4 uni_proj_mat;
uniform mat4 uni_view_mat;
uniform mat4 uni_mod_mat;
uniform vec3 uni_color;
uniform sampler2D uni_texture;

float diffuse_factor = 0.5;
float ambiant_factor = 0.2;
vec3  sun_direction = normalize(vec3(-1.5, -0.8, -1));
vec3  sun_color     = vec3(1, 1, 1);
float sun_factor    = 50;
float sun_shine     = 0;

void main()
{
	// Geometry
	vec3 world_norm = normalize((uni_mod_mat * frag_norm).xyz);
	vec3 cam_pos = (uni_view_mat * frag_pos).xyz;

	// Ambiant light
	vec3 ambiant_light = ambiant_factor * sun_color;

	// Diffuse light
	vec3 diffuse_light = diffuse_factor * sun_color * max(0, dot(world_norm, -normalize(sun_direction)));

	// Specular light
	vec3  reflect_vec = (uni_view_mat * vec4(reflect(sun_direction, world_norm), 0)).xyz;
	float specular_val = clamp(dot(-normalize(cam_pos), reflect_vec) + sun_shine, 0, 1);
	vec3  specular_light = sun_color * pow(specular_val, sun_factor);

	// Total light
	vec3 total_light = ambiant_light + diffuse_light + specular_light;

	// Surface color
	vec3 surface_color = texture2D(uni_texture, frag_uv).rgb * frag_col * uni_color;

	// Final pixel color
	pixel_color = surface_color * total_light;
}
