#version 110

uniform float radius;
varying vec3 lightDir;

void main() {
	float distancePercent = length(lightDir) / radius;
	gl_FragColor = vec4(distancePercent);	
} 