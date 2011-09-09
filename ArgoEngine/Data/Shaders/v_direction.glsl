#version 110

uniform vec3 camPos;
varying vec3 lookDir;

void main() {
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	lookDir = vec3(gl_Vertex)-camPos;
	lookDir = (normalize(lookDir)+vec3(1.0)) * 0.5;
}