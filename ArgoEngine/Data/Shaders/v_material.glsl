#version 120

attribute vec3 v_vertex;
attribute vec2 v_texture;
attribute vec3 v_normal;
attribute vec3 v_tangent;
attribute vec3 v_bitangent;
attribute vec3 v_color;
varying vec4 color;
varying vec3 normal;
varying vec3 tangent;
varying vec3 bitangent;

void main() {
	gl_TexCoord[0] = gl_TextureMatrix[0]*vec4(v_texture,0.0,0.0);
	gl_Position = gl_ModelViewProjectionMatrix * vec4(v_vertex,1.0);
	normal = v_normal;
	tangent = v_tangent;
	bitangent = v_bitangent;
	color = vec4(v_color,1.0);
}