#ifndef MATERIALEDITOR_H
#define MATERIALEDITOR_H

#include <QDialog>
#include <QtGUI>
#include <QGLWidget>
#include "ArgoTextureManager.h"
#include "TextureWidget.h"
#include "ArgoMaterialManager.h"
#include "MaterialWidget.h"
#include "ModelEditor.h"
#include "DockedActorEditor.h"

class MaterialEditor : public QDialog
{
	Q_OBJECT

private:
	MaterialEditor(QGLWidget *parent = 0);
	static MaterialEditor* pInstance;

	QString *currentMat;
	MaterialWidget *matWidget;
	TextureWidget *texWidget, *normalWidget;

	QComboBox *matCmb,*textureCmb,*normalCmb;
	QLineEdit *nameEdt,*uTexOffEdt,*vTexOffEdt,*uTexScaleEdt,*vTexScaleEdt;
	QLabel *nameLbl,*colorLbl,*specLbl,*shineLbl,*glowLbl,
			*colorViewLbl,*glowViewLbl,*textureLbl,
			*uvOffLbl,*uvScaleLbl,*texRotateLbl,*normalLbl;
	QSlider *specSld,*shineSld,*texRotateSld;
	QPushButton *newMaterialBtn,*colorBtn, *glowBtn;
	QCheckBox *normalChk;

public:
	static MaterialEditor* Instance();
    static void Initialize(QGLWidget *parent = 0);

public slots:
	void updateEditor();
	void currentMatChanged(QString mat);
	

private slots:
	void nameChanged(QString name);
	void specChanged(int value);
	void shineChanged(int value);
	void colorChanged();
	void glowChanged();
	void currentTexChanged(QString tex);
	void currentNormChanged(QString tex);
	void addNewMaterial();
	void uTexOffChanged(QString value);
	void vTexOffChanged(QString value);
	void uTexScaleChanged(QString value);
	void vTexScaleChanged(QString value);
	void texRotateChanged(int value);
	void normalChanged();
};

#endif