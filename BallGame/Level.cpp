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

	myBall = new Model();
	myBall->load("Data/Models/AOBJ/Sphere.aobj");
	ballTex = new Texture();
	ballTex->load("Data/Textures/TGA/Beach Ball.tga");
}

void Level::buildDynamicsWorld() {
	map<string,Object *>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++) {
			dynamicsWorld->addRigidBody(i->second->getRigidBody());
	}

	btCollisionShape* colShape = new btSphereShape(btScalar(0.25));
	btTransform startTransform;
	startTransform.setIdentity();
	btScalar mass(10.f);
	btVector3 localInertia(0,0,0);
	colShape->calculateLocalInertia(mass,localInertia);
	startTransform.setOrigin(btVector3(0,0.312359,1.21146));
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
	ballBody = new btRigidBody(rbInfo);
	ballBody->setFriction(btScalar(15.0));
	dynamicsWorld->addRigidBody(ballBody);
}

void Level::updateDynamicsWorld(bool *keys, Camera *camera, int fps) {
	ArgoVector3 dir = ArgoVector3(0);
	if (keys['w']) {
		dir = camera->getLookAt()-camera->geteyeV();
		dir.set(dir[0],0,dir[2]);
		dir.normalize();
		btVector3 velocity(dir[0],0,dir[2]);
		ballBody->activate(true);
		ballBody->applyCentralForce(velocity*100);
	}
	if (keys['s']) {
		dir = camera->geteyeV()-camera->getLookAt();
		dir.set(dir[0],0.01,dir[2]);
		dir.normalize();
		btVector3 velocity(dir[0],0,dir[2]);
		ballBody->activate(true);
		ballBody->applyCentralForce(velocity*100);
	}
	if (keys['d']) {
		dir = camera->getRight();
		dir.set(dir[0],0,dir[2]);
		dir.normalize();
		btVector3 velocity(dir[0],0,dir[2]);
		ballBody->activate(true);
		ballBody->applyCentralForce(velocity*100);
	}
	if (keys['a']) {
		dir = camera->getRight() * -1.0f;
		dir.set(dir[0],0,dir[2]);
		dir.normalize();
		btVector3 velocity(dir[0],0,dir[2]);
		ballBody->activate(true);
		ballBody->applyCentralForce(velocity*100);
	}
	dynamicsWorld->stepSimulation(1.f/60.f,10);

	btTransform trans;
	ballBody->getMotionState()->getWorldTransform(trans);
	camera->setLookAt(trans.getOrigin().getX(),trans.getOrigin().getY(),trans.getOrigin().getZ());
	camera->updateFromDistance();
}

void Level::drawNoShaders() {
	btTransform trans;
	ballBody->getMotionState()->getWorldTransform(trans);
	glPushMatrix();
		materials->getMaterial("Default")->useNoShaders(textures);
		ballTex->use();
		float mat[16];
		trans.getOpenGLMatrix(mat);
		glMultMatrixf(mat);
		glScalef(0.25,0.25,0.25);
		myBall->drawNoShaders();
	glPopMatrix();

	map<string,Object *>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++) {
		glPushMatrix();
			i->second->transform();
			materials->getMaterial(i->second->getMaterial())->useNoShaders(textures);
			models->getModel(i->second->getModel())->drawNoShaders();
		glPopMatrix();
	}
}