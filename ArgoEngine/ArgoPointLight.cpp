#include "ArgoPointLight.h"

ArgoPointLight::ArgoPointLight(QString *name)
{
	color[0]=1.0; color[1]=1.0; color[2]=1.0;
	ambient=0.0;
	diffuse=1.0;
	specular=1.0;
	attenuation=1.0;
	radius=5.0;
	translations[0]=0.0;translations[1]=1.0;translations[2]=0.0;
	scale[0]=0.1;scale[1]=0.1;scale[2]=0.1;
	enabled=true;
	this->setName(name);
	setModel(ArgoModelManager::Instance()->getPointLightModel()->getName());
	setMaterial(ArgoMaterialManager::Instance()->getLightMaterial()->getName());
	shadowMap = new ArgoPointShadowMap(512);
}

void ArgoPointLight::setPosition(float x, float y, float z)
{
	translations[0]=x;
	translations[1]=y;
	translations[2]=z;
}

void ArgoPointLight::sendToShader(GLSLProgram *glslProgram)
{
	float position[] = {translations[0],translations[1],translations[2],1.0};
	float amb[] = {ambient*color[0],ambient*color[1],ambient*color[2]};
	float dif[] = {diffuse*color[0],diffuse*color[1],diffuse*color[2]};
	float spc[] = {specular*color[0],specular*color[1],specular*color[2]};
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
	glLightfv(GL_LIGHT0,GL_SPECULAR,spc);
	glslProgram->sendUniform("attenuation",attenuation);
	glslProgram->sendUniform("radius",radius);
}

void ArgoPointLight::buildShadowMaps(ArgoFrustum *frustum)
{
	shadowMap->generateShadowMap(ArgoVector3(translations[0],translations[1],translations[2]),radius,frustum);
}

void ArgoPointLight::sendShadowsToShader(GLSLProgram *program)
{
	GLuint cubeMap = shadowMap->getShadowMap();

	glActiveTexture(GL_TEXTURE8);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP,cubeMap);
	program->sendUniform("shadowCubeTex",8);
	glEnable(GL_TEXTURE_2D);
}

void ArgoPointLight::updateDockedWidget()
{
	ArgoLight::updateDockedWidget();
}