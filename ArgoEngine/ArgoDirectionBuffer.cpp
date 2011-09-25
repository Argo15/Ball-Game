#include "ArgoDirectionBuffer.h"

ArgoDirectionBuffer::ArgoDirectionBuffer(int width, int height)
{
	this->width=width;
	this->height=height;

	std::string log;
	directionProg = new GLSLProgram("Data/Shaders/v_direction.glsl","Data/Shaders/f_direction.glsl");
	if (!directionProg->vertex_->isCompiled()){
		directionProg->vertex_->getShaderLog(log);
	}
	if (!directionProg->fragment_->isCompiled()){	
		directionProg->fragment_->getShaderLog(log);
	}

	glEnable(GL_TEXTURE_2D);

	glGenFramebuffersEXT(1,&buffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);

	glGenTextures(1, &directionTex);
	glBindTexture(GL_TEXTURE_2D, directionTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, directionTex, 0);

	// check FbO status
	GLenum FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO. %i\n",FBOstatus);
	else
		printf("Direction Buffer Done\n");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

