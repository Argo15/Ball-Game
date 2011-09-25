#ifndef ARGOVIeW_H
#define ARGOVIeW_H

#include <QtOpenGL>

class ArgoView{
private:
	GLdouble fovy, aspect, zNear, zFar;
	GLdouble left, right, top, bottom, front, back;
public:
	ArgoView(){}
	~ArgoView(){}

	void use3D(boolean use3D);
	void set3D(GLdouble _fovy, GLdouble _aspect, GLdouble _zNear, GLdouble _zFar);
	void set2D(GLdouble _left, GLdouble _right, GLdouble _bottom, GLdouble _top, GLdouble front, GLdouble back);
	void viewport(int x, int y, int width, int height) {glViewport(x,y,width,height);}

	float getFOV() {return fovy;}
	float getAspect() {return aspect;}
	float getNear() {return zNear;}
	float getFar() {return zFar;}

	float getOrthoWidth() {return right-left;}
	float getOrthoHeight() {return top-bottom;}
	float getOrthoDepth() {return back-front;}
	float getOrthoNear() {return front;}
	float getOrthoFar() {return back;}
};

#endif