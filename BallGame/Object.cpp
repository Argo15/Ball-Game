#include "Object.h"

float Object::getScaledRadius(ModelRegistry *models)
{
	return models->getModel(model)->getRadius()*max(max(scale[0],scale[1]),scale[2]);
}

void Object::transform()
{
	btTransform trans;
	body->getMotionState()->getWorldTransform(trans);
	float mat[16];
	trans.getOpenGLMatrix(mat);
	glMultMatrixf(mat);
	rotation.getMatrix().multiplyToCurrent();
	glScalef(scale[0],scale[1],scale[2]);

	glMatrixMode(GL_TEXTURE);
		glActiveTextureARB(GL_TEXTURE7);
		glLoadIdentity();
		glMultMatrixf(mat);
		rotation.getMatrix().multiplyToCurrent();
	glMatrixMode(GL_MODELVIEW);
}