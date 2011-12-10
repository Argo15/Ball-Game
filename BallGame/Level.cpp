#include "Level.h"
#include "ParticleCube.h"

struct BallCallback : public btCollisionWorld::ContactResultCallback
{
	bool canJump;

	virtual	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObject* colObj0, int partId0, int index0, const btCollisionObject* colObj1, int partId1, int index1)
	{
		if (btVector3(
			cp.m_normalWorldOnB.mVec128.m128_f32[0],
			cp.m_normalWorldOnB.mVec128.m128_f32[1],
			cp.m_normalWorldOnB.mVec128.m128_f32[2]
		).dot(btVector3(0,1,0)) > 0.7) {
			canJump = true;
		}

		return 0;
	}
};

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
	ballTexs[0] = new Texture();
	ballTexs[1] = new Texture();
	ballTexs[2] = new Texture();
	ballTexs[3] = new Texture();
	ballTexs[4] = new Texture();
	ballTexs[5] = new Texture();
	ballTexs[0]->load("Data/Textures/TGA/White.tga");
	ballTexs[1]->load("Data/Textures/TGA/White.tga");
	ballTexs[2]->load("Data/Textures/TGA/White.tga");
	ballTexs[3]->load("Data/Textures/TGA/White.tga");
	ballTexs[4]->load("Data/Textures/TGA/Beach Ball.tga");
	ballTexs[5]->load("Data/Textures/TGA/Earth.tga");
	ballColors[0][0] = 0.8; ballColors[0][1] = 0.2; ballColors[0][2] = 0.2; 
	ballColors[1][0] = 0.2; ballColors[1][1] = 0.8; ballColors[1][2] = 0.2; 
	ballColors[2][0] = 0.2; ballColors[2][1] = 0.2; ballColors[2][2] = 0.8; 
	ballColors[3][0] = 0.8; ballColors[3][1] = 0.8; ballColors[3][2] = 0.8; 
	ballColors[4][0] = 1.0; ballColors[4][1] = 1.0; ballColors[4][2] = 1.0; 
	ballColors[5][0] = 1.0; ballColors[5][1] = 1.0; ballColors[5][2] = 1.0; 
	ballNormals[0] = new Texture();
	ballNormals[1] = new Texture();
	ballNormals[2] = new Texture();
	ballNormals[3] = new Texture();
	ballNormals[4] = new Texture();
	ballNormals[0]->load("Data/Textures/TGA/Test Normals.tga");
	ballNormals[1]->load("Data/Textures/TGA/Concrete Normal.tga");
	ballNormals[2]->load("Data/Textures/TGA/Tiles Normals.tga");
	ballNormals[3]->load("Data/Textures/TGA/pavement_bump.tga");
	ballNormals[4]->load("Data/Textures/TGA/White.tga");

	canJump=true;

	ballReflection = new EnvironmentMap(512);
}

Level::~Level() {
	delete textures;
	delete materials;
	delete dynamicsWorld;
	delete models;
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
	startTransform.setOrigin(start);
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
	ballBody = new btRigidBody(rbInfo);
	ballBody->setFriction(btScalar(15.0));
	dynamicsWorld->addRigidBody(ballBody);
}

