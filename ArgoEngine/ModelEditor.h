#ifndef MODELEDITOR_H
#define MODELEDITOR_H

#include <QDialog>
#include <QtGUI>
#include <QGLWidget>
#include "ArgoModelManager.h"
#include "ArgoMaterialManager.h"
#include "MaterialWidget.h"
#include "ModelWidget.h"
#include "ArgoSceneManager.h"

class ModelEditor : public QDialog
{
	Q_OBJECT

private:
	ModelEditor(QGLWidget *parent = 0);
	static ModelEditor* pInstance;

	QString *currentModel;
	QString *currentMat;

	QLineEdit *nameEdt;
	QLabel *modelLbl, *matLbl;
	QComboBox *modelCmb, *matCmb;
	QPushButton *loadModelBtn, *addToSceneBtn;

	ModelWidget *modelWidget;

public:
	static ModelEditor* Instance();
    static void Initialize(QGLWidget *parent = 0);

public slots:
	void updateEditor();

private slots:
	void currentModelChanged(QString model);
	void currentMatChanged(QString mat);
	void loadModel();
	void addToScene();
	void nameChanged(QString name);
};
#endif