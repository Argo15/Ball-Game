#version 110

varying vec3 lookDir;

void main() {
	gl_FragColor = vec4(lookDir,1.0);	
} 