#include "Object.h"

float Object::getScaledRadius(ModelRegistry *models)
{
	return models->getModel(model)->getRadius()*max(max(scale[0],scale[1]),scale[2]);
}

void Object::transform()
{
	glTranslatef(translations[0],translations[1],translations[2]);
	rotation.getMatrix().multiplyToCurrent();
	glScalef(scale[0],scale[1],scale[2]);
}