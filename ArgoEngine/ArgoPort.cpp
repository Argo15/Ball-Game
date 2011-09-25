#include "ArgoPort.h"
#include "ArgoModelManager.h"
#include "ArgoMaterialManager.h"


void ArgoPort::setType(PortType type) {
	this->type=type;
	for (int i=0; i<3; i++)
		scale[i]=0.25;
	this->setModel(ArgoModelManager::Instance()->getPortModel()->getName());
	switch (type) {
		case ENTRANCE:
			this->setMaterial(ArgoMaterialManager::Instance()->getEntranceMaterial()->getName());
			break;
		case EXIT:
			this->setMaterial(ArgoMaterialManager::Instance()->getExitMaterial()->getName());
			break;
		default: break;
	}
}

void ArgoPort::updateDockedWidget()
{
	ArgoActor::updateDockedWidget();
}