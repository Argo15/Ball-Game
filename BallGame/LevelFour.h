#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include "LevelState.h"

class LevelFour : public LevelState
{
private:

public:
	LevelFour();

	void update(int fps);
	void onFinish();
};

#endif