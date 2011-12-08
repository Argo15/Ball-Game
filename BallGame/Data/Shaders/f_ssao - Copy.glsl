#version 120

uniform sampler2D depthTex;
uniform float near;
uniform float far;

void main() {
	float numSamples = 8;
	vec3 samples[8] = vec3[](
		vec3(0.504819, -0.682676, -0.52831),
		vec3(-0.0769878, 0.74329, 0.664524),
		vec3(0.129552, -0.20929, -0.969234),
		vec3(-0.307936, 0.63848, -0.70535),
		vec3(0.0798244, -0.839381, -0.537651),
		vec3(-0.97612, -0.216725, -0.0148617),
		vec3(-0.666353, 0.121957, -0.735595),
		vec3(0.21801, -0.638822, 0.73782)
	);
	vec3 samples2[8] = vec3[](
		vec3(0.933321, -0.281096, 0.223374),
		vec3(-0.958038, -0.244364, 0.149832),
		vec3(-0.00334457, 0.160155, 0.987086),
		vec3(-0.199883, 0.895859, 0.396843),
		vec3(0.720137, -0.308266, 0.621591),
		vec3(0.457198, 0.789847, -0.408792),
		vec3(0.180365, 0.616501, -0.766417),
		vec3(-0.0809984, -0.50934, 0.856745)
	);
	
	float hyperDepth = texture2D(depthTex,gl_TexCoord[0].st).r;
	float depth = (2.0 * near) / (far + near - (hyperDepth*2.0-1.0) * (far - near));

	vec4 screenPos = vec4(gl_TexCoord[0].s*2.0-1.0, gl_TexCoord[0].t*2.0-1.0, hyperDepth*2.0-1.0, 1.0);
	vec4 worldPos = gl_TextureMatrixInverse[2] * screenPos;
	worldPos /= worldPos.w;
	
	float scale = 0.1;
	float newDepth = 0.0;
	float intensity = 0.0;
	vec4 newScreenPos;
	vec4 newWorldPos;
	float sampleHyperDepth;
	float sampleDepth;
	
	for (int i=0; i<numSamples; i++) {
		newWorldPos = vec4(worldPos.xyz+scale*samples[i],1.0);
		newScreenPos = gl_TextureMatrix[2] * newWorldPos;
		newScreenPos = newScreenPos/newScreenPos.w;
		newDepth = (2.0 * near) / (far + near - (newScreenPos.z) * (far - near));
		newScreenPos = newScreenPos / 2.0 + vec4(0.5, 0.5, 0.0, 0.0);
		sampleHyperDepth = texture2D(depthTex,newScreenPos.st).r;
		sampleDepth = (2.0 * near) / (far + near - (sampleHyperDepth*2.0-1.0) * (far - near));
		if (newDepth-0.0001 < sampleDepth || (newDepth - sampleDepth) > 0.5/(far - near))
			intensity++;
			
		newWorldPos = vec4(worldPos.xyz+scale*samples2[i],1.0);
		newScreenPos = gl_TextureMatrix[2] * newWorldPos;
		newScreenPos = newScreenPos/newScreenPos.w;
		newDepth = (2.0 * near) / (far + near - (newScreenPos.z) * (far - near));
		newScreenPos = newScreenPos / 2.0 + vec4(0.5, 0.5, 0.0, 0.0);
		sampleHyperDepth = texture2D(depthTex,newScreenPos.st).r;
		sampleDepth = (2.0 * near) / (far + near - (sampleHyperDepth*2.0-1.0) * (far - near));
		if (newDepth-0.00003 < sampleDepth || (newDepth - sampleDepth) > 0.5/(far - near))
			intensity++;
	}
	
	if ((intensity+3) > (numSamples))
		intensity = 1.0;
	else
		intensity = clamp(intensity/(2.0*numSamples),0,1);
	
	if (depth>0.99)
		gl_FragColor = vec4(1.0,1.0,1.0,1.0);
	else
		gl_FragColor = vec4(intensity,intensity,intensity,intensity);
}