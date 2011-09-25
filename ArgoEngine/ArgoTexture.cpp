#include "ArgoTexture.h"

void ArgoTexture::use()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void ArgoTexture::remove()
{
	 glDeleteTextures(1,&textureID);
}