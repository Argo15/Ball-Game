#include "Transformer.h"

int Transformer::selected = -1;
float Transformer::lastAngle = 0;
ArgoVector3 Transformer::dragPoint = ArgoVector3(0,0,0);

void Transformer::drawBoundingBox(QString *sActor)
{
	glPushMatrix();
	ArgoActor *actor = ArgoSceneManager::Instance()->getActor(*sActor);
	ArgoModel *model = ArgoModelManager::Instance()->getModel(*actor->getModel());
	glVertexAttrib3f(5,0.0,0.0,0.0);
	glColor3f(0.0,0.0,0.0);
	glLineWidth(3.0);
	float *center = model->getCenter();
	float radius = actor->getScaledRadius();
	float *translate = actor->getTranslate();
	glTranslatef(translate[0],translate[1],translate[2]);
	glBegin(GL_LINE_STRIP);
		glVertex3f(center[0]-radius,center[1]+radius,center[2]-radius);
		glVertex3f(center[0]-radius,center[1]+radius,center[2]+radius);
		glVertex3f(center[0]+radius,center[1]+radius,center[2]+radius);
		glVertex3f(center[0]+radius,center[1]+radius,center[2]-radius);
		glVertex3f(center[0]-radius,center[1]+radius,center[2]-radius);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex3f(center[0]-radius,center[1]-radius,center[2]-radius);
		glVertex3f(center[0]-radius,center[1]-radius,center[2]+radius);
		glVertex3f(center[0]+radius,center[1]-radius,center[2]+radius);
		glVertex3f(center[0]+radius,center[1]-radius,center[2]-radius);
		glVertex3f(center[0]-radius,center[1]-radius,center[2]-radius);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(center[0]-radius,center[1]+radius,center[2]-radius);
		glVertex3f(center[0]-radius,center[1]-radius,center[2]-radius);
		glVertex3f(center[0]-radius,center[1]+radius,center[2]+radius);
		glVertex3f(center[0]-radius,center[1]-radius,center[2]+radius);
		glVertex3f(center[0]+radius,center[1]+radius,center[2]+radius);
		glVertex3f(center[0]+radius,center[1]-radius,center[2]+radius);
		glVertex3f(center[0]+radius,center[1]+radius,center[2]-radius);
		glVertex3f(center[0]+radius,center[1]-radius,center[2]-radius);
	glEnd();
	glPopMatrix();
}

void Transformer::drawTranslator(QString *sActor,float *xColor,float *yColor, float *zColor, bool selection)
{
	glPushMatrix();
	ArgoActor *actor = ArgoSceneManager::Instance()->getActor(*sActor);
	ArgoModel *model = ArgoModelManager::Instance()->getModel(*actor->getModel());
	glColor3f(0.0,0.0,0.0);
	glVertexAttrib3f(5,0.0,0.0,0.0);
	glLineWidth(8.0);
	float *center = model->getCenter();
	float radius = actor->getScaledRadius();
	float *translate = actor->getTranslate();

	glTranslatef(translate[0],translate[1],translate[2]);
	glBegin(GL_LINES);
		glColor3f(xColor[0],xColor[1],xColor[2]);
		glVertexAttrib3f(5,xColor[0],xColor[1],xColor[2]);
		glVertex3f(center[0]+radius,center[1],center[2]);
		glVertex3f(center[0]+radius+max(0.2,radius),center[1],center[2]);
		glColor3f(yColor[0],yColor[1],yColor[2]);
		glVertexAttrib3f(5,yColor[0],yColor[1],yColor[2]);
		glVertex3f(center[0],center[1]+radius,center[2]);
		glVertex3f(center[0],center[1]+radius+max(0.2,radius),center[2]);
		glColor3f(zColor[0],zColor[1],zColor[2]);
		glVertexAttrib3f(5,zColor[0],zColor[1],zColor[2]);
		glVertex3f(center[0],center[1],center[2]+radius);
		glVertex3f(center[0],center[1],center[2]+radius+max(0.2,radius));
	glEnd();
	glPopMatrix();
}

void Transformer::drawRotator(QString *sActor, float *xColor, float *yColor, float *zColor, bool selection)
{
	glPushMatrix();
	ArgoActor *actor = ArgoSceneManager::Instance()->getActor(*sActor);
	ArgoModel *model = ArgoModelManager::Instance()->getModel(*actor->getModel());
	glVertexAttrib3f(5,0.0,0.0,0.0);
	glLineWidth(10.0);
	float *center = model->getCenter();
	float radius = actor->getScaledRadius();
	float *translate = actor->getTranslate();

	glTranslatef(translate[0],translate[1],translate[2]);
	glBegin(GL_LINE_STRIP);
		glColor3f(xColor[0],xColor[1],xColor[2]);
		glVertexAttrib3f(5,xColor[0],xColor[1],xColor[2]);
		for(int i=0;i<100;i++){
			glVertex3f(center[0],center[1]+radius*sinf(i/50.0*PI),center[2]+radius*cosf(i/50.0*PI));
		}
		glVertex3f(center[0]+radius*sinf(0),center[1],center[2]+radius*cosf(0));
		glEnd();
	glBegin(GL_LINE_STRIP);
		glColor3f(yColor[0],yColor[1],yColor[2]);
		glVertexAttrib3f(5,yColor[0],yColor[1],yColor[2]);
		for(int i=0;i<100;i++){
			glVertex3f(center[0]+radius*sinf(i/50.0*PI),center[1],center[2]+radius*cosf(i/50.0*PI));
		}
		glVertex3f(center[0],center[1]+radius*sinf(0),center[2]+radius*cosf(0));
	glEnd();
	glBegin(GL_LINE_STRIP);
		glColor3f(zColor[0],zColor[1],zColor[2]);
		glVertexAttrib3f(5,zColor[0],zColor[1],zColor[2]);
		for(int i=0;i<100;i++){
			glVertex3f(center[0]+radius*cosf(i/50.0*PI),center[1]+radius*sinf(i/50.0*PI),center[2]);
		}
		glVertex3f(center[0]+radius*cosf(0),center[1]+radius*sinf(0),center[2]);
	glEnd();

	glPopMatrix();
}

