#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
#include "ArgoObjModel.h"

bool ArgoObjModel::load(QString filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly)){
		std::cerr << "Cannot open file for reading: "
			<< qPrintable(filename) << " " << qPrintable(file.errorString()) << std::endl;
		return false;
	}
	vector<float> verticies;
	vector<float> texcoords;
	vector<float> normals;
	vector<int> faces;
	float max[3];
	float min[3];
	for (int i=0;i<3;i++){
		max[i]=-1000000000;
		min[i]= 1000000000;
	}
	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		QStringList fields = line.split(' ');
		QString first = fields.takeFirst();
		if (first == "v")
			for (int i=0; i<3; i++)
			{
				float vert = fields.takeFirst().toFloat();
				if(vert>max[i])
					max[i]=vert;
				if(vert<min[i])
					min[i]=vert;
				verticies.push_back(vert);
			}
		if (first == "vt")
			for (int i=0; i<2; i++)
				texcoords.push_back(fields.takeFirst().toFloat());
		if (first == "vn")
			for (int i=0; i<3; i++)
				normals.push_back(fields.takeFirst().toFloat());
		if (first == "f"){
			if (texcoords.empty()){
				std::cerr << "Cannot load model"
					<< qPrintable(filename) << std::endl << "Requires texture coordinates";
			return false;
			}
			if (normals.empty()){
				std::cerr << "Cannot load model"
					<< qPrintable(filename) << std::endl << "Requires normal vectors";
			return false;
			}
			for (int i=0; i<3; i++){
				QString face = fields.takeFirst();
				QStringList fFields = face.split('/');
				for (int j=0; j<3; j++)
					faces.push_back(fFields.takeFirst().toInt());
			}
		}
	}
	file.close();

	for (int i=0;i<3;i++)
		center[i]=(min[i]+max[i])/2.0;

	numTriangles=faces.size()/9;

	GLfloat *vertexbuf = new GLfloat[numTriangles*9];
	GLfloat *texturebuf = new GLfloat[numTriangles*6];
	GLfloat *normalbuf = new GLfloat[numTriangles*9];
	GLfloat *notangentbuf = new GLfloat[numTriangles*9];
	float dist;

	for (int i=0; i<numTriangles*3 ; i++){
			vertexbuf[i*3]=verticies[(faces[i*3]-1)*3]-center[0];
			vertexbuf[i*3+1]=verticies[(faces[i*3]-1)*3+1]-center[1];
			vertexbuf[i*3+2]=verticies[(faces[i*3]-1)*3+2]-center[2];
			texturebuf[i*2]=texcoords[(faces[i*3+1]-1)*2];
			texturebuf[i*2+1]=texcoords[(faces[i*3+1]-1)*2+1];
			normalbuf[i*3]=normals[(faces[i*3+2]-1)*3];
			normalbuf[i*3+1]=normals[(faces[i*3+2]-1)*3+1];
			normalbuf[i*3+2]=normals[(faces[i*3+2]-1)*3+2];
			notangentbuf[i*3]=0;
			notangentbuf[i*3+1]=0;
			notangentbuf[i*3+2]=0;

			dist=sqrt(pow(vertexbuf[i*3],2)+pow(vertexbuf[i*3+1],2)+pow(vertexbuf[i*3+2],2));

			if(dist>radius)
				radius=dist;
	}

	verticies.clear();
	texcoords.clear();
	normals.clear();
	faces.clear();

	for (int i=0;i<3;i++)
		center[i]=0.0;

	glGenBuffers(1,&bufferID);
	glBindBuffer(GL_ARRAY_BUFFER,bufferID);
	glBufferData(GL_ARRAY_BUFFER,numTriangles*42*sizeof(GLfloat), NULL,GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER,0,numTriangles*9*sizeof(GLfloat),vertexbuf);
	glBufferSubData(GL_ARRAY_BUFFER,numTriangles*9*sizeof(GLfloat),numTriangles*6*sizeof(GLfloat),texturebuf);
	glBufferSubData(GL_ARRAY_BUFFER,numTriangles*15*sizeof(GLfloat),numTriangles*9*sizeof(GLfloat),normalbuf);
	glBufferSubData(GL_ARRAY_BUFFER,numTriangles*24*sizeof(GLfloat),numTriangles*9*sizeof(GLfloat),notangentbuf);
	glBufferSubData(GL_ARRAY_BUFFER,numTriangles*33*sizeof(GLfloat),numTriangles*9*sizeof(GLfloat),notangentbuf);

	location=QString(filename);
	QStringList fields = location.split('/');
	QString right = fields.takeLast();
	fields = right.split('.');
	name=new QString();
	*name=fields.takeFirst();

	delete [] vertexbuf;
	delete [] texturebuf;
	delete [] normalbuf;
	delete [] notangentbuf;

	return true;
}