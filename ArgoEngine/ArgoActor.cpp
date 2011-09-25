#include "ArgoActor.h"
#include "DockedActorWidget.h"

ArgoActor::ArgoActor(QString *name, QString *model, QString *material)
{
	for (int i=0;i<3;i++){
		translations[i]=0;
		scale[i]=1.0;
	}
	rotation = ArgoQuaternion();
	this->model = model;
	this->material = material;
	this->name=name;
}

float ArgoActor::getScaledRadius()
{
	return ArgoModelManager::Instance()->getModel(*model)->getRadius()*max(max(scale[0],scale[1]),scale[2]);
}

void ArgoActor::transform()
{
	glTranslatef(translations[0],translations[1],translations[2]);
	glMatrixMode(GL_TEXTURE);
		glActiveTextureARB(GL_TEXTURE7);
		glLoadIdentity();
		rotation.getMatrix().multiplyToCurrent();
	glMatrixMode(GL_MODELVIEW);
	rotation.getMatrix().multiplyToCurrent();
	glScalef(scale[0],scale[1],scale[2]);
}

void ArgoActor::transformToCurrentMatrix()
{
	glTranslatef(translations[0],translations[1],translations[2]);
	rotation.getMatrix().multiplyToCurrent();
	glScalef(scale[0],scale[1],scale[2]);
}

void ArgoActor::updateDockedWidget()
{
	DockedActorEditor::Instance()->getMainWidget()->getActorWidget()->show();
	DockedActorEditor::Instance()->getMainWidget()->getActorWidget()->createFromActor(this);
}

void ArgoActor::actorModified()
{
	DockedActorEditor::Instance()->getMainWidget()->getActorWidget()->updateWidget();
}