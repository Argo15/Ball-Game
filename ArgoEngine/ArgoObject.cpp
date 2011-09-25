#include "ArgoObject.h"
#include "DockedObjectWidget.h"
#include "ArgoModelManager.h"

ArgoObject::ArgoObject(QString *name, QString *model, QString *material) : 
	ArgoActor(name,model,material) 
{
	body.type=STATIC;
	createRigidBody();
}

void ArgoObject::updateDockedWidget()
{
	DockedActorEditor::Instance()->getMainWidget()->getObjectWidget()->show();
	DockedActorEditor::Instance()->getMainWidget()->getObjectWidget()->createFromObject(this);
	ArgoActor::updateDockedWidget();
}

void ArgoObject::createRigidBody()
{
	body.triangles = ArgoModelManager::Instance()->getModel(*getModel())->getPhysTriangles();
	body.numTriangles = ArgoModelManager::Instance()->getModel(*getModel())->getNumTriangles();
	float *newTriangles = new float[body.numTriangles*9.0];
	for (int i=0; i<body.numTriangles*9.0; i+=3) {
		glPushMatrix();
			glLoadIdentity();
			transform();
			ArgoMatrix4 actorMat;
			actorMat.setAsModelViewMatrix();
		glPopMatrix();
		ArgoVector4 newVertex(body.triangles[i],body.triangles[i+1],body.triangles[i+2],1.0);
		newVertex = actorMat*newVertex;
		newTriangles[i]=newVertex[0];
		newTriangles[i+1]=newVertex[1];
		newTriangles[i+2]=newVertex[2];
	}
	body.triangles=newTriangles;
}