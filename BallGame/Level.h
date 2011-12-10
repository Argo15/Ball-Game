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
#include "PointLight.h"
#include "Frustum.h"
#include "Profiler.h"
#include "EnvironmentMap.h"
#include "BallMaterial.h"
#include "Globals.h"
using namespace std;

class PointLight;
class EnvironmentMap;

class Level {
private: 
	TextureRegistry *textures;
	MaterialRegistry *materials;
	ModelRegistry *models;
	int numObjects;
	map<string,Object *> objects;
	DirectLight *dLight;
	map<string, PointLight *> pLights;

	Model *myBall;
	Texture *ballTexs[10];
	Texture *ballNormals[10];
	float ballColors[10][3];

	btRigidBody* ballBody;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btVector3 gravity;
	btVector3 start, end;
	bool canJump;

	bool toggleGravity;

	EnvironmentMap *ballReflection;

	float lastMat[16];

public:
	Level();
	~Level();

	TextureRegistry *getTextures() {return textures;}
	MaterialRegistry *getMaterials() {return materials;}
	ModelRegistry *getModels() {return models;}

	map<string,Object *> *getObjects() {return &objects;}
	Object *getObject(string name) {return objects[name];}
	void setObject(string name, Object *newObject) {objects[name]=newObject;}

	void setDirectLight(DirectLight *light) {dLight=light;}
	DirectLight *getDirectLight() {return dLight;}

	map<string,PointLight *> *getPointLights() {return &pLights;}
	PointLight *getPointLight(string name) {return pLights[name];}
	int getBestPointLights(PointLight **bestLights, Frustum *frustum, Camera *camera, int count);
	int getAllPointLights(PointLight **lights);
	void setPointLight(string name, PointLight *newpLight) {pLights[name]=newpLight;}

	void setNumObjects(int count) {numObjects = count;}
	void buildDynamicsWorld();
	void updateDynamicsWorld(bool *keys, Camera *camera, int fps, Profiler *profiler);

	void setStart(float *entrance) {start = btVector3(entrance[0],entrance[1],entrance[2]);}
	void setEnd(float *end) {this->end = btVector3(end[0],end[1],end[2]);}

	btRigidBody *getBallBody() {return ballBody;}

	float distanceFromEnd();

	void drawNoShaders(Frustum *frustum);
	void drawNoBall(Frustum *frustum);
	void draw(GLSLProgram *program, Frustum *frustum);
	void drawPointShadows(Frustum *frustum);
	void drawBall(GLSLProgram *program, Frustum *frustum);

	void setToggleGravity(bool val) {toggleGravity = val;}

	void getLastTransforms();

	btVector3* getStart();
	btVector3* getEnd();
};

#endif