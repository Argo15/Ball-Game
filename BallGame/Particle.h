#ifndef PARTICLE
#define PARTICLE

#include "btBulletDynamicsCommon.h"
#include <vector>
#include "Texture.h"
using namespace std;

class Particle
{
public:
	Particle();
	Particle(int frame);
	void Update();
	void Render(float x, float y, float z);
	void addTexture(string location);

private:
	void billboardSphericalBegin(float x, float y, float z);
	vector<Texture*> frames;
	int frameCount;
	int currentFrame;
};

#endif