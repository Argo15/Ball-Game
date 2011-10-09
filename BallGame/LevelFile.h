#ifndef LEVELFILE_H
#define LEVELFILE_H

#include <iostream>
#include <fstream>
#include "Level.h"
#include "btBulletDynamicsCommon.h"
#include "ArgoMatrix.h"
using namespace std;

enum PortType { ENTRANCE, EXIT };
enum BodyType { STATIC, KINEMATIC, DYNAMIC };

struct SaveTexture 
{
	char name[100];
	char location[500];
	char type[100];
};

struct SaveMaterial
{
	float color[3];
	float emission[3];
	float specular;
	int shininess;

	float texOffset[2];
	float texScale[2];
	float texRotate;

	char name[100];
	char texture[100];
	char normal[100];

	bool normalEnabled;
};

struct SaveModel
{
	char name[100];
	char location[500];
};

struct SaveObject
{
	char name[100];
	char model[100];
	char material[100];

	float translation[3];
	float rotation[4];
	float scale[3];

	BodyType type;
};

struct SaveDirectLight
{
	char name[100];

	float translation[3];
	float rotation[4];
	float scale[3];

	float color[3];
	float ambient;
	float diffuse;
	float specular;

	bool enabled;
};

struct SavePointLight
{
	char name[100];

	float translation[3];
	float rotation[4];
	float scale[3];

	float color[3];
	float ambient;
	float diffuse;
	float specular;

	float attenuation;
	float radius;

	bool enabled;
};

struct SavePort
{
	PortType type;
	SaveObject object;
};

struct SaveRigidBody
{
	char objectName[100];

	int numTriangles;
	float *triangles;
};

class LevelFile 
{
private: 
	int numTextures;
	SaveTexture *textures;
	char whiteTexture[100];

	int numMaterials;
	SaveMaterial *materials;
	char defaultMaterial[100];
	char lightMaterial[100];

	int numModels;
	SaveModel *models;
	char defaultModel[100];
	char pointLightModel[100];
	char directLightModel[100];

	int numObjects;
	int numPointLights;
	SaveObject *objects;
	SaveDirectLight dLight;
	SavePointLight *pLights;
	SavePort entrance;
	SavePort exit;
	
	int numRigidBodies;
	SaveRigidBody *bodies;

public:
	LevelFile() {}
	~LevelFile() {}

	void loadFile(const char *filename);
	void initializeLevel(Level *level);
};

#endif