#include "ArgoLightBuffer.h"
#include <assert.h>


ArgoLightBuffer::ArgoLightBuffer(int width, int height)
{
	this->width=width;
	this->height=height;

	std::string log;
	dLightProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_dlight.glsl");
	if (!dLightProg->vertex_->isCompiled()){
		dLightProg->vertex_->getShaderLog(log);
	}
	if (!dLightProg->fragment_->isCompiled()){	
		dLightProg->fragment_->getShaderLog(log);
		while(true) {
			printf(log.c_str());
		}
		assert (false);
	}
	pLightProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_plight.glsl");
	if (!pLightProg->vertex_->isCompiled()){
		pLightProg->vertex_->getShaderLog(log);
	}
	if (!pLightProg->fragment_->isCompiled()){	
		pLightProg->fragment_->getShaderLog(log);

	}
	

	glEnable(GL_TEXTURE_2D);

	glGenFramebuffersEXT(1,&buffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);

	glGenTextures(1, &lightTex);
	glBindTexture(GL_TEXTURE_2D, lightTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, lightTex, 0);

	glGenTextures(1, &specTex);
	glBindTexture(GL_TEXTURE_2D, specTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, specTex, 0);

	// check FbO status
	GLenum FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO. %i\n",FBOstatus);
	else
		printf("Light Buffer Done\n");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}