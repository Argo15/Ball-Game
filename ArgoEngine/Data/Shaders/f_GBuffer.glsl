#version 110

uniform sampler2D tex;
uniform sampler2D normalmap;
uniform bool normalenabled;
varying vec4 color;
varying vec3 normal;
varying vec3 tangent;
varying vec3 bitangent;

void main() {
	mat3 tangmat;
	tangmat[0] = normalize(tangent);
	tangmat[1] = normalize(bitangent);
	tangmat[2] = normalize(normal);
	vec3 normalcolor;
	if (normalenabled)
		normalcolor = texture2D(normalmap,gl_TexCoord[0].st).xyz;
	else 
		normalcolor = vec3(0.5,0.5,1.0);
	normalcolor = normalcolor*2.0-vec3(1.0);
	vec3 normalv = normalize(tangmat*normalcolor);
	normalv = (normalv+vec3(1.0))/vec3(2.0);
	vec4 texcolor = texture2D(tex,gl_TexCoord[0].st);
	vec4 finalcolor=texcolor*color*gl_FrontMaterial.diffuse;
	gl_FragData[0] = vec4(normalv,gl_FrontMaterial.specular.x);
	gl_FragData[1] = vec4(finalcolor.xyz,gl_FrontMaterial.shininess/128.0);
	gl_FragData[2] = vec4(gl_FrontMaterial.emission.xyz,1.0);
} 