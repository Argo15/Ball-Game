#version 110

uniform sampler2D colorTex;
uniform sampler2D lightTex;
uniform sampler2D specTex;

void main() {
	vec4 color = texture2D(colorTex,gl_TexCoord[0].st);
	vec4 lightColor = texture2D(lightTex,gl_TexCoord[0].st);
	vec4 specColor = texture2D(specTex,gl_TexCoord[0].st);
	gl_FragColor = vec4(color.xyz*lightColor.xyz+specColor.xyz,1.0);	
} 