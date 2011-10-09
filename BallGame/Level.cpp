#include "Level.h"

Level::Level() {
	textures = new TextureRegistry();
	materials = new MaterialRegistry();
	models = new ModelRegistry();

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-10,0));
}

void Level::drawNoShaders() {
	map<string,Object *>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++) {
		glPushMatrix();
			i->second->transform();
			materials->getMaterial(i->second->getMaterial())->useNoShaders(textures);
			models->getModel(i->second->getModel())->drawNoShaders();
		glPopMatrix();
	}
}