#version 130

out vec3 pixel_color;

smooth in vec4 frag_pos;
smooth in vec4 frag_norm;
smooth in vec3 frag_col;

uniform mat4 uni_proj_mat;
uniform mat4 uni_view_mat;
uniform mat4 uni_mod_mat;
uniform vec3 uni_color;

vec3 sun_direction = normalize(vec3(-1.5, -0.8, -1));
vec3 sun_color = vec3(1, 1, 1);

vec3 mist_color = vec3(0.7, 0.7, 1);
float mist_start = 450;
float mist_depth = 50;

float specular_power = 50;
float specular_shine = 0;

void main()
{
	// Geometry
	vec3 world_norm = normalize((uni_mod_mat * frag_norm).xyz);
	vec3 cam_pos = (uni_view_mat * frag_pos).xyz;

	// Ambiant light
	vec3 ambiant_light = 0.5 * sun_color;

	// Diffuse light
	vec3 diffuse_light = 0.5 * sun_color * max(0, dot(world_norm, -normalize(sun_direction)));

	// Specular light
	vec3 reflect_vec = (uni_view_mat * vec4(reflect(sun_direction, world_norm), 0)).xyz;
	float specular_val = clamp(dot(-normalize(cam_pos), reflect_vec) - specular_shine, 0, 1);
	vec3 specular_light = sun_color * pow(specular_val, specular_power);

	// Total light
	vec3 total_light = ambiant_light + diffuse_light + specular_light;

	// Surface color
	vec3 surface_color = frag_col * uni_color;

	// Mist
	vec3 mist_glow = mist_color * sun_color;
	float mist_val = pow(clamp((length(cam_pos) - mist_start) / mist_depth, 0, 1), 1);
	//mist_val = 0;

	// Final pixel color
	pixel_color = mix(surface_color * total_light, mist_glow, mist_val);
}
