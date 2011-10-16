#ifndef TESTLEVELTWO_H
#define TESTLEVELTWO_H

#include "LevelState.h"

class TestLevelTwo : public LevelState
{
private:
	float angle;
	float position;

	bool direction;

public:
	TestLevelTwo();

	void update(int fps);
	void onFinish();
};

#endif