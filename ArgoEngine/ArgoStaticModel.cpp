#include "ArgoStaticModel.h"
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void ArgoStaticModel::draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	glBindBufferARB(GL_ARRAY_BUFFER,bufferID);
	glVertexAttribPointerARB(0,3,GL_FLOAT,GL_FALSE,0,0);
	glVertexAttribPointerARB(1,2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(numTriangles*9*sizeof(GLfloat)));
	glVertexAttribPointerARB(2,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(numTriangles*15*sizeof(GLfloat)));
	glVertexAttribPointerARB(3,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(numTriangles*24*sizeof(GLfloat)));
	glVertexAttribPointerARB(4,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(numTriangles*33*sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, numTriangles*3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}

void ArgoStaticModel::drawSelection()
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