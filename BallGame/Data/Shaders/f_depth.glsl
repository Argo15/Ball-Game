#version 110

uniform sampler2D depthTex;
uniform float near;
uniform float far;

void main() {
	float depth = texture2D(depthTex,gl_TexCoord[0].st).r;
	float lin_depth = (2.0 * near) / (far + near - (depth*2.0-1.0) * (far - near));
	gl_FragColor = vec4(lin_depth);	
} 