void Level::updateDynamicsWorld(bool *keys, Camera *camera, int fps, Profiler *profiler) {
	dynamicsWorld->stepSimulation(1.f/60.f,10);
	profiler->profile("Step Simulation");

	BallCallback ballCallback;
	ballCallback.canJump = false;
	dynamicsWorld->contactTest(ballBody,ballCallback);
	profiler->profile("Ball test");

	btVector3 velocity = ballBody->getLinearVelocity();
	float tempY = velocity.getY();
	velocity.setY(0);
	if (velocity.length()>4) {
		velocity.normalize();
		velocity *= 4;
		velocity.setY(tempY);
		ballBody->setLinearVelocity(velocity);
	}

	ArgoVector3 dir = ArgoVector3(0);
	if (keys['r']||keys['R']) {
		ballBody->setLinearVelocity(btVector3(0,0,0));
		ballBody->setAngularVelocity(btVector3(0,0,0));
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(start);
		ballBody->setWorldTransform(startTransform);
	}
	if (keys['w'] || keys['W']) {
		dir = camera->getLookAt()-camera->geteyeV();
		dir.set(dir[0],0,dir[2]);
		dir.normalize();
		btVector3 velocity(dir[0],0,dir[2]);
		ballBody->activate(true);
		ballBody->applyCentralForce(velocity*100*(60.0/fps));
	}
	if (keys['s'] || keys['S']) {
		dir = camera->geteyeV()-camera->getLookAt();
		dir.set(dir[0],0.01,dir[2]);
		dir.normalize();
		btVector3 velocity(dir[0],0,dir[2]);
		ballBody->activate(true);
		ballBody->applyCentralForce(velocity*100*(60.0/fps));
	}
	if (keys['d'] || keys['D']) {
		dir = camera->getRight();
		dir.set(dir[0],0,dir[2]);
		dir.normalize();
		btVector3 velocity(dir[0],0,dir[2]);
		ballBody->activate(true);
		ballBody->applyCentralForce(velocity*100*(60.0/fps));
	}
	if (keys['a'] || keys['A']) {
		dir = camera->getRight() * -1.0f;
		dir.set(dir[0],0,dir[2]);
		dir.normalize();
		btVector3 velocity(dir[0],0,dir[2]);
		ballBody->activate(true);
		ballBody->applyCentralForce(velocity*100*(60.0/fps));
	}
	if (keys[32] && ballCallback.canJump) {
		btVector3 velocity(0,1,0);
		ballBody->activate(true);
		ballBody->applyCentralForce(velocity*3000);
	}

	btTransform trans;
	ballBody->getMotionState()->getWorldTransform(trans);
	btVector3 ballPos(trans.getOrigin().getX(),trans.getOrigin().getY(),trans.getOrigin().getZ());
	camera->setLookAt(ballPos.getX(),ballPos.getY(),ballPos.getZ());
	float distance = 2.5;
	camera->updateFromDistance();

	btVector3 from(camera->getLookAt()[0],camera->getLookAt()[1],camera->getLookAt()[2]);
	btVector3 to(camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());
	btCollisionWorld::ClosestRayResultCallback rayCallBack(from,to+(to-from).normalize()*0.2);
	dynamicsWorld->getCollisionWorld()->rayTest(from,to+(to-from).normalize()*0.2,rayCallBack);
	profiler->profile("Camera test");
	if (rayCallBack.hasHit()) {
		distance = (rayCallBack.m_hitPointWorld-from).length()-0.1;
		camera->setDistance(distance);
	} else {
		camera->update(fps);
	}
	camera->updateFromDistance();

	if (Globals::ballReflect > 0)
		ballReflection->generateEnvironmentMap(ArgoVector3(ballPos.getX(),ballPos.getY(),ballPos.getZ()),15.0,this);
}

float Level::distanceFromEnd() {
	btTransform trans;
	ballBody->getMotionState()->getWorldTransform(trans);
	return trans.getOrigin().distance(end);
}

void Level::drawNoBall(Frustum *frustum) {
	map<string,Object *>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++) {
		glPushMatrix();
		btVector3 pos = i->second->getRigidBody()->getCenterOfMassPosition();
		float radius = i->second->getScaledRadius(models);
		if (frustum->isInFrustum(ArgoVector3(pos.getX(), pos.getY(), pos.getZ()),radius)) {
			i->second->transform();
			materials->getMaterial(i->second->getMaterial())->useNoShaders(textures);
			models->getModel(i->second->getModel())->drawNoShaders();
		}
		glPopMatrix();
	}
}

void Level::drawNoShaders(Frustum *frustum) {
	btTransform trans;
	ballBody->getMotionState()->getWorldTransform(trans);
	glPushMatrix();
		materials->getMaterial("Default")->useNoShaders(textures);
		ballTexs[4]->use();
		float spec[] = {1.0, 1.0, 1.0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
		glMaterialf(GL_FRONT,GL_SHININESS,128);
		float mat[16];
		trans.getOpenGLMatrix(mat);
		glMultMatrixf(mat);
		glScalef(0.25,0.25,0.25);
		myBall->drawNoShaders();
	glPopMatrix();

	map<string,Object *>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++) {
		glPushMatrix();
		btVector3 pos = i->second->getRigidBody()->getCenterOfMassPosition();
		float radius = i->second->getScaledRadius(models);
		if (frustum->isInFrustum(ArgoVector3(pos.getX(), pos.getY(), pos.getZ()),radius)) {
			i->second->transform();
			materials->getMaterial(i->second->getMaterial())->useNoShaders(textures);
			models->getModel(i->second->getModel())->drawNoShaders();
		}
		glPopMatrix();
	}
}

void Level::draw(GLSLProgram *program, Frustum *frustum) {
	map<string,Object *>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++) {
		glPushMatrix();
		btVector3 pos = i->second->getRigidBody()->getCenterOfMassPosition();
		if (frustum->isInFrustum(ArgoVector3(pos.getX(), pos.getY(), pos.getZ()),i->second->getScaledRadius(models))) {
			i->second->transform();
			materials->getMaterial(i->second->getMaterial())->use(textures,program);
			models->getModel(i->second->getModel())->draw();
		}
		glPopMatrix();
	}
}

