#version 120

uniform sampler2D tex;
uniform sampler2D velTex;
uniform float numSamples;

void main() {
	vec4 totalColor = vec4(0.0);
	vec2 velocity = texture2D(velTex,gl_TexCoord[0].st).rg*2.0-vec2(1.0);
	vec2 vel = velocity;
	velocity /= 2.5*1.5;
	for (float i = 0; i<numSamples; i++) {
		totalColor += texture2D(tex,gl_TexCoord[0].st-velocity*((i-(numSamples/2))/numSamples));
	}
	totalColor /= numSamples;
	if (length(vel) > 0.99)
		totalColor = texture2D(tex,gl_TexCoord[0].st);
	gl_FragData[0] = vec4(totalColor.xyz,1.0);	
} 