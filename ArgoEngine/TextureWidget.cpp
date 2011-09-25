#include "TextureWidget.h"

TextureWidget::TextureWidget(QWidget *parent, const QGLWidget * shareWidget)
 : QGLWidget(parent,shareWidget)
{
	texture=new QString();
	*texture="";
	view = new ArgoView();
}

void TextureWidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth
}

void TextureWidget::resizeGL(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,width,height);
	view->set2D(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

void TextureWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0,1.0,1.0);
	glDisable(GL_LIGHTING);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE3);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	float white[] = {1.0,1.0,1.0};
	float black[] = {0,0,0};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,white);
	glMaterialfv(GL_FRONT,GL_AMBIENT,white);
	glMaterialfv(GL_FRONT,GL_EMISSION,black);

	view->use3D(false);
	ArgoTextureManager::Instance()->BindTexture(*texture);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);		 glVertex2f(-1.0,-1.0);
		glTexCoord2f(1.0f,0);	 glVertex2f(1.0,-1.0);
		glTexCoord2f(1.0f,1.0f); glVertex2f(1.0,1.0);
		glTexCoord2f(0,1.0f);	 glVertex2f(-1.0,1.0);
	glEnd();
}