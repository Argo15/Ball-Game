#include "TestLevelOne.h"
#include "TestLevelTwo.h"
#include "Globals.h"

TestLevelOne::TestLevelOne() : LevelState(){
	levelFile = new LevelFile();
	levelFile->loadFile("Data/Saves/Test Level.ascn");
	level = new Level();
	levelFile->initializeLevel(level);
	angle = 0;
	position = -5.0;
	level->getObject("Cube Actor(4)")->getRigidBody()->setFriction(btScalar(20.0f));
	level->getObject("Cube Actor(5)")->getRigidBody()->setFriction(btScalar(20.0f));
	endDistance = 1.0;
	Globals::glowEnabled = true;
}

void TestLevelOne::update(int fps) {
	// Rotate body
	btRigidBody *rotatingBody = level->getObject("Cube Actor(5)")->getRigidBody();
	btTransform trans;
	rotatingBody->getMotionState()->getWorldTransform(trans);
	btQuaternion rot = trans.getRotation();
	rot.setRotation(btVector3(0.0,1.0,0.0),btScalar(angle));
	trans.setRotation(rot);
	rotatingBody->getMotionState()->setWorldTransform(trans);
	angle += 0.5f/(fps+0.01f);

	// Move Body
	btRigidBody *movingBody = level->getObject("Cube Actor(4)")->getRigidBody();
	movingBody->getMotionState()->getWorldTransform(trans);
	btVector3 org = trans.getOrigin();
	org.setZ(position);
	trans.setOrigin(org);
	movingBody->getMotionState()->setWorldTransform(trans);
	if (direction) {
		position-= 1.5f/fps;
		if (position < -9.0f) {
			position = -9.0f;
			direction = false;
		}
	} else {
		position+= 1.5f/fps;
		if (position > -5.0f) {
			position = -5.0f;
			direction = true;
		}
	}

	LevelState::update(fps);
}

void TestLevelOne::onFinish() {
	LevelState::onFinish();
	Globals::GAMESTATE = new TestLevelTwo();
	Globals::GAMESTATE->resize(width,height);
}