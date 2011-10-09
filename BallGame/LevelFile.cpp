#include "LevelFile.h"

void LevelFile::loadFile(const char *filename)
{
	ifstream file(filename, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
		float version;
		file.seekg (0, ios::beg);
		file.read((char *)&version, sizeof(version));

		file.read((char*)&numTextures,sizeof(numTextures));
		textures = new SaveTexture[numTextures];
		file.read((char*)textures,sizeof(SaveTexture)*numTextures);
		file.read((char*)&whiteTexture,sizeof(whiteTexture));

		file.read((char*)&numMaterials,sizeof(numMaterials));
		materials = new SaveMaterial[numMaterials];
		file.read((char*)materials,sizeof(SaveMaterial)*numMaterials);
		file.read((char*)&defaultMaterial,sizeof(defaultMaterial));
		file.read((char*)&lightMaterial,sizeof(lightMaterial));

		file.read((char*)&numModels,sizeof(numModels));
		models = new SaveModel[numModels];
		file.read((char*)models,sizeof(SaveModel)*numModels);
		file.read((char*)&defaultModel,sizeof(defaultModel));
		file.read((char*)&pointLightModel,sizeof(pointLightModel));
		file.read((char*)&directLightModel,sizeof(directLightModel));

		file.read((char*)&numObjects,sizeof(numObjects));
		objects = new SaveObject[numObjects];
		file.read((char*)objects,sizeof(SaveObject)*numObjects);
		file.read((char*)&dLight,sizeof(dLight));
		file.read((char*)&numPointLights,sizeof(numPointLights));
		pLights = new SavePointLight[numPointLights];
		file.read((char*)pLights,sizeof(SavePointLight)*numPointLights);			

		file.read((char*)&entrance,sizeof(SavePort));
		file.read((char*)&exit,sizeof(SavePort));

		file.read((char*)&numRigidBodies,sizeof(numRigidBodies));
		bodies = new SaveRigidBody[numRigidBodies];
		for (int i=0; i<numRigidBodies; i++){
			file.read((char*)&bodies[i].objectName[0],sizeof(char)*100);
			file.read((char*)&bodies[i].numTriangles,sizeof(int));
			bodies[i].triangles = new float[9*bodies[i].numTriangles];
			file.read((char*)&bodies[i].triangles[0],sizeof(float)*9*bodies[i].numTriangles);
		}

		file.close();
	}
}

void LevelFile::initializeLevel(Level *level) {
	TextureRegistry *texReg = level->getTextures();
	MaterialRegistry *matReg = level->getMaterials();
	ModelRegistry *modelReg = level->getModels();

	for (int i=0; i<numTextures; i++) {
		Texture *texture = new Texture();
		texture->load(textures[i].location);
		texReg->addTexture(textures[i].name,texture);
	}

	for (int i=0; i<numMaterials; i++) {
		Material *material = new Material();
		material->setTexture(materials[i].texture);
		material->setNormal(materials[i].normal);
		material->setColor(materials[i].color[0],materials[i].color[1],materials[i].color[2]);
		material->setEmission(materials[i].emission[0],materials[i].emission[1],materials[i].emission[2]);
		material->setSpecular(materials[i].specular);
		material->setShine(materials[i].shininess);
		material->setTexOffset(materials[i].texOffset[0],materials[i].texOffset[1]);
		material->setTexRotate(materials[i].texRotate);
		material->setTexScale(materials[i].texScale[0],materials[i].texScale[1]);
		material->setNormalEnabled(materials[i].normalEnabled);
		matReg->addMaterial(materials[i].name, material);
	}

	for (int i=0; i<numModels; i++){
		Model *model = new Model();
		model->load(models[i].location);
		modelReg->addModel(models[i].name, model);
	}

	level->setNumObjects(numObjects);

	for (int i=0; i<numObjects; i++){
		Object *newObject = new Object();
		newObject->setModel(objects[i].model);
		newObject->setMaterial(objects[i].material);
		newObject->setTranslate(objects[i].translation[0],objects[i].translation[1],objects[i].translation[2]);
		newObject->setRotate(ArgoQuaternion(objects[i].rotation[0],objects[i].rotation[1],objects[i].rotation[2],objects[i].rotation[3]));
		newObject->setScale(objects[i].scale[0],objects[i].scale[1],objects[i].scale[2]);
		level->setObject(objects[i].name, newObject);
	}

	for (int i=0; i<numRigidBodies; i++) {
		btTriangleMesh *mesh = new btTriangleMesh();
		for (int j =0; j<bodies[i].numTriangles*9; j+=9) {
			mesh->addTriangle(
				btVector3(bodies[i].triangles[j],bodies[i].triangles[j+1],bodies[i].triangles[j+2]),
				btVector3(bodies[i].triangles[j+3],bodies[i].triangles[j+4],bodies[i].triangles[j+5]),
				btVector3(bodies[i].triangles[j+6],bodies[i].triangles[j+7],bodies[i].triangles[j+8])
			);
		}
		mesh->addTriangle(btVector3(0,0,0),btVector3(0,0,0),btVector3(0,0,0));
		btCollisionShape* bodyShape = new btBvhTriangleMeshShape(mesh,true);
		btTransform bodyTransform;
		bodyTransform.setIdentity();
		ArgoVector3 org = level->getObject(bodies[i].objectName)->getTranslateV();
		bodyTransform.setOrigin(btVector3(org[0],org[1],org[2]));
		btScalar mass(0.);
		btVector3 localInertia(0,0,0);
		btDefaultMotionState* myMotionState = new btDefaultMotionState(bodyTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,bodyShape,localInertia);
		btRigidBody *newBody = new btRigidBody(rbInfo);

		level->getObject(bodies[i].objectName)->setRigidBody(newBody);
	}
}