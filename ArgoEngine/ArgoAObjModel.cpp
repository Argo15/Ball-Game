#include "ArgoAObjModel.h"

bool ArgoAObjModel::load(QString filename)
{
	ifstream file(qPrintable(filename), ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
		float version=0;
		file.seekg (0, ios::beg);
		file.read((char*)&version,sizeof(version));
		file.read((char*)&numTriangles,sizeof(numTriangles));
		float *vertex = new float[numTriangles*9];
		float *texture = new float[numTriangles*6];
		float *normal = new float[numTriangles*9];
		float *tangentbuf = new float[numTriangles*9];
		float *bitangentbuf = new float[numTriangles*9];
		file.read((char*)vertex,sizeof(float)*9*numTriangles);
		file.read((char*)texture,sizeof(float)*6*numTriangles);
		file.read((char*)normal,sizeof(float)*9*numTriangles);
		file.read((char*)tangentbuf,sizeof(float)*9*numTriangles);
		file.read((char*)bitangentbuf,sizeof(float)*9*numTriangles);
		file.read((char*)&radius,sizeof(radius));
		center[0]=center[1]=center[2]=0.0;	
		physTriangles=vertex;

		glGenBuffers(1,&bufferID);
		glBindBuffer(GL_ARRAY_BUFFER,bufferID);
		glBufferData(GL_ARRAY_BUFFER,numTriangles*42*sizeof(GLfloat), NULL,GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER,0,numTriangles*9*sizeof(GLfloat),vertex);
		glBufferSubData(GL_ARRAY_BUFFER,numTriangles*9*sizeof(GLfloat),numTriangles*6*sizeof(GLfloat),texture);
		glBufferSubData(GL_ARRAY_BUFFER,numTriangles*15*sizeof(GLfloat),numTriangles*9*sizeof(GLfloat),normal);
		glBufferSubData(GL_ARRAY_BUFFER,numTriangles*24*sizeof(GLfloat),numTriangles*9*sizeof(GLfloat),tangentbuf);
		glBufferSubData(GL_ARRAY_BUFFER,numTriangles*33*sizeof(GLfloat),numTriangles*9*sizeof(GLfloat),bitangentbuf);

		location=QString(filename);
		QStringList fields = location.split('/');
		QString right = fields.takeLast();
		fields = right.split('.');
		name=new QString();
		*name=fields.takeFirst();

		return true;
	}
	return false;
}