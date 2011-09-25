#ifndef ARGORIGIDBODY_H
#define ARGORIGIDBODY_H

enum BodyType { STATIC, KINEMATIC, DYNAMIC };

class ArgoRigidBody {
public:
	BodyType type;
	int numTriangles;
	float *triangles;
};

#endif