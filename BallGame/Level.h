#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include "MaterialRegistry.h"
#include "ModelRegistry.h"
#include "Object.h"
#include "btBulletDynamicsCommon.h"
#include "Camera.h"
#include "GLSLProgram.h"
#include "DirectLight.h"
using namespace std;

class Level {
private: 
	TextureRegistry *textures;
	MaterialRegistry *materials;
	ModelRegistry *models;
	int numObjects;
	map<string,Object *> objects;

	DirectLight *dLight;

	Model *myBall;
	Texture *ballTex;

	btRigidBody* ballBody;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btVector3 start, end;
	bool canJump;

public:
	Level();
	~Level() {}

	TextureRegistry *getTextures() {return textures;}
	MaterialRegistry *getMaterials() {return materials;}
	ModelRegistry *getModels() {return models;}

	map<string,Object *> getObjects() {return objects;}
	Object *getObject(string name) {return objects[name];}
	void setObject(string name, Object *newObject) {objects[name]=newObject;}

	void setDirectLight(DirectLight *light) {dLight=light;}
	DirectLight *getDirectLight() {return dLight;}

	void setNumObjects(int count) {numObjects = count;}
	void buildDynamicsWorld();
	void updateDynamicsWorld(bool *keys, Camera *camera, int fps);

	void setStart(float *entrance) {start = btVector3(entrance[0],entrance[1],entrance[2]);}
	void setEnd(float *end) {this->end = btVector3(end[0],end[1],end[2]);}

	btRigidBody *getBallBody() {return ballBody;}

	float distanceFromEnd();

	void drawNoShaders();
	void draw(GLSLProgram *program);
};

#endif