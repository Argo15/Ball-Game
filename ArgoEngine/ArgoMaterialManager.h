#ifndef ARGOMATERIALMANAGER_H
#define ARGOMATERIALMANAGER_H

#include <QGLWidget>
#include <QtGui>
#include "GLSLProgram.h"
#include "ArgoMaterial.h"

class ArgoMaterialManager {
public:
    static ArgoMaterialManager* Instance();
    static void Initialize();
	void AddMaterial(ArgoMaterial *material);
	void UseMaterial(QString name,GLSLProgram *program = 0) {materials[name]->use(program);}
	void UseDefault(GLSLProgram *program = 0) {materials[*defaultMat]->use(program);}
	void RenameMaterial(QString oldName, QString newName);
	void DeleteMaterial(QString name);
	void DeleteAllMaterials();
	
	void setDefault(QString *defaultMaterial) {defaultMat=defaultMaterial;}
	ArgoMaterial *getDefault() {return materials[*defaultMat];}

	void setLightMaterial(QString *lightMaterial) {lightMat=lightMaterial;}
	ArgoMaterial *getLightMaterial() {return materials[*lightMat];}

	void setEntranceMaterial(QString *entranceMaterial) {entranceMat=entranceMaterial;}
	ArgoMaterial *getEntranceMaterial() {return materials[*entranceMat];}

	void setExitMaterial(QString *exitMaterial) {exitMat=exitMaterial;}
	ArgoMaterial *getExitMaterial() {return materials[*exitMat];}

	ArgoMaterial *getMaterial(QString name) { 
		return materials[name]; 
	}
	QMap<QString,ArgoMaterial *> *getMaterials() {return &materials;}	

	~ArgoMaterialManager(){}
private:
	QMap<QString,ArgoMaterial *> materials; 
	QString *defaultMat;
	QString *lightMat;
	QString *entranceMat;
	QString *exitMat;

	ArgoMaterialManager();
    static ArgoMaterialManager* pInstance;
};

#endif