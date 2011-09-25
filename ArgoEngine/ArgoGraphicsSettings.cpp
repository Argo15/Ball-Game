#include "ArgoGraphicsSettings.h"

ArgoGraphicsSettings *ArgoGraphicsSettings::pInstance = 0;

ArgoGraphicsSettings::ArgoGraphicsSettings()
{
	shaders = true;
}

void ArgoGraphicsSettings::Initialize()
{
	pInstance=new ArgoGraphicsSettings;
}

ArgoGraphicsSettings *ArgoGraphicsSettings::Instance()
{
	return pInstance;
}