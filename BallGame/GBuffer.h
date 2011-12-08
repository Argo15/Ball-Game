#ifndef GBUFFER_H
#define GBUFFER_H

#include <windows.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>

class GBuffer 
{
private:
	GLuint depthTex;
	GLuint normalTex;
	GLuint colorTex;
	GLuint glowTex;
	GLuint motionTex;
	GLuint buffer;

	int width,height;

public:
	GBuffer(int width, int height);
	~GBuffer(){glDeleteFramebuffers(1,&buffer);}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindDepthTex() {glBindTexture(GL_TEXTURE_2D, depthTex);}
	void bindNormalTex() {glBindTexture(GL_TEXTURE_2D, normalTex);}
	void bindColorTex() {glBindTexture(GL_TEXTURE_2D, colorTex);}
	void bindGlowTex() {glBindTexture(GL_TEXTURE_2D, glowTex);}
	void bindMotionTex() {glBindTexture(GL_TEXTURE_2D, motionTex);}

	GLuint getGlowTex() {return glowTex;}
	GLuint getDepthTex() {return depthTex;}

	int getWidth() {return width;}
	int getHeight() {return height;}
};

#endif