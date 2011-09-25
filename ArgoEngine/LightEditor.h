#ifndef LIGHTEDITOR_H
#define LIGHTEDITOR_H

#include <QDialog>
#include <QtGUI>
#include <QGLWidget>
#include "DirectLightWidget.h"
#include "PointLightWidget.h"

class DirectLightWidget;
class PointLightWidget;

class LightEditor : public QDialog
{
	Q_OBJECT

private:
	LightEditor(QGLWidget *parent = 0);
	static LightEditor* pInstance;

	QTabWidget *lightTab;
	DirectLightWidget *dLightWgt;
	PointLightWidget *pLightWgt;

public:
	static LightEditor* Instance();
    static void Initialize(QGLWidget *parent = 0);

	PointLightWidget *getPointLightWidget() {return pLightWgt;}

public slots:
	void updateEditor();

};

#endif