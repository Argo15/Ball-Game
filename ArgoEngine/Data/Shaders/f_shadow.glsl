#version 110

uniform sampler2D tex;

void main() {
	float texcolor = texture2D(tex, gl_TexCoord[0].st).r;
	gl_FragColor = vec4(texcolor);	
} 