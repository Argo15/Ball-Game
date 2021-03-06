#version 110

uniform sampler2D depthTex;
uniform sampler2D colorTex;
uniform sampler2D normalTex;
uniform sampler2D glowTex;
uniform sampler2D lightTex;
uniform samplerCube shadowCubeTex;
uniform vec3 cameraPos;
uniform float attenuation;
uniform float radius;

void main() {
	if(radius < 1.0 || attenuation < 0.05)
	  discard;
	float hyperDepth = texture2D(depthTex,gl_TexCoord[0].st).r;
	vec4 screenPos = vec4(gl_TexCoord[0].s*2.0-1.0, gl_TexCoord[0].t*2.0-1.0, hyperDepth*2.0-1.0, 1.0);
	vec4 worldPos = gl_TextureMatrixInverse[2] * screenPos;
	worldPos /= worldPos.w;
		
	vec3 lightDir = worldPos.xyz-gl_LightSource[0].position.xyz;
	float distance = length(lightDir);
	if (distance > radius){
		discard;
	}
	
	lightDir = normalize(lightDir);
	float closestDist = textureCube(shadowCubeTex,lightDir).x;
	float shadow = 1.0;
	if (distance > closestDist*radius*1.05){
		shadow = 0.0;
	}
	vec3 look = normalize(worldPos.xyz.xyz-cameraPos);
	vec3 normal = texture2D(normalTex,gl_TexCoord[0].st).xyz;
	float specular = texture2D(normalTex,gl_TexCoord[0].st).a;
	float shininess = 128.0*texture2D(colorTex,gl_TexCoord[0].st).a;
	
	float atten = 1.0-clamp(pow(distance/radius,attenuation),0.0,1.0);
	
	vec4 lightcolor;
	vec3 specIntensity;
	if (length(normal) < 0.1){
		lightcolor=vec4(1.0);
		specIntensity=vec3(0.0);
		atten=1.0; 
	} else {
		normal = normalize(normal*vec3(2.0)-vec3(1.0));
		lightcolor = gl_LightSource[0].ambient+
					 shadow*gl_LightSource[0].diffuse*clamp(dot(normal,-lightDir.xyz),0.0,1.0);
		specIntensity = shadow*gl_LightSource[0].specular.xyz*(pow(clamp(dot(normalize(reflect(lightDir.xyz,normal)),-look),0.0,1.0),shininess)*specular);
	}
	vec3 glow = texture2D(glowTex,gl_TexCoord[0].st).xyz;
	vec3 prevLight = texture2D(lightTex,gl_TexCoord[0].st).xyz;
	gl_FragData[0] = vec4(atten*lightcolor.xyz+prevLight,1.0);
	gl_FragData[1] = vec4(atten*specIntensity+glow,1.0);
}