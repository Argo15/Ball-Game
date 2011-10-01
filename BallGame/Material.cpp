#include "Material.h"

Material::Material() {
	for (int i=0;i<3;i++){
		color[i]=1.0;
		emission[i]=0.0;
	}
	texOffset[0]=0.0;
	texOffset[1]=0.0;
	texScale[0]=1.0;
	texScale[1]=1.0;
	texRotate=0.0;
	specular=0.0;
	shininess=25;
	normalEnabled=false;
}

void Material::use() 
{

}

void Material::useNoShaders(TextureRegistry *textures)
{
	glDisable(GL_COLOR_MATERIAL);

	float spec[] = {specular, specular, specular};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color);
	glMaterialfv(GL_FRONT,GL_AMBIENT,color);
	glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
	glMaterialf(GL_FRONT,GL_SHININESS,shininess);
	glMaterialfv(GL_FRONT,GL_EMISSION,emission);

	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE0);
	glLoadIdentity();
	glTranslatef(texOffset[0],texOffset[1],0.0);
	glRotatef(texRotate,0.0,0.0,1.0);
	glScalef(texScale[0],texScale[1],1.0);
	glMatrixMode(GL_MODELVIEW);

	textures->getTexture(texture)->use();
}