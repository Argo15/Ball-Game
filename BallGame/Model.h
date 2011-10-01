#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <windows.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
using namespace std;

class Model {
private:
	GLuint bufferID;
	int numTriangles;
	float radius;

public:
	Model(){}
	~Model(){}
	bool load(const char *filename);
	void remove() { glDeleteBuffers(1, &bufferID); }
	void draw();
	void drawNoShaders();
	float getRadius() {return radius;}
};

#endif