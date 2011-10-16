#ifndef TESTLEVELONE_H
#define TESTLEVELONE_H

#include "LevelState.h"

class TestLevelOne : public LevelState
{
private:
	float angle;
	float position;

	bool direction;

public:
	TestLevelOne();

	void update(int fps);
	void onFinish();
};

#endif