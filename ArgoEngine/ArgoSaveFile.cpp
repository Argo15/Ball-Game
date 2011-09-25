#include "ArgoSaveFile.h"
#include "Default.h"

void ArgoSaveFile::createSaveFromScene()
{
	int i;

	QMap<QString,ArgoTexture *> *texMap = ArgoTextureManager::Instance()->getTextures();
	QMap<QString, ArgoTexture *>::iterator itex;
	numTextures = texMap->size();
	textures = new SaveTexture[numTextures];
	i=0;
	for (itex = texMap->begin(); itex != texMap->end(); ++itex){
		ArgoTexture *texture = itex.value();
		strcpy(textures[i].location,qPrintable(texture->getLocation()));
		strcpy(textures[i].name,qPrintable(*texture->getName()));
		strcpy(textures[i].type,qPrintable(texture->getType()));
		i++;
	}
	strcpy(whiteTexture,qPrintable(*ArgoTextureManager::Instance()->getWhite()->getName()));

	QMap<QString,ArgoMaterial *> *matMap = ArgoMaterialManager::Instance()->getMaterials();
	QMap<QString, ArgoMaterial *>::iterator imat;
	numMaterials = matMap->size();
	materials = new SaveMaterial[numMaterials];
	i=0;
	for (imat = matMap->begin(); imat != matMap->end(); ++imat){
		ArgoMaterial *material = imat.value();
		strcpy(materials[i].name,qPrintable(*material->getName()));
		strcpy(materials[i].texture,qPrintable(*material->getTexture()));
		strcpy(materials[i].normal,qPrintable(*material->getNormal()));
		materials[i].color[0] = material->getColor()[0];
		materials[i].color[1] = material->getColor()[1];
		materials[i].color[2] = material->getColor()[2];
		materials[i].emission[0] = material->getEmission()[0];
		materials[i].emission[1] = material->getEmission()[1];
		materials[i].emission[2] = material->getEmission()[2];
		materials[i].shininess = material->getShine();
		materials[i].specular = material->getSpecular();
		materials[i].texOffset[0] = material->getTexOffset()[0];
		materials[i].texOffset[1] = material->getTexOffset()[1];
		materials[i].texRotate = material->getTexRotate();
		materials[i].texScale[0] = material->getTexScale()[0];
		materials[i].texScale[1] = material->getTexScale()[1];
		materials[i].normalEnabled = material->normalsEnabled();
		i++;
	}
	strcpy(defaultMaterial,qPrintable(*ArgoMaterialManager::Instance()->getDefault()->getName()));
	strcpy(lightMaterial,qPrintable(*ArgoMaterialManager::Instance()->getLightMaterial()->getName()));


	QMap<QString,ArgoModel *> *modelMap = ArgoModelManager::Instance()->getModels();
	QMap<QString, ArgoModel *>::iterator imodel;
	numModels = modelMap->size();
	models = new SaveModel[numModels];
	i=0;
	for (imodel = modelMap->begin(); imodel != modelMap->end(); ++imodel){
		ArgoModel *model = imodel.value();
		strcpy(models[i].name,qPrintable(*model->getName()));
		strcpy(models[i].location,qPrintable(model->getLocation()));
		i++;
	}
	strcpy(defaultModel,qPrintable(*ArgoModelManager::Instance()->getDefault()->getName()));
	strcpy(pointLightModel,qPrintable(*ArgoModelManager::Instance()->getPointLightModel()->getName()));
	strcpy(directLightModel,qPrintable(*ArgoModelManager::Instance()->getDirectLightModel()->getName()));

	QMap<QString,ArgoObject *> *objectMap = ArgoSceneManager::Instance()->getObjects();
	QMap<QString,ArgoObject *>::iterator iobject;
	numObjects = objectMap->size();
	numRigidBodies=numObjects;
	objects = new SaveObject[numObjects];
	bodies = new SaveRigidBody[numObjects];
	i=0;
	for (iobject = objectMap->begin(); iobject != objectMap->end(); ++iobject) {
		ArgoObject *object = iobject.value();
		strcpy(objects[i].name,qPrintable(*object->getName()));
		strcpy(objects[i].material,qPrintable(*object->getMaterial()));
		strcpy(objects[i].model,qPrintable(*object->getModel()));
		objects[i].rotation[0] = object->getRotate()[0];
		objects[i].rotation[1] = object->getRotate()[1];
		objects[i].rotation[2] = object->getRotate()[2];
		objects[i].rotation[3] = object->getRotate()[3];
		objects[i].scale[0] = object->getScale()[0];
		objects[i].scale[1] = object->getScale()[1];
		objects[i].scale[2] = object->getScale()[2];
		objects[i].translation[0] = object->getTranslate()[0];
		objects[i].translation[1] = object->getTranslate()[1];
		objects[i].translation[2] = object->getTranslate()[2];
		object->createRigidBody();
		bodies[i].type = object->getRigidBody().type;
		bodies[i].numTriangles = object->getRigidBody().numTriangles;
		bodies[i].triangles = object->getRigidBody().triangles;
		i++;
	}

	ArgoDirectLight *directLight = ArgoSceneManager::Instance()->getDirectLight();
	strcpy(dLight.name,qPrintable(*directLight->getName()));
	dLight.rotation[0] = directLight->getRotate()[0];
	dLight.rotation[1] = directLight->getRotate()[1];
	dLight.rotation[2] = directLight->getRotate()[2];
	dLight.rotation[3] = directLight->getRotate()[3];
	dLight.scale[0] = directLight->getScale()[0];
	dLight.scale[1] = directLight->getScale()[1];
	dLight.scale[2] = directLight->getScale()[2];
	dLight.translation[0] = directLight->getTranslate()[0];
	dLight.translation[1] = directLight->getTranslate()[1];
	dLight.translation[2] = directLight->getTranslate()[2];
	dLight.color[0] = directLight->getColor()[0];
	dLight.color[1] = directLight->getColor()[1];
	dLight.color[2] = directLight->getColor()[2];
	dLight.ambient = directLight->getAmbient();
	dLight.diffuse = directLight->getDiffuse();
	dLight.specular = directLight->getSpecular();
	dLight.enabled = directLight->isenabled();

	QMap<QString,ArgoPointLight *> *pLightMap = ArgoSceneManager::Instance()->getPointLights();
	QMap<QString,ArgoPointLight *>::iterator ilight;
	numPointLights = pLightMap->size();
	pLights = new SavePointLight[numPointLights];
	i=0;
	for (ilight = pLightMap->begin(); ilight != pLightMap->end(); ++ilight) {
		ArgoPointLight *pointLight = ilight.value();
		strcpy(pLights[i].name,qPrintable(*pointLight->getName()));
		pLights[i].rotation[0] = pointLight->getRotate()[0];
		pLights[i].rotation[1] = pointLight->getRotate()[1];
		pLights[i].rotation[2] = pointLight->getRotate()[2];
		pLights[i].rotation[3] = pointLight->getRotate()[3];
		pLights[i].scale[0] = pointLight->getScale()[0];
		pLights[i].scale[1] = pointLight->getScale()[1];
		pLights[i].scale[2] = pointLight->getScale()[2];
		pLights[i].translation[0] = pointLight->getTranslate()[0];
		pLights[i].translation[1] = pointLight->getTranslate()[1];
		pLights[i].translation[2] = pointLight->getTranslate()[2];
		pLights[i].color[0] = pointLight->getColor()[0];
		pLights[i].color[1] = pointLight->getColor()[1];
		pLights[i].color[2] = pointLight->getColor()[2];
		pLights[i].ambient = pointLight->getAmbient();
		pLights[i].diffuse = pointLight->getDiffuse();
		pLights[i].specular = pointLight->getSpecular();
		pLights[i].attenuation = pointLight->getAttenuation();
		pLights[i].radius = pointLight->getRadius();
		pLights[i].enabled = pointLight->isenabled();
		i++;
	}

	ArgoPort *ent = ArgoSceneManager::Instance()->getEntrance();
	entrance.type = ent->getType();
	strcpy(entrance.object.name,qPrintable(*ent->getName()));
	strcpy(entrance.object.material,qPrintable(*ent->getMaterial()));
	strcpy(entrance.object.model,qPrintable(*ent->getModel()));
	entrance.object.rotation[0] = ent->getRotate()[0];
	entrance.object.rotation[1] = ent->getRotate()[1];
	entrance.object.rotation[2] = ent->getRotate()[2];
	entrance.object.rotation[3] = ent->getRotate()[3];
	entrance.object.scale[0] = ent->getScale()[0];
	entrance.object.scale[1] = ent->getScale()[1];
	entrance.object.scale[2] = ent->getScale()[2];
	entrance.object.translation[0] = ent->getTranslate()[0];
	entrance.object.translation[1] = ent->getTranslate()[1];
	entrance.object.translation[2] = ent->getTranslate()[2];

	ArgoPort *ex = ArgoSceneManager::Instance()->getExit();
	exit.type = ex->getType();
	strcpy(exit.object.name,qPrintable(*ex->getName()));
	strcpy(exit.object.material,qPrintable(*ex->getMaterial()));
	strcpy(exit.object.model,qPrintable(*ex->getModel()));
	exit.object.rotation[0] = ex->getRotate()[0];
	exit.object.rotation[1] = ex->getRotate()[1];
	exit.object.rotation[2] = ex->getRotate()[2];
	exit.object.rotation[3] = ex->getRotate()[3];
	exit.object.scale[0] = ex->getScale()[0];
	exit.object.scale[1] = ex->getScale()[1];
	exit.object.scale[2] = ex->getScale()[2];
	exit.object.translation[0] = ex->getTranslate()[0];
	exit.object.translation[1] = ex->getTranslate()[1];
	exit.object.translation[2] = ex->getTranslate()[2];
}

