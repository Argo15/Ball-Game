#ifndef DIRECTLIGHTWIDGET_H
#define DIRECTLIGHTWIDGET_H

#include <QGLWidget>
#include <QtGui>
#include "ArgoSceneManager.h"

class DirectLightWidget : public QWidget
{
    Q_OBJECT

private:
	QLabel *nameLbl, *colorLbl, *ambientLbl, *diffuseLbl, *specularLbl, *colorViewLbl;
	QCheckBox *enabledChk;
	QLineEdit *nameEdt;
	QSlider *ambientSld, *diffuseSld, *specularSld;
	QPushButton *colorBtn;

public:
	DirectLightWidget(QGLWidget *parent = 0);

public slots:
	void updateWidget();
	void ambientChanged(int value);
	void diffuseChanged(int value);
	void specularChanged(int value);
	void nameChanged(QString name);
	void colorChanged();
	void enabledChanged();
};

#endif