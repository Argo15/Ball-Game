#include "TestLevelTwo.h"
#include "MainMenuState.h"
#include "Globals.h"

TestLevelTwo::TestLevelTwo() : LevelState(){
	levelFile = new LevelFile();
	levelFile->loadFile("Data/Saves/Test Level 2.ascn");
	level = new Level();
	levelFile->initializeLevel(level);
	endDistance = 1.0;
	angle = 0;
	position = 0;
	direction=false;
	level->getObject("SpinningThing Actor")->getRigidBody()->setFriction(btScalar(20.0f));
}

void TestLevelTwo::update(int fps) {
	btRigidBody *rotatingBody = level->getObject("SpinningThing Actor")->getRigidBody();
	btTransform trans;
	rotatingBody->getMotionState()->getWorldTransform(trans);
	btQuaternion rot = trans.getRotation();
	rot.setRotation(btVector3(0.0,0.0,1.0),btScalar(angle));
	trans.setRotation(rot);
	rotatingBody->getMotionState()->setWorldTransform(trans);
	angle += 0.5f/(fps+0.01f);

	btTransform ballTrans;
	level->getBallBody()->getMotionState()->getWorldTransform(ballTrans);
	btVector3 ballPos = ballTrans.getOrigin();
	direction = (ballPos.getZ() > -12);
	btRigidBody *movingBody = level->getObject("EndingPad Actor(3)")->getRigidBody();
	movingBody->getMotionState()->getWorldTransform(trans);
	btVector3 org = trans.getOrigin();
	org.setY(position);
	trans.setOrigin(org);
	movingBody->getMotionState()->setWorldTransform(trans);
	if (direction) {
		position-= 3.0f/fps;
		if (position < 0.0f) {
			position = 0.0f;
		}
	} else {
		position+= 1.0f/fps;
		if (position > 10.0f) {
			position = 10.0f;
		}
	}
	LevelState::update(fps);
}

void TestLevelTwo::onFinish() {
	LevelState::onFinish();
	Globals::GAMESTATE = new MainMenuState();
	Globals::GAMESTATE->resize(width,height);
}