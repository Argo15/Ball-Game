#version 110

uniform vec3 lightPos;
varying vec3 lightDir;

void main() {
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	vec4 worldPos = gl_TextureMatrix[5] * gl_Vertex;
	lightDir = worldPos.xyz-lightPos;
}