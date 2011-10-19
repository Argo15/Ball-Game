#version 110

uniform sampler2D depthTex;
uniform sampler2D colorTex;
uniform sampler2D normalTex;
uniform sampler2D glowTex;
uniform sampler2DShadow shadowMap[4];
uniform float slices[3];
uniform vec3 cameraPos;
uniform bool lightenabled;
uniform float near;
uniform float far;

void main() {
	float hyperDepth = texture2D(depthTex,gl_TexCoord[0].st).r;
	float depth = (2.0 * near) / (far + near - (hyperDepth*2.0-1.0) * (far - near));
	if (depth>0.999)
		discard;

	vec4 screenPos = vec4(gl_TexCoord[0].s*2.0-1.0, gl_TexCoord[0].t*2.0-1.0, hyperDepth*2.0-1.0, 1.0);
	vec4 worldPos = gl_TextureMatrixInverse[2] * screenPos;
	worldPos /= worldPos.w;
	
	float mapNum=0.0;
	float sfilter=4.0;
	mat4 shadowMat = gl_TextureMatrix[3];
	if (depth<slices[1] && depth>=slices[0]){
		shadowMat = gl_TextureMatrix[4];
		mapNum=1.0;
		sfilter=3.0;
	} else if (depth<slices[2] && depth>=slices[1]){
		shadowMat = gl_TextureMatrix[5];
		mapNum=2.0;
		sfilter=2.0;
	} else if (depth>=slices[2]) {
		shadowMat = gl_TextureMatrix[6];
		mapNum=3.0;
		sfilter=2.0;
	}
	
	vec4 shadowCoord = shadowMat*worldPos;
	
	float xOff=0.0;
	float yOff=0.0;
	float shadowij=((sfilter-0.99)/2.0);
	float pixelOff=1024.0;
	float shadow;
	for (float i=-shadowij; i<=shadowij; i++){
		for (float j=-shadowij; j<=shadowij; j++){
			xOff=i/pixelOff;
			yOff=j/pixelOff;
			if ( mapNum < 0.5 )
				shadow += shadow2DProj(shadowMap[0], shadowCoord + vec4(xOff, yOff, -0.0005, 0.0)).w;
			else if(mapNum<1.5)
				shadow += shadow2DProj(shadowMap[1], shadowCoord + vec4(xOff, yOff, -0.001, 0.0)).w;
			else if(mapNum<2.5)
				shadow += shadow2DProj(shadowMap[2], shadowCoord + vec4(xOff, yOff, -0.0015, 0.0)).w;
			else
				shadow += shadow2DProj(shadowMap[3], shadowCoord + vec4(xOff, yOff, -0.002, 0.0)).w;
		}
	}
	shadow /= sfilter*sfilter;
		
	vec4 direction = -normalize(gl_LightSource[0].position);
	vec3 look = normalize(worldPos.xyz-cameraPos);
	vec3 normal = texture2D(normalTex,gl_TexCoord[0].st).xyz;
	float specular = texture2D(normalTex,gl_TexCoord[0].st).a;
	float shininess = 128.0*texture2D(colorTex,gl_TexCoord[0].st).a;
	vec4 lightcolor;
	vec3 specIntensity;
	if (length(normal) < 0.1){
		lightcolor=vec4(1.0);
		specIntensity=vec3(0.0);
	} else if (!lightenabled) {
		lightcolor=vec4(0.0);
		specIntensity=vec3(0.0);
	} else {
		normal = normalize(normal*vec3(2.0)-vec3(1.0));
		lightcolor = gl_LightSource[0].ambient+
					 shadow*gl_LightSource[0].diffuse*clamp(dot(normal,direction.xyz),0.0,1.0);
		specIntensity = gl_LightSource[0].specular.xyz*(shadow*pow(clamp(dot(normalize(reflect(-direction.xyz,normal)),-look),0.0,1.0),shininess)*specular);
	}
	vec3 glow = texture2D(glowTex,gl_TexCoord[0].st).xyz;
	gl_FragData[0] = vec4(lightcolor.xyz,1.0);
	gl_FragData[1] = vec4(specIntensity+glow,1.0);
}