void ArgoSaveFile::createSceneFromSave(float version)
{
	for (int i=0 ; i<numTextures; i++){
		ArgoTextureManager::Instance()->LoadTexture(QString(textures[i].location),QString(textures[i].name));
		ArgoTextureManager::Instance()->getTexture(textures[i].name)->setType(textures[i].type);
	}
	ArgoTextureManager::Instance()->SetWhite(ArgoTextureManager::Instance()->getTexture(QString(whiteTexture))->getName());

	for (int i=0; i<numMaterials; i++){
		ArgoMaterial *material = new ArgoMaterial(new QString(materials[i].name));
		material->setTexture(ArgoTextureManager::Instance()->getTexture(QString(materials[i].texture))->getName());
		material->setNormal(ArgoTextureManager::Instance()->getTexture(QString(materials[i].normal))->getName());
		material->setColor(materials[i].color[0],materials[i].color[1],materials[i].color[2]);
		material->setEmission(materials[i].emission[0],materials[i].emission[1],materials[i].emission[2]);
		material->setSpecular(materials[i].specular);
		material->setShine(materials[i].shininess);
		material->setTexOffset(materials[i].texOffset[0],materials[i].texOffset[1]);
		material->setTexRotate(materials[i].texRotate);
		material->setTexScale(materials[i].texScale[0],materials[i].texScale[1]);
		material->enableNormal(materials[i].normalEnabled);
		ArgoMaterialManager::Instance()->AddMaterial(material);
	}
	ArgoMaterialManager::Instance()->setDefault(ArgoMaterialManager::Instance()->getMaterial(QString(defaultMaterial))->getName());
	ArgoMaterialManager::Instance()->setLightMaterial(ArgoMaterialManager::Instance()->getMaterial(QString(lightMaterial))->getName());

	for (int i=0; i<numModels; i++){
		ArgoModelManager::Instance()->LoadModel(QString(models[i].location),QString(models[i].name));
	}
	ArgoModelManager::Instance()->setDefault(ArgoModelManager::Instance()->getModel(QString(defaultModel))->getName());
	ArgoModelManager::Instance()->setPointLightModel(ArgoModelManager::Instance()->getModel(QString(pointLightModel))->getName());
	ArgoModelManager::Instance()->setDirectLightModel(ArgoModelManager::Instance()->getModel(QString(directLightModel))->getName());

	for (int i=0; i<numObjects; i++){
		ArgoObject *object = new ArgoObject(new QString(objects[i].name),
			ArgoModelManager::Instance()->getModel(QString(objects[i].model))->getName(),
			ArgoMaterialManager::Instance()->getMaterial(QString(objects[i].material))->getName());
		object->setTranslate(objects[i].translation[0],objects[i].translation[1],objects[i].translation[2]);
		object->setRotate(ArgoQuaternion(objects[i].rotation[0],objects[i].rotation[1],objects[i].rotation[2],objects[i].rotation[3]));
		object->setScale(objects[i].scale[0],objects[i].scale[1],objects[i].scale[2]);
		ArgoSceneManager::Instance()->AddObject(object);
	}

	ArgoDirectLight *directLight = new ArgoDirectLight(new QString(dLight.name));
	directLight->setMaterial(ArgoMaterialManager::Instance()->getLightMaterial()->getName());
	directLight->setModel(ArgoModelManager::Instance()->getDirectLightModel()->getName());
	directLight->setTranslate(dLight.translation[0],dLight.translation[1],dLight.translation[2]);
	directLight->setRotate(ArgoQuaternion(dLight.rotation[0],dLight.rotation[1],dLight.rotation[2],dLight.rotation[3]));
	directLight->setScale(dLight.scale[0],dLight.scale[1],dLight.scale[2]);
	directLight->setColor(dLight.color[0],dLight.color[1],dLight.color[2]);
	directLight->setAmbient(dLight.ambient);
	directLight->setDiffuse(dLight.diffuse);
	directLight->setSpecular(dLight.specular);
	directLight->setEnabled(dLight.enabled);
	ArgoSceneManager::Instance()->setDirectLight(directLight);

	for (int i=0; i<numPointLights; i++){
		ArgoPointLight *pointLight = new ArgoPointLight(new QString(pLights[i].name));
		pointLight->setMaterial(ArgoMaterialManager::Instance()->getLightMaterial()->getName());
		pointLight->setModel(ArgoModelManager::Instance()->getPointLightModel()->getName());
		pointLight->setTranslate(pLights[i].translation[0],pLights[i].translation[1],pLights[i].translation[2]);
		pointLight->setRotate(ArgoQuaternion(pLights[i].rotation[0],pLights[i].rotation[1],pLights[i].rotation[2],pLights[i].rotation[3]));
		pointLight->setScale(pLights[i].scale[0],pLights[i].scale[1],pLights[i].scale[2]);
		pointLight->setColor(pLights[i].color[0],pLights[i].color[1],pLights[i].color[2]);
		pointLight->setAmbient(pLights[i].ambient);
		pointLight->setDiffuse(pLights[i].diffuse);
		pointLight->setSpecular(pLights[i].specular);
		pointLight->setAttenuation(pLights[i].attenuation);
		pointLight->setRadius(pLights[i].radius);
		pointLight->setEnabled(pLights[i].enabled);
		ArgoSceneManager::Instance()->AddPointLight(pointLight);
	}

	if (version > 0.399) {
		ArgoPort *ent = new ArgoPort();
		ent->setType(entrance.type);
		ent->setName(new QString(entrance.object.name));
		ent->setMaterial(ArgoMaterialManager::Instance()->getMaterial(entrance.object.material)->getName());
		ent->setModel(ArgoModelManager::Instance()->getModel(entrance.object.model)->getName());
		ent->setTranslate(entrance.object.translation[0],entrance.object.translation[1],entrance.object.translation[2]);
		ent->setRotate(ArgoQuaternion(entrance.object.rotation[0],entrance.object.rotation[1],entrance.object.rotation[2],entrance.object.rotation[3]));
		ent->setScale(entrance.object.scale[0],entrance.object.scale[1],entrance.object.scale[2]);
		ArgoSceneManager::Instance()->setEntrance(ent);

		ArgoPort *ex = new ArgoPort();
		ex->setType(exit.type);
		ex->setName(new QString(exit.object.name));
		ex->setMaterial(ArgoMaterialManager::Instance()->getMaterial(exit.object.material)->getName());
		ex->setModel(ArgoModelManager::Instance()->getModel(exit.object.model)->getName());
		ex->setTranslate(exit.object.translation[0],exit.object.translation[1],exit.object.translation[2]);
		ex->setRotate(ArgoQuaternion(exit.object.rotation[0],exit.object.rotation[1],exit.object.rotation[2],exit.object.rotation[3]));
		ex->setScale(exit.object.scale[0],exit.object.scale[1],exit.object.scale[2]);
		ArgoSceneManager::Instance()->setExit(ex);
	} else {
		LoadDefaultPorts();
	}
}