void Level::drawBall(GLSLProgram *program, Frustum *frustum) {
	btTransform trans;
	ballBody->getMotionState()->getWorldTransform(trans);

	glPushMatrix();
		glActiveTexture(GL_TEXTURE8);
		glEnable(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP,ballReflection->getEnvironmentMap());
		program->sendUniform("environmentTex",8);
		glEnable(GL_TEXTURE_2D);
		glActiveTextureARB(GL_TEXTURE0);
		program->sendUniform("matFactor",1.0f - 0.5f*Globals::ballReflect);
		program->sendUniform("reflectFactor",Globals::ballReflect);

		float mat[16];
		trans.getOpenGLMatrix(mat);
		glMultMatrixf(mat);
		glScalef(0.25,0.25,0.25);
		glMatrixMode(GL_TEXTURE);
		glActiveTextureARB(GL_TEXTURE7);
		glLoadIdentity();
		glMultMatrixf(mat);
		glScalef(0.25,0.25,0.25);
		glActiveTextureARB(GL_TEXTURE2);
		glLoadIdentity();
		glMultMatrixf(lastMat);
		glScalef(0.25,0.25,0.25);
		for (int i=0; i<16; i++) lastMat[i] = mat[i];
		glMatrixMode(GL_MODELVIEW);


		materials->getMaterial("Default")->use(textures,program);
		float spec[] = {1.0, 1.0, 1.0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
		glMaterialf(GL_FRONT,GL_SHININESS,128);

		int i = Globals::matNum;

		glEnable(GL_COLOR_MATERIAL);
		glColor3f(ballColors[i][0], ballColors[i][1], ballColors[i][2]);

		glActiveTextureARB(GL_TEXTURE0);
		ballTexs[i]->use();
		program->sendUniform("tex",0);

		glActiveTextureARB(GL_TEXTURE1);
		glEnable(GL_TEXTURE_2D);
		ballNormals[Globals::bumpNum]->use();
		program->sendUniform("normalmap",1);
		program->sendUniform("normalenabled",Globals::bumpNum < 4);

		myBall->draw();

	glPopMatrix();
	glActiveTextureARB(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
}

void Level::drawPointShadows(Frustum *frustum) {
	btTransform trans;
	ballBody->getMotionState()->getWorldTransform(trans);
	float mat[16];
	trans.getOpenGLMatrix(mat);
	glMatrixMode(GL_TEXTURE);
			glActiveTextureARB(GL_TEXTURE5);
			glLoadIdentity();
			glMultMatrixf(mat);
			glScalef(0.25,0.25,0.25);
			glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glMultMatrixf(mat);
		glScalef(0.25,0.25,0.25);
		myBall->drawNoShaders();
	glPopMatrix();

	map<string,Object *>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++) {
		Object *object = i->second;
		btVector3 pos = object->getRigidBody()->getCenterOfMassPosition();
		if (frustum->isInFrustum(ArgoVector3(pos.getX(), pos.getY(), pos.getZ()),object->getScaledRadius(models))) {
			glMatrixMode(GL_TEXTURE);
			glActiveTextureARB(GL_TEXTURE5);
			glLoadIdentity();
			object->transformToCurrentMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				object->transform();
				models->getModel(object->getModel())->drawNoShaders();
			glPopMatrix();
		}
	}
}

void Level::getLastTransforms() {
	map<string,Object *>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++) {
		Object *object = i->second;
		object->setLastTransform();
	}
}

int Level::getBestPointLights(PointLight **bestLights, Frustum *frustum, Camera *camera, int count) 
{
	PointLight **lights = new PointLight*[100];
	btTransform trans;
	ballBody->getMotionState()->getWorldTransform(trans);
	ArgoVector3 ballPos(trans.getOrigin().getX(),trans.getOrigin().getY(),trans.getOrigin().getZ());
	int numLights = 0;
	map<string,PointLight *>::iterator it;
	for (it = pLights.begin(); it != pLights.end(); ++it){
		PointLight *pLight = it->second;
		if (pLight->isenabled()){
			if (frustum->isInFrustum(pLight->getPosition(),pLight->getRadius())) {
				lights[numLights++] = pLight;
			}
		}
	}
	int lightCount = min(numLights,count);
	for (int i = numLights-1; i>0; i--) {
		for (int j=0; j<i; j++) {
			ArgoVector3 first(lights[j]->getPosition()-ballPos);
			ArgoVector3 second(lights[j+1]->getPosition()-ballPos);
			if (first.length()>second.length()) {
				swap(lights[j],lights[j+1]);
			}
		}
	}
	for (int i = 0; i < lightCount; i++) {
		bestLights[i]=lights[i];
	}
	return lightCount;
}

int Level::getAllPointLights(PointLight **lights) {
	int numLights = 0;
	map<string,PointLight *>::iterator it;
	for (it = pLights.begin(); it != pLights.end(); ++it){
		lights[numLights++] = it->second;
	}
	return numLights;
}

btVector3* Level::getStart()
{
	return &start;
}

btVector3* Level::getEnd()
{
	return &end;
}