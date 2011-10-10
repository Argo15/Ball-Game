#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include "MaterialRegistry.h"
#include "ModelRegistry.h"
#include "Object.h"
#include "btBulletDynamicsCommon.h"
#include "Camera.h"
using namespace std;

class Level {
private: 
	TextureRegistry *textures;
	MaterialRegistry *materials;
	ModelRegistry *models;
	int numObjects;
	map<string,Object *> objects;

	Model *myBall;
	Texture *ballTex;

	btRigidBody* ballBody;
	btDiscreteDynamicsWorld* dynamicsWorld;

public:
	Level();
	~Level() {}

	TextureRegistry *getTextures() {return textures;}
	MaterialRegistry *getMaterials() {return materials;}
	ModelRegistry *getModels() {return models;}

	map<string,Object *> getObjects() {return objects;}
	Object *getObject(string name) {return objects[name];}
	void setObject(string name, Object *newObject) {objects[name]=newObject;}

	void setNumObjects(int count) {numObjects = count;}
	void buildDynamicsWorld();
	void updateDynamicsWorld(bool *keys, Camera *camera, int fps);

	void drawNoShaders();
};

#endif