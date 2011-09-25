#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <QGLWidget>
#include "ArgoActor.h"
#include "ArgoSceneManager.h"
#include "Selection.h"
#include "ArgoMatrix.h"
#include "DragPoint.h"
#include "Unproject.h"
#include "TransformAngle.h"

class Transformer {
public:
	static ArgoVector3 dragPoint;
	static float lastAngle;
	static int selected;

	static void drawBoundingBox(QString *sActor);
	static void drawTranslator(QString *sActor,float *xColor,float *yColor, float *zColor,bool selection);
	static void drawRotator(QString *sActor,float *xColor,float *yColor, float *zColor,bool selection);
	static void draw(QString *sActor,bool selection);
	static void calculateTransform(int mouseX, int mouseY, bool shift, bool ctrl);
};

#endif