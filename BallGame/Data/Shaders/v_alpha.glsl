#version 110

varying vec4 position;

void main() {
	gl_TexCoord[0] = gl_MultiTexCoord0;
	position = ftransform();
	gl_Position = position;
}