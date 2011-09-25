#ifndef ARGOPORT_H
#define ARGOPORT_H

#include "ArgoActor.h"

enum PortType { ENTRANCE, EXIT };

class ArgoPort : public ArgoActor {
private:
	PortType type;

public:
	ArgoPort() {setType(ENTRANCE); QString newName="New Port"; this->setName(newName);}
	ArgoPort(PortType type) {setType(type); QString newName="New Port"; this->setName(newName);}
	~ArgoPort() {}

	void setType(PortType type);
	PortType getType() {return type;}

	virtual void updateDockedWidget();

};

#endif