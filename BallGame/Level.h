#ifndef LEVEL_H
#define LEVEL_H

#include "MaterialRegistry.h"
#include "ModelRegistry.h"
#include "Object.h"

class Level {
private: 
	TextureRegistry *textures;
	MaterialRegistry *materials;
	ModelRegistry *models;
	int numObjects;
	Object **objects;

public:
	Level();
	~Level() {}

	TextureRegistry *getTextures() {return textures;}
	MaterialRegistry *getMaterials() {return materials;}
	ModelRegistry *getModels() {return models;}

	Object **getObjects() {return objects;}
	void setObjects(Object **objs) {objects=objs;}

	void setNumObjects(int count) {numObjects = count;}

	void drawNoShaders();
};

#endif