#version 460 core

out vec4 color;

in vec2 v_UV;

uniform vec3 u_Color;
uniform float u_Radius;
uniform float u_Smooth;

void main()
{
	double uvDistance = v_UV.x * v_UV.x + v_UV.y * v_UV.y;
	color = vec4(u_Color, 1 - smoothstep(u_Smooth, 1, uvDistance));
}
