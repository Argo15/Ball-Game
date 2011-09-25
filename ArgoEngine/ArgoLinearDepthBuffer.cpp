#include "ArgoLinearDepthBuffer.h"

ArgoLinearDepthBuffer::ArgoLinearDepthBuffer(int width, int height)
{
	this->width=width;
	this->height=height;

	std::string log;
	depthProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_depth.glsl");
	if (!depthProg->vertex_->isCompiled()){
		depthProg->vertex_->getShaderLog(log);
	}
	if (!depthProg->fragment_->isCompiled()){	
		depthProg->fragment_->getShaderLog(log);
	}

	glEnable(GL_TEXTURE_2D);

	glGenFramebuffersEXT(1,&buffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);

	glGenTextures(1, &linearDepthTex);
	glBindTexture(GL_TEXTURE_2D, linearDepthTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, linearDepthTex, 0);

	// check FbO status
	GLenum FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO. %i\n",FBOstatus);
	else
		printf("Linear Depth Buffer Done\n");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}