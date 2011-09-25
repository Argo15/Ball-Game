#include "ModelWidget.h"
#include "ArgoGraphicsSettings.h"

ModelWidget::ModelWidget(QWidget *parent, const QGLWidget *shareWidget)
 : QGLWidget(parent,shareWidget)
{
	material=new QString();
	model=new QString();
	camera = new ArgoCamera();
	view = new ArgoView();
	camera->setRotSpeed(4.0);
	this->setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
}

void ModelWidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth

	std::string log;
	glslProgram = new GLSLProgram("Data/Shaders/v_material.glsl","Data/Shaders/f_material.glsl");
	if (!glslProgram->vertex_->isCompiled()){
		glslProgram->vertex_->getShaderLog(log);
	}
	if (!glslProgram->fragment_->isCompiled()){	
		glslProgram->fragment_->getShaderLog(log);
	}
}

void ModelWidget::resizeGL(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,width,height);
	GLfloat aspect = GLfloat(width) / height;
	view->set3D(45.0f,aspect,0.1,100);
	glMatrixMode(GL_MODELVIEW);
}

void ModelWidget::paintGL()
{
	if (ArgoGraphicsSettings::Instance()->shadersEnabled()) 
		shaderPaint();
	else
		shaderlessPaint();

	
}

void ModelWidget::shaderPaint()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float direction[] = {-1.0,-2.0,-3.0,0.0};
	float ambient[] = {0.4,0.4,0.4,0.0};
	float diffuse[] = {0.5,0.5,0.5,0.0};
	float specular[] = {1.0,1.0,1.0,0.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glLightfv(GL_LIGHT0,GL_POSITION,direction);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	view->use3D(true);
	camera->transform();
	glslProgram->use();
	glslProgram->sendUniform("lookDir",camera->getLookAt()[0]-camera->geteyeX(),camera->getLookAt()[1]-camera->geteyeY(),camera->getLookAt()[2]-camera->geteyeZ());
	glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");
	glBindAttribLocation(glslProgram->getHandle(), 1, "v_texture");
	glBindAttribLocation(glslProgram->getHandle(), 2, "v_normal");
	glBindAttribLocation(glslProgram->getHandle(), 3, "v_tangent");
	glBindAttribLocation(glslProgram->getHandle(), 4, "v_bitangent");
	glBindAttribLocation(glslProgram->getHandle(), 5, "v_color");
	glVertexAttrib3f(5,1.0,1.0,1.0);
	ArgoMaterialManager::Instance()->UseMaterial(*material,glslProgram);
	ArgoModelManager::Instance()->DrawModel(*model);
	glslProgram->disable();
}

void ModelWidget::shaderlessPaint()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float direction[] = {1.0,2.0,3.0,0.0};
	float ambient[] = {0.2,0.2,0.2,0.0};
	float diffuse[] = {0.5,0.5,0.5,0.0};
	float specular[] = {1.0,1.0,1.0,0.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	view->use3D(true);
	camera->transform();
	glLightfv(GL_LIGHT0,GL_POSITION,direction);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);

	glColor3f(1.0,1.0,1.0);
	ArgoMaterialManager::Instance()->UseMaterial(*material,0);
	ArgoModelManager::Instance()->DrawModelSelection(*model);
}

void ModelWidget::setModel(QString *name)
{
	model=name;
	cameraDist=3.333 * ArgoModelManager::Instance()->getModel(*model)->getRadius();
	camera->setDistance(cameraDist);
	camera->updateFromDistance();
}

void ModelWidget::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();
	if (event->buttons() & Qt::RightButton)
		camera->mouseRotate(x,y);
	else
		camera->noRotate();
	this->repaint();
}

void ModelWidget::wheelEvent(QWheelEvent *event)
{
	float scrollDegrees = event->delta()/600.0;
	camera->zoom((float)scrollDegrees*cameraDist);
	this->repaint();
}