#version 110

attribute vec3 v_vertex;
attribute vec2 v_texture;
attribute vec3 v_normal;
attribute vec3 v_tangent;
attribute vec3 v_bitangent;
attribute vec3 v_color;
uniform vec3 cameraPos;
varying vec4 color;
varying vec3 normal;
varying vec3 tangent;
varying vec3 bitangent;
varying vec4 oldPosition;
varying vec4 newPosition;
varying vec3 viewVector;

void main() {
	gl_TexCoord[0] = gl_TextureMatrix[0]*vec4(v_texture,0.0,0.0);
	gl_Position = gl_ModelViewProjectionMatrix * vec4(v_vertex,1.0);
	vec4 worldPos = gl_TextureMatrixInverse[1] *  gl_ModelViewMatrix * vec4(v_vertex,1.0);
	viewVector=normalize(cameraPos - worldPos.xyz);
	normal = vec4(gl_TextureMatrix[7]*vec4(v_normal,0.0)).xyz;
	tangent = vec4(gl_TextureMatrix[7]*vec4(v_tangent,0.0)).xyz;
	bitangent = vec4(gl_TextureMatrix[7]*vec4(v_bitangent,0.0)).xyz;
	color = vec4(v_color,1.0);
	oldPosition = gl_ProjectionMatrix * gl_TextureMatrix[1] * gl_TextureMatrix[2] * vec4(v_vertex,1.0);
	newPosition = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(v_vertex,1.0);
	gl_Position = newPosition;
}