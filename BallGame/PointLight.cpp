#include "PointLight.h"

PointLight::PointLight()
{
	color[0]=1.0; color[1]=1.0; color[2]=1.0;
	ambient=0.0;
	diffuse=1.0;
	specular=1.0;
	attenuation=1.0;
	radius=5.0;
	translations[0]=0.0;translations[1]=1.0;translations[2]=0.0;
	enabled=true;
	shadowMap = new PointShadowMap(512);
}

void PointLight::setPosition(float x, float y, float z)
{
	translations[0]=x;
	translations[1]=y;
	translations[2]=z;
}

void PointLight::setColor(float r, float g, float b)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
}

void PointLight::sendToShader(GLSLProgram *glslProgram, GLenum lightNum)
{
	float position[] = {translations[0],translations[1],translations[2],1.0};
	float amb[] = {ambient*color[0],ambient*color[1],ambient*color[2]};
	float dif[] = {diffuse*color[0],diffuse*color[1],diffuse*color[2]};
	float spc[] = {specular*color[0],specular*color[1],specular*color[2]};
	glLightfv(lightNum,GL_POSITION,position);
	glLightfv(lightNum,GL_AMBIENT,amb);
	glLightfv(lightNum,GL_DIFFUSE,dif);
	glLightfv(lightNum,GL_SPECULAR,spc);
	if (glslProgram != 0) {
		glslProgram->sendUniform("attenuation",attenuation);
		glslProgram->sendUniform("radius",radius);
	}
}

void PointLight::buildShadowMaps(Frustum *frustum, Level *level, bool drawAll)
{
	shadowMap->generateShadowMap(ArgoVector3(translations[0],translations[1],translations[2]),radius,frustum,level,drawAll);
}

void PointLight::sendShadowsToShader(GLSLProgram *program)
{
	GLuint cubeMap = shadowMap->getShadowMap();

	glActiveTexture(GL_TEXTURE8);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP,cubeMap);
	program->sendUniform("shadowCubeTex",8);
	glEnable(GL_TEXTURE_2D);
}