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

void Material::use(TextureRegistry *textures, GLSLProgram *program) 
{
	float spec[] = {specular, specular, specular};
	glDisable(GL_COLOR_MATERIAL);
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

	glActiveTextureARB(GL_TEXTURE0);
	textures->getTexture(texture)->use();
	program->sendUniform("tex",0);
	glActiveTexture(GL_TEXTURE1); 
	textures->getTexture(normal)->use();
	program->sendUniform("normalmap",1);
	program->sendUniform("normalenabled",normalEnabled);

}

void Material::useNoShaders(TextureRegistry *textures)
{
	glDisable(GL_COLOR_MATERIAL);
	
	float spec[] = {specular, specular, specular};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color);
	glMaterialfv(GL_FRONT,GL_AMBIENT,color);
	glColor3f(color[0],color[1],color[2]);
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