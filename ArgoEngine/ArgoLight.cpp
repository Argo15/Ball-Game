#include "ArgoLight.h"

void ArgoLight::setColor(float r, float g, float b)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
}

void ArgoLight::updateDockedWidget()
{
	ArgoActor::updateDockedWidget();
}