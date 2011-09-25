#ifndef ARGOTEXTURe_H
#define ARGOTEXTURe_H

#include <QGLWidget>

class ArgoTexture{

protected:
	GLuint textureID;
	QString location;
	QString *name;
	QString type;

public:
	virtual bool load(const char *filename) = 0;
	void use();
	void remove();

	QString getLocation() { return location; }
	QString *getName() {return name;}
	QString getType() {return type;}
	void setName(QString newName) {*name=newName;}
	void setType(QString newType) {type=newType;}
};

#endif