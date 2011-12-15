#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#define NUM_BUFFERS 1
#define NUM_SOURCES 1

#include <AL/alut.h>
#include <al.h>
#include <alc.h>
#include <string>
#include "Camera.h"
#include "btBulletDynamicsCommon.h"
#include <map>
#include <list>

using namespace std;

class SoundManager
{
public:
	static SoundManager* Instance();
	void updateListenerPosition(Camera* cam);
	void updateListenerPosition(ALfloat* fl);
	void updateListenerVelocity(const btVector3* vel);
	void addSoundSource(string filename,string id,ALfloat* position);
	void addSoundSource(string filename,string id, btVector3* position,bool doesNothing);
	void updateSourcePosition(string id,const btVector3* vec);
	void updateSourcePosition(string id,ALfloat* vec);
	void stopSound(string id);
	void startSound(string id,bool restartIfPlaying);
	bool isPlaying(string id);
	void makeLoop(string id);
	void loop();
private:
	SoundManager();
	static SoundManager* smInstance;
	void init();

	list<string> loopIDs;
	ALCdevice* Device;
	ALCcontext* Context;
	map<string,ALuint> buffers;
	map<string,ALuint> sources;
	ALfloat listenerPos[3];
	ALfloat listenerVel[3];
	ALfloat listenerOri[6];
};
#endif