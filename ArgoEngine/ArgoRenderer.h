#ifndef ARGOReNDeReR_H
#define ARGOReNDeReR_H

#include <QtOpenGL>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>

class ArgoRenderer {
private:
	
public:
	ArgoRenderer(){setClearColor(0.0f,0.0f,0.0f,0.0f);setClearDepth(1.0f);}
	~ArgoRenderer(){}

	void init();
	void clear();
	void setClearColor(float r, float g, float b, float a) {glClearColor(r,g,b,a);}
	void setClearDepth(float d) {glClearDepth(1.0f);}
	void flush() {glFlush();}
	void loadIdentity(){glLoadIdentity();}
	void pushMatrix(){glPushMatrix();}
	void popMatrix(){glPopMatrix();}
};

#endif