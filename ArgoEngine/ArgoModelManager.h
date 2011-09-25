#ifndef ARGOMODELMANAGER_H
#define ARGOMODELMANAGER_H

#include <QGLWidget>
#include <QtGui>
#include "ArgoAObjModel.h"
#include "ArgoObjModel.h"

class ArgoModelManager {
public:
    static ArgoModelManager* Instance();
    static void Initialize();
	void LoadModel(QString filename, QString name = "");
	void DrawModel(QString name);
	void DrawModelSelection(QString name);
	void RenameModel(QString oldName, QString newName);
	void DeleteModel(QString name);
	void DeleteAllModels();

	void setDefault(QString *defaultModel) {this->defaultModel=defaultModel;}
	ArgoModel *getDefault() {return models[*defaultModel];}

	void setPointLightModel(QString *pointLightModel) {this->pointLightModel=pointLightModel;}
	ArgoModel *getPointLightModel() {return models[*pointLightModel];}

	void setDirectLightModel(QString *directLightModel) {this->directLightModel=directLightModel;}
	ArgoModel *getDirectLightModel() {return models[*directLightModel];}

	void setPortModel(QString *portModel) {this->portModel=portModel;}
	ArgoModel *getPortModel() {return models[*portModel];}

	ArgoModel *getModel(QString name) { return models[name]; }
	QMap<QString,ArgoModel *> *getModels() {return &models;}	

	~ArgoModelManager(){}
private:
	QMap<QString,ArgoModel *> models; 
	QString *defaultModel;
	QString *pointLightModel;
	QString *directLightModel;
	QString *portModel;

	ArgoModelManager();
    static ArgoModelManager* pInstance;
};

#endif