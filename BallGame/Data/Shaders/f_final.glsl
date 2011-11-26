#version 110

uniform sampler2D colorTex;
uniform sampler2D lightTex;
uniform sampler2D specTex;
uniform sampler2D ssaoTex;

void main() {
	vec4 color = texture2D(colorTex,gl_TexCoord[0].st);
	vec4 lightColor = texture2D(lightTex,gl_TexCoord[0].st);
	vec4 specColor = texture2D(specTex,gl_TexCoord[0].st);
	float ssaoColor = texture2D(ssaoTex,gl_TexCoord[0].st).r;
	gl_FragColor = vec4(color.xyz*lightColor.xyz*ssaoColor+specColor.xyz,1.0);	
} 