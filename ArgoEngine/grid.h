#ifndef GRID_H
#define GRID_H

#include <QGLWidget>

class grid{
private:
	float color[3];
	int length,width;
	float center[2];
public:
	grid() {width=16;length=16;color[0]=0;color[1]=0;color[2]=0;center[0]=0;center[1]=0;}
	grid(int l, int w) {length=l;width=w;color[0]=0;color[1]=0;color[2]=0;center[0]=0;center[1]=0;}
	~grid() {}

	void setColor(float r, float g, float b) { color[0]=r;color[1]=g;color[2]=b;}
	void setSize(int l, int w) {length=l;width=w;}
	void setCenter(float x, float y) {center[0]=x;center[1]=y;}

	void draw()
	{
		float u = (float)width/2.0;
		float v = (float)length/2.0;
		glLineWidth(2.0);

		glVertexAttrib3f(2,0.0,0.0,0.0);
		glVertexAttrib3f(3,0.0,0.0,0.0);
		glVertexAttrib3f(4,0.0,0.0,0.0);
		glVertexAttrib3f(5,color[0],color[1],color[2]);
		glColor3f(1.0,1.0,1.0);
		for (int x=0;x<=width;x++){
			int a = center[0]-u+(float)x;
			glBegin(GL_LINES);
				glVertex3f(a,0,center[1]+v);
				glVertex3f(a,0,center[1]-v);
			glEnd();
		}
		for (int y=0;y<=length;y++){
			int b = center[1]-v+(float)y;
			glBegin(GL_LINES);
				glVertex3f(center[0]+u,0,b);
				glVertex3f(center[0]-u,0,b);
			glEnd();
		}
		glLineWidth(1.0);
	}
};
#endif
