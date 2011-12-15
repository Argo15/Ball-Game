#version 110

uniform sampler2D tex;
uniform sampler2D depthTex;
uniform float near;
uniform float far;
varying vec4 position;


void main() {
	vec4 color = texture2D(tex, gl_TexCoord[0].st);
	if (color.a < 0.01)
		discard;
	vec2 screenPos = vec2(((position.x/position.w)+1.0)/2.0,((position.y/position.w)+1.0)/2.0);
	float depth = texture2D(depthTex,screenPos).r;
	float fragDepth = (2.0 * near) / (far + near - (position.z/position.w) * (far - near));
	if (fragDepth > depth)
		discard; 
	gl_FragColor = color;
} 