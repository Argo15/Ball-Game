#ifndef TEXTUREWIDGET_H
#define TEXTUREWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QtGui>
#include "ArgoTextureManager.h"
#include "ArgoView.h"


class TextureWidget : public QGLWidget
{
    Q_OBJECT

private:
	QString *texture;
	ArgoView *view;

public:
	TextureWidget(QWidget *parent = 0, const QGLWidget * shareWidget = 0);
	void setTexture(QString *name) {texture=name;}

protected:
    void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

private slots:
};

#endif