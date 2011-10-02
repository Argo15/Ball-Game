#include "Level.h"

Level::Level() {
	textures = new TextureRegistry();
	materials = new MaterialRegistry();
	models = new ModelRegistry();
}

void Level::drawNoShaders() {
	for (int i=0; i<numObjects; i++) {
		glPushMatrix();
			objects[i]->transform();
			materials->getMaterial(objects[i]->getMaterial())->useNoShaders(textures);
			models->getModel(objects[i]->getModel())->drawNoShaders();
		glPopMatrix();
	}
}