#include <stdlib.h>
#include <GL/glut.h>
#include "LevelState.h"
#include "Globals.h"
#include "MainMenuState.h"

// init
LevelState::LevelState() {
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);	// Really Nice Perspective Calculations
	glEnable(GL_NORMALIZE);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	view = new View();

	camera = new Camera();
	camera->setRotSpeed(2.0);
	camera->updateFromDistance();

	endDistance = 0.5;

	gBuffer = new GBuffer(1280,720);
	gBufferProg = new GLSLProgram("Data/Shaders/v_GBuffer.glsl","Data/Shaders/f_GBuffer.glsl");
	std::string log;
	if (!gBufferProg->vertex_->isCompiled()){
		gBufferProg->vertex_->getShaderLog(log);
	}
	if (!gBufferProg->fragment_->isCompiled()){	
		gBufferProg->fragment_->getShaderLog(log);
	}
	printf(log.c_str());

	log="";
	depthBuffer = new LinearDepthBuffer(1280,720);
	depthProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_depth.glsl");
	if (!depthProg->vertex_->isCompiled()){
		depthProg->vertex_->getShaderLog(log);
	}
	if (!depthProg->fragment_->isCompiled()){	
		depthProg->fragment_->getShaderLog(log);
	}
	printf(log.c_str());
}

void LevelState::resize(int w, int h) {
	GameState::resize(w,h);
	if(h == 0)
		h = 1;
	GLfloat aspect = GLfloat(w) / h;
	view->viewport(0, 0, w, h);
	view->set3D(45.0f,aspect,0.01,30);
	view->set2D(0,1,0,1,0,1);
}

void LevelState::update(int fps) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	level->updateDynamicsWorld(keys,camera,fps);
	if (level->distanceFromEnd() < endDistance) {
		onFinish();
	}
}

void LevelState::render() {
	view->use3D(true);
	glLoadIdentity();

	camera->transform();

	glEnable(GL_LIGHTING);
	float direction[] = {1.0,2.0,3.0,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,direction);

	if (Globals::RENDERSTATE == NOSHADERS)
		level->drawNoShaders();
	else {
		gBuffer->bind();
			GLenum mrt[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT };
			glDrawBuffers(3, mrt);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glPushAttrib( GL_VIEWPORT_BIT );
			glViewport( 0, 0, gBuffer->getWidth(), gBuffer->getHeight());
			renderGBuffer();
			glPopAttrib();
		gBuffer->unbind();

		glActiveTexture(GL_TEXTURE1);
		glEnable(GL_COLOR_MATERIAL);
		glDisable(GL_LIGHTING);
		glColor3f(1.0,1.0,1.0);

		view->use3D(true);
		camera->transform();
		glMatrixMode(GL_TEXTURE);
		glActiveTextureARB(GL_TEXTURE2);
		glLoadIdentity();
		ArgoMatrix4 invMVP;
		invMVP.setAsModelViewProjection();
		invMVP.multiplyToCurrent();

		depthBuffer->bind();
			depthProg->use();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
			glPushAttrib( GL_VIEWPORT_BIT );
			glViewport( 0, 0, depthBuffer->getWidth(), depthBuffer->getHeight());
			view->use3D(false);	
			glActiveTexture(GL_TEXTURE0); 
			glEnable(GL_TEXTURE_2D);
			
			gBuffer->bindDepthTex();
			depthProg->sendUniform("depthTex",0);
			depthProg->sendUniform("near",view->getNear());
			depthProg->sendUniform("far",view->getFar());
			depthProg->use();
			drawScreen(0.0,0.0,1.0,1.0);
			glPopAttrib();
			depthProg->disable();
		depthBuffer->unbind();

		glDisable(GL_LIGHTING);
		glActiveTextureARB(GL_TEXTURE0);
		level->getMaterials()->getMaterial("Default")->useNoShaders(level->getTextures());
		if (Globals::RENDERSTATE == DEPTH) depthBuffer->bindLinearDepthTex();
		if (Globals::RENDERSTATE == NORMAL) gBuffer->bindNormalTex();
		if (Globals::RENDERSTATE == COLOR) gBuffer->bindColorTex();
		view->use3D(false);
		glLoadIdentity();
		drawScreen(0.0,0.0,1.0,1.0);
	}

	glutSwapBuffers();
}

void LevelState::renderGBuffer() {
	gBufferProg->use();
		glBindAttribLocation(gBufferProg->getHandle(), 0, "v_vertex");
		glBindAttribLocation(gBufferProg->getHandle(), 1, "v_texture");
		glBindAttribLocation(gBufferProg->getHandle(), 2, "v_normal");
		glBindAttribLocation(gBufferProg->getHandle(), 3, "v_tangent");
		glBindAttribLocation(gBufferProg->getHandle(), 4, "v_bitangent");
		glBindAttribLocation(gBufferProg->getHandle(), 5, "v_color");
		glVertexAttrib3f(5,1.0,1.0,1.0);
		level->draw(gBufferProg);
	gBufferProg->disable();
}

void LevelState::mousePressedMove(int x, int y) {
	if (mouse[2])
		camera->mouseRotate(x, y);
}

void LevelState::mouseReleasedMove(int x, int y) {
	camera->noRotate();
}

void LevelState::drawScreen(float x1, float y1, float x2, float y2)
{
	glBegin(GL_QUADS);
			glTexCoord2f(0,0);		 glVertex2f(x1,y1);
			glTexCoord2f(1.0f,0);	 glVertex2f(x2,y1);
			glTexCoord2f(1.0f,1.0f); glVertex2f(x2,y2);
			glTexCoord2f(0,1.0f);	 glVertex2f(x1,y2);
	glEnd();
}