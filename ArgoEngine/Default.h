#include "ArgoSceneManager.h"

static void LoadDefaultPorts()
{
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/Sphere.aobj");
	ArgoModelManager::Instance()->setPortModel(ArgoModelManager::Instance()->getModel("Sphere")->getName());

	ArgoMaterial *entranceMaterial = new ArgoMaterial(new QString("Entrance"));
	entranceMaterial->setTexture(ArgoTextureManager::Instance()->getWhite()->getName());
	entranceMaterial->setEmission(0.0,1.0,0.0);
	entranceMaterial->setColor(0.0,1.0,0.0);
	ArgoMaterial *exitMaterial = new ArgoMaterial(new QString("Exit"));
	exitMaterial->setTexture(ArgoTextureManager::Instance()->getWhite()->getName());
	exitMaterial->setEmission(1.0,0.0,0.0);
	exitMaterial->setColor(1.0,0.0,0.0);
	ArgoMaterialManager::Instance()->AddMaterial(entranceMaterial);
	ArgoMaterialManager::Instance()->AddMaterial(exitMaterial);
	ArgoMaterialManager::Instance()->setEntranceMaterial(entranceMaterial->getName());
	ArgoMaterialManager::Instance()->setExitMaterial(exitMaterial->getName());

	ArgoPort *entranceActor = new ArgoPort(ENTRANCE);
	entranceActor->setName("Start");
	entranceActor->Translate(0.0,0.25,0.0);
	ArgoPort *exitActor = new ArgoPort(EXIT);
	exitActor->setName("Exit");
	exitActor->Translate(0.0,0.25,-2.0);
	ArgoSceneManager::Instance()->setEntrance(entranceActor);
	ArgoSceneManager::Instance()->setExit(exitActor);
}

static void LoadDefaultScene()
{
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/White.tga");
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/Black.tga");
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/Brick Wall.tga");
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/Grass.tga");
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/Apple.tga");
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/Beach Ball.tga");
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/Stone.tga");
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/Wood Floorboard.tga");
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/Test Normals.tga");
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/Concrete.tga");
	ArgoTextureManager::Instance()->LoadTexture("Data/Textures/TGA/Concrete Normal.tga");
	ArgoTextureManager::Instance()->SetWhite(ArgoTextureManager::Instance()->getTexture("White")->getName());
	ArgoTextureManager::Instance()->getTexture("Concrete Normal")->setType("Normal");
	ArgoTextureManager::Instance()->getTexture("Test Normals")->setType("Normal");

	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/Cube.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/Bunny.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/Torus.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/Apple.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/Cone.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/Cylinder.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/TorusKnot.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/Plane.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/smoothdragon.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/smoothbuddha.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/Armadillo.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/Light/DirectLight.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/Light/PointLight.aobj");
	ArgoModelManager::Instance()->setDefault(ArgoModelManager::Instance()->getModel("Cube")->getName());
	ArgoModelManager::Instance()->setPointLightModel(ArgoModelManager::Instance()->getModel("PointLight")->getName());
	ArgoModelManager::Instance()->setDirectLightModel(ArgoModelManager::Instance()->getModel("DirectLight")->getName());

	ArgoMaterial *defaultMaterial = new ArgoMaterial(new QString("Default"));
	defaultMaterial->setTexture(ArgoTextureManager::Instance()->getTexture("White")->getName());
	ArgoMaterial *lightMaterial = new ArgoMaterial(new QString("Light"));
	lightMaterial->setTexture(ArgoTextureManager::Instance()->getTexture("White")->getName());
	lightMaterial->setEmission(1.0,1.0,1.0);
	ArgoMaterialManager::Instance()->AddMaterial(defaultMaterial);
	ArgoMaterialManager::Instance()->AddMaterial(lightMaterial);
	ArgoMaterialManager::Instance()->setDefault(defaultMaterial->getName());
	ArgoMaterialManager::Instance()->setLightMaterial(lightMaterial->getName());

	QString *dLightStr = new QString("Direct Light");
	ArgoDirectLight *dLight = new ArgoDirectLight(dLightStr);
	dLight->setMaterial(lightMaterial->getName());
	dLight->setModel(ArgoModelManager::Instance()->getModel("DirectLight")->getName());
	dLight->setTranslate(0.0,1.3,0.0);
	dLight->setScale(0.2,0.4,0.2);
	ArgoSceneManager::Instance()->setDirectLight(dLight);

	LoadDefaultPorts();
}