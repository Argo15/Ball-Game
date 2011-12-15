#ifndef PARTICLE_CUBE
#define PARTICLE_CUBE

#include "btBulletDynamicsCommon.h"
#include "Texture.h"
#include "Particle.h"

class ParticleCube
{
public:
	ParticleCube();
	~ParticleCube();
	void Update(btVector3* start,btVector3* end);
	void Render(GLSLProgram *program);
	void nullify();
	

private:
	btVector3* start;
	btVector3* end;
	Particle* particles[10];

};

#endif