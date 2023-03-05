// Source code for the circle vertex shader
#version 130

in vec2 fragCoord;

out vec4 fragColor;

uniform vec3 position;
uniform vec3 color;
uniform float radius;

vec4 circle(vec2 uv, vec2 pos, float rad, vec3 color) {
	float d = length(pos - uv) - rad;
	float t = clamp(d, 0.0, 1.0);
	return vec4(color, 1.0-t);
}

void main() {
	vec2 uv = fragCoord.xy;
	fragColor = circle(uv, position.xy, radius, color);
}