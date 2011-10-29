#ifndef FUNHOUSE_H
#define FUNHOUSE_H

#include "LevelState.h"

class FunHouse : public LevelState
{
private:

public:
	FunHouse();

	void resize(int w, int h);
	void update(int fps);
	void onFinish();
};

#endif