#include "Model.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void Model::draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	glBindBufferARB(GL_ARRAY_BUFFER,bufferID);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(numTriangles*9*sizeof(GLfloat)));
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(numTriangles*15*sizeof(GLfloat)));
	glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(numTriangles*24*sizeof(GLfloat)));
	glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(numTriangles*33*sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, numTriangles*3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}

void Model::drawNoShaders()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glClientActiveTextureARB(GL_TEXTURE0_ARB); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glBindBufferARB(GL_ARRAY_BUFFER,bufferID);
	glVertexPointer(3,GL_FLOAT,0,0);
	glTexCoordPointer(2,GL_FLOAT,0,BUFFER_OFFSET(numTriangles*9*sizeof(GLfloat)));
	glNormalPointer(GL_FLOAT,0,BUFFER_OFFSET(numTriangles*15*sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, numTriangles*3);
}

bool Model::load(const char *filename)
{
	ifstream file(filename, ios::in|ios::binary|ios::ate);
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

		glGenBuffers(1,&bufferID);
		glBindBuffer(GL_ARRAY_BUFFER,bufferID);
		glBufferData(GL_ARRAY_BUFFER,numTriangles*42*sizeof(GLfloat), NULL,GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER,0,numTriangles*9*sizeof(GLfloat),vertex);
		glBufferSubData(GL_ARRAY_BUFFER,numTriangles*9*sizeof(GLfloat),numTriangles*6*sizeof(GLfloat),texture);
		glBufferSubData(GL_ARRAY_BUFFER,numTriangles*15*sizeof(GLfloat),numTriangles*9*sizeof(GLfloat),normal);
		glBufferSubData(GL_ARRAY_BUFFER,numTriangles*24*sizeof(GLfloat),numTriangles*9*sizeof(GLfloat),tangentbuf);
		glBufferSubData(GL_ARRAY_BUFFER,numTriangles*33*sizeof(GLfloat),numTriangles*9*sizeof(GLfloat),bitangentbuf);

		file.close();

		return true;
	}
	return false;
}