#include "Funhouse.h"
#include "MainMenuState.h"
#include "Globals.h"

FunHouse::FunHouse() : LevelState(){
	levelFile = new LevelFile();
	levelFile->loadFile("Data/Saves/FunHouse.ascn");
	level = new Level();
	levelFile->initializeLevel(level);
	endDistance = 1.0;
	irishSpinAngle = 0;
	Globals::glowEnabled = false;
}

void FunHouse::resize(int w, int h) {
	GameState::resize(w,h);
	if(h == 0)
		h = 1;
	GLfloat aspect = GLfloat(w) / h;
	view->viewport(0, 0, w, h);
	view->set3D(45.0f,aspect,0.01,30);
	view->set2D(0,1,0,1,0,1);
}

void FunHouse::update(int fps) {
	btRigidBody *rotatingBody;
	btTransform trans;
	btQuaternion rot;

	rotatingBody = level->getObject("IrishSpinner Actor")->getRigidBody();
	rotatingBody->getMotionState()->getWorldTransform(trans);
	rot = trans.getRotation();
	rot.setRotation(btVector3(0.0,1.0,0.0),btScalar(irishSpinAngle));
	trans.setRotation(rot);
	rotatingBody->getMotionState()->setWorldTransform(trans);

	rotatingBody = level->getObject("IrishSpinner Actor(1)")->getRigidBody();
	rotatingBody->getMotionState()->getWorldTransform(trans);
	rot = trans.getRotation();
	rot.setRotation(btVector3(0.0,1.0,0.0),btScalar(irishSpinAngle*3.0));
	trans.setRotation(rot);
	rotatingBody->getMotionState()->setWorldTransform(trans);

	rotatingBody = level->getObject("IrishSpinner Actor(2)")->getRigidBody();
	rotatingBody->getMotionState()->getWorldTransform(trans);
	rot = trans.getRotation();
	rot.setRotation(btVector3(0.0,1.0,0.0),btScalar(-irishSpinAngle*2.0));
	trans.setRotation(rot);
	rotatingBody->getMotionState()->setWorldTransform(trans);

	rotatingBody = level->getObject("IrishSpinner Actor(3)")->getRigidBody();
	rotatingBody->getMotionState()->getWorldTransform(trans);
	rot = trans.getRotation();
	rot.setRotation(btVector3(0.0,1.0,0.0),btScalar(-irishSpinAngle*4.0));
	trans.setRotation(rot);
	rotatingBody->getMotionState()->setWorldTransform(trans);

	rotatingBody = level->getObject("spinHole Actor")->getRigidBody();
	rotatingBody->getMotionState()->getWorldTransform(trans);
	rot = trans.getRotation();
	rot.setRotation(btVector3(0.0,0.0,1.0),btScalar(irishSpinAngle/2));
	trans.setRotation(rot);
	rotatingBody->getMotionState()->setWorldTransform(trans);

	rotatingBody = level->getObject("Barrel Actor")->getRigidBody();
	rotatingBody->getMotionState()->getWorldTransform(trans);
	rot = trans.getRotation();
	rot.setRotation(btVector3(1.0,0.0,0.0),btScalar(irishSpinAngle*2));
	trans.setRotation(rot);
	rotatingBody->getMotionState()->setWorldTransform(trans);

	LevelState::update(fps);
	irishSpinAngle += 2/(fps+0.01f);
}

void FunHouse::onFinish() {
	LevelState::onFinish();
	Globals::GAMESTATE = new MainMenuState();
	Globals::GAMESTATE->resize(width,height);
	delete this;
}