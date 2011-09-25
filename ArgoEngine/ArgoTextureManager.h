#ifndef ARGOTEXTUREMANAGER_H
#define ARGOTEXTUREMANAGER_H

#include <QGLWidget>
#include <QtGui>
#include "ArgoTgaTexture.h"

class ArgoTextureManager {
public:
    static ArgoTextureManager* Instance();
    static void Initialize();
	void LoadTexture(QString filename, QString name = "");
	void BindTexture(QString name);
	void RenameTexture(QString oldName, QString newName);
	void DeleteTexture(QString name);
	void DeleteAllTextures();

	void SetWhite(QString *name) {white=name;}
	void BindWhite() {BindTexture(*white);}
	ArgoTexture *getWhite() {return textures[*white];}

	ArgoTexture *getTexture(QString name) { return textures[name]; }
	QMap<QString,ArgoTexture *> *getTextures() {return &textures;}	

	~ArgoTextureManager(){}
private:
	QMap<QString,ArgoTexture *> textures; 
	QString *white;

	ArgoTextureManager();
    static ArgoTextureManager* pInstance;
};

#endif