void Transformer::draw(QString *sActor, bool selection)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE3);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE4);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);

	float white[] = {1.0,1.0,1.0};
	float black[] = {0,0,0};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,white);
	glMaterialfv(GL_FRONT,GL_AMBIENT,white);
	glMaterialfv(GL_FRONT,GL_EMISSION,black);

	glVertexAttrib3f(2,0.0,0.0,0.0);
	glVertexAttrib3f(3,0.0,0.0,0.0);
	glVertexAttrib3f(4,0.0,0.0,0.0);

	float xColor[3];
	float yColor[3];
	float zColor[3];
	if (!selection) {
		xColor[0]=1.0;xColor[1]=0.0;xColor[2]=0.0;
		yColor[0]=0.0;yColor[1]=1.0;yColor[2]=0.0;
		zColor[0]=0.0;zColor[1]=0.0;zColor[2]=1.0;
		switch (selected) {
			case 0: xColor[1]=1.0; break;
			case 1: yColor[0]=1.0; break;
			case 2: zColor[0]=1.0; zColor[1]=1.0; zColor[2]=0.0; break;
		}
	} else {
		getColorFromID(100000,xColor);
		getColorFromID(100001,yColor);
		getColorFromID(100002,zColor);
	}
	drawTranslator(sActor,xColor,yColor,zColor,selection);
	drawBoundingBox(sActor);
	if (!selection) {
		xColor[0]=1.0;xColor[1]=0.0;xColor[2]=0.0;
		yColor[0]=0.0;yColor[1]=1.0;yColor[2]=0.0;
		zColor[0]=0.0;zColor[1]=0.0;zColor[2]=1.0;
		switch (selected) {
			case 3: xColor[1]=1.0; break;
			case 4: yColor[0]=1.0; break;
			case 5: zColor[0]=1.0; zColor[1]=1.0; zColor[2]=0.0; break;
		}
	} else {
		getColorFromID(100003,xColor);
		getColorFromID(100004,yColor);
		getColorFromID(100005,zColor);
	}
	drawRotator(sActor,xColor,yColor,zColor,selection);
	glPopMatrix();
	glVertexAttrib3f(5,1.0,1.0,1.0);
}

void Transformer::calculateTransform(int mouseX, int mouseY, bool shift, bool ctrl)
{
	QString *sActor = ArgoSceneManager::Instance()->getSelected();
	if (sActor == 0 || selected == -1) {
		dragPoint = ArgoVector3(0,0,0);
		return;
	}

	ArgoActor *actor = ArgoSceneManager::Instance()->getActor(*sActor);
	ArgoVector3 unProjLine[2];
	ArgoVector3 dragLine[2];

	float *center = actor->getTranslate();
	
	unProjLine[0] = getUnproject(0,mouseX,mouseY);
	unProjLine[1] = getUnproject(1,mouseX,mouseY)-unProjLine[0];
	dragLine[0] = ArgoVector3(center[0],center[1],center[2]);

	if (selected<3) {
		switch (selected) {
			case 0: dragLine[1] = ArgoVector3(1.0,0.0,0.0); break;
			case 1: dragLine[1] = ArgoVector3(0.0,1.0,0.0); break;
			case 2: dragLine[1] = ArgoVector3(0.0,0.0,1.0); break;
			default: return;
		}

		ArgoVector3 newDragPoint = getDragPoint(dragLine,unProjLine);
		ArgoVector3 translate = newDragPoint-dragPoint;

		if (dragPoint.length() > 0.0001){
			if (ctrl) {
				float scale = (translate[0]+translate[1]+translate[2])/2.0;
				actor->Scale(scale,scale,scale);
			} else if (shift) {
				translate = translate * 0.5;
				actor->Scale(translate[0],translate[1],translate[2]);
			} else {
				actor->Translate(translate[0],translate[1],translate[2]);
			}
		}
		dragPoint=newDragPoint;
	} else {
		float newAngle;
		float angleChange;
		ArgoVector3 normal;
		ArgoVector3 tangent;

		switch (selected) {
			case 3: normal = ArgoVector3(1.0,0.0,0.0); tangent = ArgoVector3(0,0,1); break;
			case 4: normal = ArgoVector3(0.0,1.0,0.0); tangent = ArgoVector3(0,0,1); break;
			case 5: normal = ArgoVector3(0.0,0.0,1.0); tangent = ArgoVector3(1,0,0); break;
			default: return;
		}
		
		ArgoVector3 vcenter=ArgoVector3(center[0],center[1],center[2]);
		unProjLine[0]-=vcenter;
		newAngle = getRotAngle(unProjLine,&normal,&tangent);

		angleChange=newAngle-lastAngle;
		if (lastAngle==0){
			angleChange=0;
		}
		lastAngle = newAngle;

		ArgoQuaternion quat;
		quat.createQuaternion(angleChange,normal[0],normal[1],normal[2]);
		actor->Rotate(quat);
	}
}

