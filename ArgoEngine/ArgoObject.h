#ifndef ARGOOBJECT_H
#define ARGOOBJECT_H

#include "ArgoActor.h"
#include "ArgoRigidBody.h"

class ArgoObject : public ArgoActor
{
private:
	ArgoRigidBody body;

public:
	ArgoObject(){}
	ArgoObject(QString *name, QString *model = 0, QString *material = 0);
	~ArgoObject(){}

	virtual void updateDockedWidget();
	void createRigidBody();
	ArgoRigidBody getRigidBody() {return body;}
};

#endif