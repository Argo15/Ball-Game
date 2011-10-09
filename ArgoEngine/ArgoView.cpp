#include "ArgoView.h"

void ArgoView::use3D(boolean use3D){
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (use3D)
        gluPerspective(fovy, aspect, zNear, zFar);
    else
        glOrtho(left, right, bottom, top, front, back);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ArgoView::set3D(GLdouble _fovy, GLdouble _aspect, GLdouble _zNear, GLdouble _zFar){
	fovy=_fovy;
    aspect=_aspect;
    zNear=_zNear;
    zFar=_zFar;
}

void ArgoView::set2D(GLdouble _left, GLdouble _right, GLdouble _bottom, GLdouble _top, GLdouble _front, GLdouble _back){
        left=_left;
        right=_right;
        bottom=_bottom;
        top=_top;
        front=_front;
        back=_back;
}