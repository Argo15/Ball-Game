#ifndef START_AND_END
#define START_AND_END

#include "btBulletDynamicsCommon.h"
using namespace std;

class StartAndEnd
{
public:
	StartAndEnd();
	void Update(btVector3* start, btVector3* end);
	void Render();
private:
	btVector3 startPoint;
	btVector3 endPoint;
};

#endif