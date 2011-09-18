#version 120

uniform sampler2D tex;
uniform sampler2D normalmap;
uniform bool normalenabled;
uniform vec3 lookDir;
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
	vec3 _normal = normalize(tangmat*normalcolor);
	vec3 viewVector = normalize(lookDir);
	vec3 lightDir = normalize(gl_LightSource[0].position.xyz);
	vec4 texcolor = texture2D(tex,gl_TexCoord[0].st);
	vec4 lightcolor =	gl_FrontMaterial.ambient*gl_LightSource[0].ambient+
						gl_FrontMaterial.diffuse*gl_LightSource[0].diffuse*clamp(dot(_normal,-lightDir),0.0,1.0);
	float specular = pow(clamp(dot(reflect(-lightDir,_normal),viewVector),0.0,1.0),gl_FrontMaterial.shininess)*gl_LightSource[0].specular.r*gl_FrontMaterial.specular.r;
	vec4 finalcolor = color*texcolor*lightcolor+vec4(specular)+gl_FrontMaterial.emission;
	gl_FragColor = finalcolor;
} 