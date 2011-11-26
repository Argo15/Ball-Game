#version 120

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
	float numSamples = 4;
	vec3 samples[4] = vec3[](
		vec3(0.178571, -0.822257, -0.540375),
		vec3(0.0739551, -0.559848, 0.825288),
		vec3(0.251094, 0.638356, 0.727635),
		vec3(0.561541, -0.147783, -0.814145)
	);
	vec3 samples2[4] = vec3[](
		vec3(0.653557, 0.52561, 0.544607),
		vec3(0.619019, 0.752763, 0.223972),
		vec3(-0.444555, 0.580853, -0.681895),
		vec3(-0.37873, -0.67566, -0.632493)
	);

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
	float closestDist;
	float shadow = 1.0;
	float off = 0.003;
	
	for (int i=0; i<numSamples; i++) {
		vec3 newLightDir = lightDir-off*samples[i];
		closestDist = textureCube(shadowCubeTex,newLightDir).x;
		if (distance > closestDist*radius*1.05){
			shadow -= 0.5/numSamples;
		}
		
		newLightDir = lightDir-off*samples2[i];
		closestDist = textureCube(shadowCubeTex,newLightDir).x;
		if (distance > closestDist*radius*1.05){
			shadow -= 0.5/numSamples;
		}
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