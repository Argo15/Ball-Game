#include "Selection.h"

void Selection::calculateSelection(ArgoFrustum *frustum, int mouseX, int mouseY)
{
	if (Transformer::selected != -1)
		return;

	QMap<QString,ArgoActor *> *actors = ArgoSceneManager::Instance()->getActors();

	glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

	float white[] = {1.0,1.0,1.0};
	float black[] = {0,0,0};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,white);
	glMaterialfv(GL_FRONT,GL_AMBIENT,white);
	glMaterialfv(GL_FRONT,GL_EMISSION,black);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float color[3];
	int currentID = 1;
	ArgoActor **tempActors = new ArgoActor *[actors->size()+1];
	QMap<QString, ArgoActor *>::iterator it;
	for (it = actors->begin(); it != actors->end(); ++it){
		ArgoActor *actor = it.value();
		if (frustum->isInFrustum(actor->getTranslateV(),actor->getScaledRadius())){
			glPushMatrix();
				getColorFromID(currentID,color);
				glColor3f(color[0],color[1],color[2]);
				actor->transform();
				ArgoModelManager::Instance()->DrawModelSelection(*(actor->getModel()));
				tempActors[currentID]=actor;
				currentID++;
			glPopMatrix();
		}
	}

	unsigned char readcolor[3];
	GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(mouseX, viewport[3] - mouseY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, readcolor);
	int selectID = getIDFromColor(readcolor[0], readcolor[1], readcolor[2]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

	if (selectID <= actors->size()+1 && selectID > 0) {
		ArgoSceneManager::Instance()->setSelected(tempActors[selectID]->getName());
	}

	delete tempActors;
}

void Selection::calculateSelectedTransformer(int mouseX, int mouseY)
{
	Transformer::selected=-1;
	Transformer::lastAngle=0;
	Transformer::dragPoint=ArgoVector3(0,0,0);

	QString *sActor = ArgoSceneManager::Instance()->getSelected();
	if (sActor == 0)
		return;

	ArgoActor *selectedActor = ArgoSceneManager::Instance()->getActor(*sActor);
	
	glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Transformer::draw(selectedActor->getName(),true);

	unsigned char color[3];
	GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(mouseX, viewport[3] - mouseY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
	int selectID = getIDFromColor(color[0], color[1], color[2]);

	if ( (selectID>=100000) && (selectID<100006) ) {
		Transformer::selected=selectID-100000;
	}

}