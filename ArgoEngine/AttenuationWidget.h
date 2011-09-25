#ifndef ATTENUATIONWIDGET_H
#define ATTENUATIONWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QtGui>
#include "ArgoTextureManager.h"
#include "ArgoView.h"

class AttenuationWidget : public QGLWidget
{
    Q_OBJECT

private:
	float attenuation;
	ArgoView *view;

public:
	AttenuationWidget(QWidget *parent = 0, QGLWidget *shared = 0);
	void setAttenuation(float atten) {attenuation=atten;}

protected:
    void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

};

#endif