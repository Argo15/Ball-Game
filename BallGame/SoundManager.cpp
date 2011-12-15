#include "SoundManager.h"
#include <iostream>
#include <AL/alut.h>
#include <al.h>
#include <alc.h>
#include <efx.h>
#include <efx-creative.h>
#include <EFX-Util.h>
#include <xram.h>
#include "btBulletDynamicsCommon.h"
#include <map>

using namespace std;

SoundManager* SoundManager::smInstance = NULL;

//returns a singleton to the sound manager
SoundManager* SoundManager::Instance()
{
	if(!smInstance)//only one instance of this class
		smInstance = new SoundManager();

	return smInstance;
}
SoundManager::SoundManager()
{
	init();
}

void SoundManager::init()
{
	//initialize the listener's positions
	for(int x =0;x<3;x++)
	{
	listenerPos[x]=0.0;
	listenerVel[x]=0.0;
	}
	listenerOri[0]=0.0;
	listenerOri[1]=0.0;
	listenerOri[2]=-1.0;
	listenerOri[3]=0.0;
	listenerOri[4]=1.0;
	listenerOri[5]=0.0;
	
	

	//Open a device
	//Device = alcOpenDevice(NULL);

	//open context on the device
	//if(Device)
	//{
//		Context = alcCreateContext(Device,0);
	//}
//	else
//	{
//		cout<<"Could Not Open OPENAL Device"<<endl;
//		exit(1);
//	}
//	alGetError();//clear errors

	//initiallizes the buffers
//	alGenBuffers(NUM_BUFFERS,buffers);


}

//updates the location of the listener based on the camera (once per frame)
void SoundManager::updateListenerPosition(Camera* cam)
{
	ALenum error;
	listenerPos[0] = cam->geteyeX();
	listenerPos[1] = cam->geteyeY();
	listenerPos[2] = cam->geteyeZ();

	alGetError();//clear error code

	alListenerfv(AL_POSITION,listenerPos);

	if((error = alGetError()) != AL_NO_ERROR)
	{
		//DisplayALError("alListenerfv POSITION : ",error);
		cout<<error<<endl;
		return;
	}
}

void SoundManager::updateListenerPosition(ALfloat* fl)
{
	ALenum error;
	alGetError();//clear error code
	alListenerfv(AL_VELOCITY,fl);
		if((error = alGetError()) != AL_NO_ERROR)
	{
		//DisplayALError("alListenerfv POSITION : ",error);
		cout<<error<<endl;
		return;
	}
}

void SoundManager::updateListenerVelocity(const btVector3* vel)
{
	ALenum error;
	listenerVel[0] = vel->getX();
	listenerVel[1] = vel->getY();
	listenerVel[2] = vel->getZ();
	alGetError();//clear error code
	alListenerfv(AL_VELOCITY,listenerVel);
		if((error = alGetError()) != AL_NO_ERROR)
	{
		//DisplayALError("alListenerfv POSITION : ",error);
		cout<<error<<endl;
		return;
	}
}

void SoundManager::addSoundSource(string filename,string id,ALfloat* position)
{
	//return if sound already created
	if(buffers[id] != NULL)
	{
		return;
	}
	ALenum error;
	alGetError();//clear errors
	buffers[id] = alutCreateBufferFromFile((const char*)filename.c_str());
	//buf = alutCreateBufferHelloWorld();
	alGenSources(1,&sources[id]);
	alSourcei(sources[id],AL_BUFFER,buffers[id]);
	if(position==NULL)
	{
		alSourcefv(sources[id],AL_POSITION,listenerPos);
	}
	else
	{
		alSourcefv(sources[id],AL_POSITION,position);
	}

	//alSourcePlay(sources[id]);

	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
	{
		//DisplayALError("alListenerfv POSITION : ",error);
		cout<<error<<endl;
		return;
	}

	//ALuint buffer = alutCreateBufferHelloWorld();
	//ALuint source;
	//alGenSources(1, &source);
	//alSourcei(source, AL_BUFFER, buffer);
	//alSourcePlay(source);
}

void SoundManager::addSoundSource(string filename,string id,btVector3* position,bool doesNothing)
{
	//return if sound already created
	if(buffers[id] != NULL)
	{
		return;
	}
	ALenum error;
	alGetError();//clear errors
	buffers[id] = alutCreateBufferFromFile((const char*)filename.c_str());
	//buf = alutCreateBufferHelloWorld();
	alGenSources(1,&sources[id]);
	alSourcei(sources[id],AL_BUFFER,buffers[id]);
	if(position==NULL)
	{
		alSourcefv(sources[id],AL_POSITION,listenerPos);
	}
	else
	{
		ALfloat conv[3];
		conv[0]= position->getX();
		conv[1]= position->getY();
		conv[2]= position->getZ();
		alSourcefv(sources[id],AL_POSITION,conv);
	}

	//alSourcePlay(sources[id]);

	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
	{
		//DisplayALError("alListenerfv POSITION : ",error);
		cout<<error<<endl;
		return;
	}

	//ALuint buffer = alutCreateBufferHelloWorld();
	//ALuint source;
	//alGenSources(1, &source);
	//alSourcei(source, AL_BUFFER, buffer);
	//alSourcePlay(source);
}

void SoundManager::stopSound(string id)
{
	loopIDs.remove(id);
	alSourceStop(sources[id]);
}

void SoundManager::startSound(string id,bool restartIfPlaying)
{
	if(sources[id]!=NULL)
	{
		if(isPlaying(id)==true && restartIfPlaying == true)
		{
			alSourcePlay(sources[id]);
		}
		if(isPlaying(id)==false)
		{
			alSourcePlay(sources[id]);
		}
	}
}

bool SoundManager::isPlaying(string id)
{
	ALenum state;
	alGetSourcei(sources[id],AL_SOURCE_STATE,&state);
	return (state == AL_PLAYING);
}

void SoundManager::makeLoop(string id)
{
	loopIDs.push_front(id);
}

//called once per frame in level update to loop each sound
//also in update menustate
void SoundManager::loop()
{
	for(list<string>::iterator it = loopIDs.begin();it!= loopIDs.end();it++)
	{
		if(isPlaying(*it)==false)
		{
			startSound(*it,false);
		}
	}
}

void SoundManager::updateSourcePosition(string id,const btVector3* vec)
{
	ALfloat conv[3];
	conv[0]= vec->getX();
	conv[1]= vec->getY();
	conv[2]= vec->getZ();
	alSourcefv(sources[id],AL_POSITION,conv);
}

void SoundManager::updateSourcePosition(string id,ALfloat* vec)
{
	alSourcefv(sources[id],AL_POSITION,vec);
}