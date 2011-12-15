#ifndef MINECRAFT_H
#define MINECRAFT_H

#include "LevelState.h"

class Minecraft : public LevelState
{
private:

public:
	Minecraft();

	void update(int fps);
	void onFinish();
};

#endif