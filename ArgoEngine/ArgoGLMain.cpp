#include <QtOpenGL>
#include <iostream>
using namespace std;

#include "ArgoGLMain.h"
#include "ArgoGraphicsSettings.h"

ArgoGLMain::ArgoGLMain(QGLFormat fmt, QWidget *parent)
    : QGLWidget(fmt,parent)
{
	setFormat(fmt);
	this->setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
	for (int i=0;i<4;i++)
		wsad[i]=false;
	shift=false;
	ctrl=false;
	q_key=false;
	e_key=false;
	this->setAutoBufferSwap(true);
}

void ArgoGLMain::initializeGL()
{
	view = new ArgoView;
	renderer = new ArgoRenderer;
	camera = new ArgoCamera;
	camera->setRotSpeed(2.0);

	myGrid = new grid;
	myGrid->setColor(1.0,1.0,1.0);

	LoadDefaultScene();

	cascadedShadowMap = new ArgoCascadedShadowMap(1024);

	renderer->init();

	frustum = new ArgoFrustum();

    int width = 1280, length = 720;
	gBuffers = new ArgoGBuffer(width,length);
	depthBuffer = new ArgoLinearDepthBuffer(width,length);
	lightBuffer = new ArgoLightBuffer(width,length);
	finalBuffer = new ArgoFinalBuffer(width,length);

	std::string log;
	texProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_texture.glsl");
	if (!texProg->vertex_->isCompiled()){
		texProg->vertex_->getShaderLog(log);
		QMessageBox::information(this, tr("Vertex Shader error"),
								QString(log.c_str()), QMessageBox::Ok);
	}
	if (!texProg->fragment_->isCompiled()){	
		texProg->fragment_->getShaderLog(log);
		QMessageBox::information(this, tr("Fragment Shader error"), QString(log.c_str()), QMessageBox::Ok);
	}

	TextureEditor::Initialize(this);
	MaterialEditor::Initialize(this);
	ModelEditor::Initialize(this);
	LightEditor::Initialize(this);

	bufferName="Final";
}

void ArgoGLMain::resizeGL(int width, int height)
{
	view->viewport(0, 0, width, height);
    GLfloat aspect = GLfloat(width) / height;
	view->set3D(45.0f,aspect,0.01,30);
	view->set2D(-1,1,-1,1,0,-1);
}

void ArgoGLMain::update(float fps)
{
	if (fps>0){
		if (e_key)
			camera->moveUp(fps*0.5);
		if (q_key)
			camera->moveDown(fps*0.5);
		camera->move(wsad,0.5*60.0/fps);
	}
	frustum->getFrustum(camera,view);
	cascadedShadowMap->buildShadowMaps(camera,view,frustum);
	QMap<QString,ArgoPointLight *> *lightMap = ArgoSceneManager::Instance()->getPointLights();
	QMap<QString, ArgoPointLight *>::iterator it;
	for (it = lightMap->begin(); it != lightMap->end(); ++it){
		ArgoPointLight *pLight = it.value();
		if (pLight->isenabled()){
			if (frustum->isInFrustum(pLight->getTranslateV(),pLight->getRadius())) {
				pLight->buildShadowMaps(frustum);
			}
		}
	}
}

