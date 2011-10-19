#version 120

uniform sampler2D tex;
uniform float height;
uniform float size;

void main() {
	float samples[3] = float[3](0.0545, 0.2442, 0.4026);
	vec2 texcoord;
	vec4 totalColor = vec4(0);
	float totalWeight;
	vec4 texcolor;
	
	texcoord = gl_TexCoord[0].st-vec2(0,(size*2.0/height));
	if (texcoord.y > 0.0) {
		texcolor = texture2D(tex,texcoord);
		totalColor += samples[0]*texcolor;
		totalWeight += samples[0];
	}
	
	texcoord = gl_TexCoord[0].st-vec2(0,(size*1.0/height));
	if (texcoord.y > 0.0) {
		texcolor = texture2D(tex,texcoord);
		totalColor += samples[1]*texcolor;
		totalWeight += samples[1];
	}
	
	texcoord = gl_TexCoord[0].st;
	texcolor = texture2D(tex,texcoord);
	totalColor += samples[2]*texcolor;
	totalWeight += samples[2];
	
	texcoord = gl_TexCoord[0].st+vec2(0,(size*1.0/height));
	if (texcoord.y < 1.0) {
		texcolor = texture2D(tex,texcoord);
		totalColor += samples[1]*texcolor;
		totalWeight += samples[1];
	}
	
	texcoord = gl_TexCoord[0].st+vec2(0,(size*2.0/height));
	if (texcoord.y < 1.0) {
		texcolor = texture2D(tex,texcoord);
		totalColor += samples[0]*texcolor;
		totalWeight += samples[0];
	}
	
	totalColor /= totalWeight;
	
	gl_FragData[0] = vec4(totalColor.xyz,1.0);	
} 