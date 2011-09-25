#ifndef ARGOGRAPHICSSETTINGS_H
#define ARGOGRAPHICSSETTINGS_H

#include <QGLWidget>
#include <QtGui>

class ArgoGraphicsSettings {
public:
    static ArgoGraphicsSettings* Instance();
    static void Initialize();

	bool shadersEnabled() {return shaders;}
	void setShadersEnabled(bool enabled) {shaders=enabled;}

private:
	bool shaders;

	ArgoGraphicsSettings();
    static ArgoGraphicsSettings* pInstance;
};

#endif