void ArgoGLMain::render()
{
	if (!ArgoGraphicsSettings::Instance()->shadersEnabled()) {
		shaderlessRender();
		return;
	} 

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	renderer->clear();
	view->use3D(true);	
	camera->transform();
	gBuffers->bind();
		GLenum mrt[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT };
		glDrawBuffers(3, mrt);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib( GL_VIEWPORT_BIT );
		glViewport( 0, 0, gBuffers->getWidth(), gBuffers->getHeight());
		ArgoMaterialManager::Instance()->UseDefault();
		gBuffers->getProgram()->sendUniform("normalenabled",false);
		myGrid->draw();
		glBindAttribLocation(gBuffers->getProgram()->getHandle(), 0, "v_vertex");
		glBindAttribLocation(gBuffers->getProgram()->getHandle(), 1, "v_texture");
		glBindAttribLocation(gBuffers->getProgram()->getHandle(), 2, "v_normal");
		glBindAttribLocation(gBuffers->getProgram()->getHandle(), 3, "v_tangent");
		glBindAttribLocation(gBuffers->getProgram()->getHandle(), 4, "v_bitangent");
		glBindAttribLocation(gBuffers->getProgram()->getHandle(), 5, "v_color");
		view->use3D(true);
		camera->transform();
		ArgoSceneManager::Instance()->DrawScene(frustum,gBuffers->getProgram());
		glPopAttrib();
	gBuffers->unbind();

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);

	view->use3D(true);
	camera->transform();
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE2);
	glLoadIdentity();
	ArgoMatrix4 invMVP;
	invMVP.setAsModelViewProjection();
	invMVP.multiplyToCurrent();

	depthBuffer->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib( GL_VIEWPORT_BIT );
		glViewport( 0, 0, finalBuffer->getWidth(), finalBuffer->getHeight());
		view->use3D(false);	
		glActiveTexture(GL_TEXTURE0); 
		gBuffers->bindDepthTex();
		depthBuffer->getDepthProgram()->sendUniform("depthTex",0);
		depthBuffer->getDepthProgram()->sendUniform("near",view->getNear());
		depthBuffer->getDepthProgram()->sendUniform("far",view->getFar());
		drawScreen(-1.0,-1.0,1.0,1.0);
		glPopAttrib();
	depthBuffer->unbind();

	ArgoDirectLight *dLight = ArgoSceneManager::Instance()->getDirectLight();

	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD,GL_FUNC_ADD);

	lightBuffer->bind();
	lightBuffer->getDLightProgram()->use();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib( GL_VIEWPORT_BIT );
		GLenum mrtLight[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
		glDrawBuffers(2, mrtLight);
		glViewport( 0, 0, lightBuffer->getWidth(), lightBuffer->getHeight());
		view->use3D(false);	
		glActiveTexture(GL_TEXTURE0); 
		gBuffers->bindDepthTex();
		glActiveTexture(GL_TEXTURE1); 
		gBuffers->bindNormalTex();
		glActiveTexture(GL_TEXTURE2); 
		gBuffers->bindColorTex();
		glActiveTexture(GL_TEXTURE3);
		gBuffers->bindGlowTex();
		lightBuffer->getDLightProgram()->sendUniform("depthTex",0);
		lightBuffer->getDLightProgram()->sendUniform("normalTex",1);
		lightBuffer->getDLightProgram()->sendUniform("colorTex",2);
		lightBuffer->getDLightProgram()->sendUniform("glowTex",3);
		lightBuffer->getDLightProgram()->sendUniform("cameraPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());
		lightBuffer->getDLightProgram()->sendUniform("near",view->getNear());
		lightBuffer->getDLightProgram()->sendUniform("far",view->getFar());
		dLight->sendToShader(lightBuffer->getDLightProgram());
		cascadedShadowMap->sendToShader(lightBuffer->getDLightProgram(),view);
		drawScreen(-1.0,-1.0,1.0,1.0);
		glPopAttrib();
	lightBuffer->getDLightProgram()->disable();
	lightBuffer->unbind();

	QMap<QString,ArgoPointLight *> *lightMap = ArgoSceneManager::Instance()->getPointLights();
	QMap<QString, ArgoPointLight *>::iterator it;
	for (it = lightMap->begin(); it != lightMap->end(); ++it){
		ArgoPointLight *pLight = it.value();
		if (pLight->isenabled()){
			if (frustum->isInFrustum(pLight->getTranslateV(),pLight->getRadius())) {
				lightBuffer->bind();
				lightBuffer->getPLightProgram()->use();
					glClear(GL_DEPTH_BUFFER_BIT);
					glPushAttrib( GL_VIEWPORT_BIT );
					GLenum mrtLight[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
					glDrawBuffers(2, mrtLight);
					glViewport( 0, 0, lightBuffer->getWidth(), lightBuffer->getHeight());
					view->use3D(false);	
					glActiveTexture(GL_TEXTURE0); 
					gBuffers->bindDepthTex();
					glActiveTexture(GL_TEXTURE1); 
					gBuffers->bindNormalTex();
					glActiveTexture(GL_TEXTURE2); 
					gBuffers->bindColorTex();
					glActiveTexture(GL_TEXTURE3);
					lightBuffer->bindSpecTex();
					glActiveTexture(GL_TEXTURE4);
					lightBuffer->bindLightTex();
					lightBuffer->getPLightProgram()->sendUniform("depthTex",0);
					lightBuffer->getPLightProgram()->sendUniform("normalTex",1);
					lightBuffer->getPLightProgram()->sendUniform("colorTex",2);
					lightBuffer->getPLightProgram()->sendUniform("glowTex",3);
					lightBuffer->getPLightProgram()->sendUniform("lightTex",4);
					lightBuffer->getPLightProgram()->sendUniform("cameraPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());
					pLight->sendToShader(lightBuffer->getPLightProgram());
					pLight->sendShadowsToShader(lightBuffer->getPLightProgram());
					drawScreen(-1.0,-1.0,1.0,1.0);
					glPopAttrib();
				lightBuffer->getDLightProgram()->disable();
				lightBuffer->unbind();
			}
		}
	}

	finalBuffer->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib( GL_VIEWPORT_BIT );
		glViewport( 0, 0, finalBuffer->getWidth(), finalBuffer->getHeight());
		view->use3D(false);
		glActiveTexture(GL_TEXTURE0); 
		gBuffers->bindColorTex();
		glActiveTexture(GL_TEXTURE1); 
		lightBuffer->bindLightTex();
		glActiveTexture(GL_TEXTURE2); 
		lightBuffer->bindSpecTex();
		finalBuffer->getFinalProgram()->sendUniform("colorTex",0);
		finalBuffer->getFinalProgram()->sendUniform("lightTex",1);
		finalBuffer->getFinalProgram()->sendUniform("specTex",2);
		drawScreen(-1.0,-1.0,1.0,1.0);
		glPopAttrib();
	finalBuffer->unbind();

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE3);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE4);
	glDisable(GL_TEXTURE_2D);

	view->use3D(false);	
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	texProg->use();
	glActiveTexture(GL_TEXTURE0); 
	texProg->sendUniform("tex",0);

	if (bufferName=="Final")		finalBuffer->bindFinalTex();
	if (bufferName=="Depth")		depthBuffer->bindLinearDepthTex();
	if (bufferName=="Normal")		gBuffers->bindNormalTex();
	if (bufferName=="Color")		gBuffers->bindColorTex();
	if (bufferName=="Specular")		lightBuffer->bindSpecTex();
	if (bufferName=="Lighting")		lightBuffer->bindLightTex();

	drawScreen(-1.0,-1.0,1.0,1.0);
	texProg->disable();
	if (glGetError()>0)
		printf("%i\n",glGetError());
}

void ArgoGLMain::shaderlessRender()
{
	glDisable(GL_LIGHTING);
	renderer->clear();
	view->use3D(true);	
	camera->transform();
	ArgoMaterialManager::Instance()->UseDefault();
	myGrid->draw();
	//glEnable(GL_LIGHTING);
	//ArgoDirectLight *dLight = ArgoSceneManager::Instance()->getDirectLight();
	//dLight->sendToShader(0);
	//ArgoSceneManager::Instance()->DrawScene(frustum,0);
	glFlush();
}

void ArgoGLMain::keyPressEvent(QKeyEvent * event) 
{
	switch (event->key()){
	case Qt::Key_W:
		wsad[0]=true;
		break;
	case Qt::Key_S:
		wsad[1]=true;
		break;
	case Qt::Key_A:
		wsad[2]=true;
		break;
	case Qt::Key_D:
		wsad[3]=true;
		break;
	case Qt::Key_Shift:
		shift=true;
		break;
	case Qt::Key_Control:
		ctrl=true;
		break;
	case Qt::Key_E:
		e_key=true;
		break;
	case Qt::Key_Q:
		q_key=true;
		break;
	case Qt::Key_Delete:
		ArgoSceneManager::Instance()->deleteSelected();
		break;
	default:
		break;
	}
}

void ArgoGLMain::keyReleaseEvent (QKeyEvent *event)
{
	switch (event->key()){
	case Qt::Key_W:
		wsad[0]=false;
		break;
	case Qt::Key_S:
		wsad[1]=false;
		break;
	case Qt::Key_A:
		wsad[2]=false;
		break;
	case Qt::Key_D:
		wsad[3]=false;
		break;
	case Qt::Key_Shift:
		shift=false;
		break;
	case Qt::Key_Control:
		ctrl=false;
		break;
	case Qt::Key_E:
		e_key=false;
		break;
	case Qt::Key_Q:
		q_key=false;
		break;
	default:
		break;
	}
}

void ArgoGLMain::mousePressEvent(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();
	if (event->buttons() & Qt::LeftButton){
		if (Transformer::selected == -1)
			ArgoSceneManager::Instance()->setSelected(0);
		view->use3D(true);
		camera->transform();
		Selection::calculateSelection(frustum,x,y);
	}
}

void ArgoGLMain::mouseReleaseEvent(QMouseEvent *event)
{
}

void ArgoGLMain::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();
	if (event->buttons() & Qt::RightButton)
		camera->mouseRotate(x,y);
	else
		camera->noRotate();
	view->use3D(true);
	camera->transform();
	if (event->buttons() & Qt::LeftButton){
		Transformer::calculateTransform(x,y,shift,ctrl);
	} else {
		Selection::calculateSelectedTransformer(x,y);
		Transformer::dragPoint = ArgoVector3(0.0);
	}

}

void ArgoGLMain::wheelEvent(QWheelEvent *event)
{
	float scrollDegrees = event->delta()/8.0;
	camera->zoom((float)scrollDegrees/15);
}

void ArgoGLMain::drawScreen(float x1, float y1, float x2, float y2)
{
	glBegin(GL_QUADS);
			glTexCoord2f(0,0);		 glVertex2f(x1,y1);
			glTexCoord2f(1.0f,0);	 glVertex2f(x2,y1);
			glTexCoord2f(1.0f,1.0f); glVertex2f(x2,y2);
			glTexCoord2f(0,1.0f);	 glVertex2f(x1,y2);
	glEnd();
}