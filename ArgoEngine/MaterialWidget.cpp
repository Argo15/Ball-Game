#include "MaterialWidget.h"
#include "ArgoGraphicsSettings.h"

MaterialWidget::MaterialWidget(QWidget *parent, const QGLWidget * shareWidget)
 : QGLWidget(parent,shareWidget)
{
	material=new QString();
	view = new ArgoView();
}

void MaterialWidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth
	glCullFace(GL_BACK);

	sphereModel = new ArgoAObjModel;
	sphereModel->load("Data/Models/AOBJ/Sphere.aobj");

	std::string log;
	glslProgram = new GLSLProgram("Data/Shaders/v_material.glsl","Data/Shaders/f_material.glsl");
	if (!glslProgram->vertex_->isCompiled()){
		glslProgram->vertex_->getShaderLog(log);
	}
	if (!glslProgram->fragment_->isCompiled()){	
		glslProgram->fragment_->getShaderLog(log);
	}
}

void MaterialWidget::resizeGL(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,width,height);
	GLfloat aspect = GLfloat(width) / height;
	view->set3D(45.0f,aspect,0.1,100);
	glMatrixMode(GL_MODELVIEW);
}

void MaterialWidget::paintGL()
{
	float direction[] = {-1.0,-1.0,1.0,0.0};
	float ambient[] = {0.2,0.2,0.2,0.0};
	float diffuse[] = {0.7,0.7,0.7,0.0};
	float specular[] = {1.0,1.0,1.0,0.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	view->use3D(true);
	glLightfv(GL_LIGHT0,GL_POSITION,direction);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glColor3f(1.0,1.0,1.0);
	glTranslatef(0.0,0.0,-3.0);
	glRotatef(90,1.0,0,0);
	if (ArgoGraphicsSettings::Instance()->shadersEnabled()) {
		glslProgram->use();
		ArgoMaterialManager::Instance()->UseMaterial(*material,glslProgram);
		glslProgram->sendUniform("lookDir",0.0f,-1.0f,0.0f);
		glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");
		glBindAttribLocation(glslProgram->getHandle(), 1, "v_texture");
		glBindAttribLocation(glslProgram->getHandle(), 2, "v_normal");
		glBindAttribLocation(glslProgram->getHandle(), 3, "v_tangent");
		glBindAttribLocation(glslProgram->getHandle(), 4, "v_bitangent");
		glBindAttribLocation(glslProgram->getHandle(), 5, "v_color");
		glVertexAttrib3f(5,1.0,1.0,1.0);
		sphereModel->draw();
		glslProgram->disable();
	} else {
		float direction[] = {1.0,1.0,-1.0,0.0};
		float ambient[] = {0.0,0.0,0.0,0.0};
		float diffuse[] = {0.7,0.7,0.7,0.0};
		glLightfv(GL_LIGHT0,GL_POSITION,direction);
		glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		ArgoMaterialManager::Instance()->UseMaterial(*material,0);
		sphereModel->drawSelection();
	}
}