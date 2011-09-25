#include "ArgoCubeShadowFBO.h"

ArgoCubeShadowFBO::ArgoCubeShadowFBO(int resolution)
{
	this->width=resolution;
	this->height=resolution;

	std::string log;
	cubeShadowProg = new GLSLProgram("Data/Shaders/v_cubeshadow.glsl","Data/Shaders/f_cubeshadow.glsl");
	if (!cubeShadowProg->vertex_->isCompiled()){
		cubeShadowProg->vertex_->getShaderLog(log);
	}
	if (!cubeShadowProg->fragment_->isCompiled()){	
		cubeShadowProg->fragment_->getShaderLog(log);
	}

	glGenFramebuffersEXT(1,&buffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);

	glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &cubeTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP,cubeTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	for (int i=0; i<6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA16, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + i, GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, cubeTexture, 0);
	}
	glDisable(GL_TEXTURE_CUBE_MAP);

	glGenRenderbuffersEXT(1, &renderbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT32,width,height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, renderbuffer);

	GLenum FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO. %i\n",FBOstatus);
	else
		printf("Cube Map Buffer Done\n");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

}