#ifndef POINTLIGHTWIDGET_H
#define POINTLIGHTWIDGET_H

#include <QGLWidget>
#include <QtGui>
#include "ArgoSceneManager.h"
#include "AttenuationWidget.h"

class QLabel;
class QCheckBox;
class QLineEdit;
class QSlider;
class QPushButton;
class QComboBox;

class PointLightWidget : public QWidget
{
    Q_OBJECT

private:
	QString *currentLight;

	AttenuationWidget *attenWgt;

	QLabel *nameLbl, *colorLbl, *ambientLbl, *diffuseLbl, *specularLbl, *colorViewLbl, *attenLbl, *radiusLbl;
	QCheckBox *enabledChk;
	QLineEdit *nameEdt, *radiusEdt;
	QSlider *ambientSld, *diffuseSld, *specularSld, *attenSld;
	QPushButton *colorBtn, *addLightBtn;
	QComboBox *lightCmb;

public:
	PointLightWidget(QGLWidget *parent = 0, QGLWidget *shared = 0);

public slots:
	void updateWidget();
	void ambientChanged(int value);
	void diffuseChanged(int value);
	void specularChanged(int value);
	void attenuationChanged(int value);
	void nameChanged(QString name);
	void radiusChanged(QString name);
	void colorChanged();
	void enabledChanged();
	void addNewLight();
	void currentLightChanged(QString name);
};

#endif