#version 120

uniform sampler2D depthTex;
uniform sampler2D depthBlurTex;

void main() {
	float depth = texture2D(depthTex,gl_TexCoord[0].st).r;
	float blurDepth = texture2D(depthBlurTex,gl_TexCoord[0].st).r;
	float diff = depth-blurDepth;
	if (diff > 0.0005) {
		diff = 0.0;
	}
	float ssao = 1.0 - diff / 0.0003;
	gl_FragColor = vec4(ssao,ssao,ssao,ssao);
}