void ArgoSaveFile::releaseSaveFile()
{
	delete [] textures;
	delete [] materials;
	delete [] models;
	delete [] objects;
	delete [] pLights;
}

void ArgoSaveFile::saveScene(const char *filename)
{
	createSaveFromScene();

	ofstream file(filename, ios::out|ios::binary|ios::ate);
	if (file.is_open())
	{ 
		float version = 0.5;
		file.write((char*)&version,sizeof(version));

		file.write((char*)&numTextures,sizeof(numTextures));
		file.write((char*)textures,sizeof(SaveTexture)*numTextures);
		file.write((char*)&whiteTexture,sizeof(whiteTexture));

		file.write((char*)&numMaterials,sizeof(numMaterials));
		file.write((char*)materials,sizeof(SaveMaterial)*numMaterials);
		file.write((char*)&defaultMaterial,sizeof(defaultMaterial));
		file.write((char*)&lightMaterial,sizeof(lightMaterial));

		file.write((char*)&numModels,sizeof(numModels));
		file.write((char*)models,sizeof(SaveModel)*numModels);
		file.write((char*)&defaultModel,sizeof(defaultModel));
		file.write((char*)&pointLightModel,sizeof(pointLightModel));
		file.write((char*)&directLightModel,sizeof(directLightModel));

		file.write((char*)&numObjects,sizeof(numObjects));
		file.write((char*)objects,sizeof(SaveObject)*numObjects);
		file.write((char*)&dLight,sizeof(dLight));
		file.write((char*)&numPointLights,sizeof(numPointLights));
		file.write((char*)pLights,sizeof(SavePointLight)*numPointLights);
		file.write((char*)&entrance,sizeof(SavePort));
		file.write((char*)&exit,sizeof(SavePort));

		for (int i=0; i<numRigidBodies; i++){
			file.write((char*)&bodies[i],sizeof(BodyType)+sizeof(int)+sizeof(float)*9.0*bodies[i].numTriangles);
		}

		file.close();
	}

	releaseSaveFile();
}

void ArgoSaveFile::openScene(const char *filename)
{
	ifstream file(filename, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
		float version;
		file.seekg (0, ios::beg);
		file.read((char *)&version, sizeof(version));

		if (version > 0.299) {
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
		}
		if (version > 0.399) {
			file.read((char*)&entrance,sizeof(SavePort));
			file.read((char*)&exit,sizeof(SavePort));
		}
		file.close();
		createSceneFromSave(version);
		releaseSaveFile();
	}
}