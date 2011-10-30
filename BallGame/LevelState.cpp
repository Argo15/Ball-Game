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
	glEnable(GL_CULL_FACE);

	view = new View();
	frustum = new Frustum();

	camera = new Camera();
	camera->setRotSpeed(2.0);
	camera->updateFromDistance();
	lastCamera = new Camera();

	cascadedShadowMap = new CascadedShadowMap(1024);

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

	log="";
	lightBuffer = new LightBuffer(1280,720);
	dLightProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_dlight.glsl");
	if (!dLightProg->vertex_->isCompiled()){
		dLightProg->vertex_->getShaderLog(log);
	}
	if (!dLightProg->fragment_->isCompiled()){	
		dLightProg->fragment_->getShaderLog(log);
	}
	printf(log.c_str());

	log="";
	pLightProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_plight.glsl");
	if (!pLightProg->vertex_->isCompiled()){
		pLightProg->vertex_->getShaderLog(log);
	}
	if (!pLightProg->fragment_->isCompiled()){	
		pLightProg->fragment_->getShaderLog(log);
	}
	printf(log.c_str());

	log="";
	finalBuffer = new FinalBuffer(1280,720);
	finalProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_final.glsl");
	if (!finalProg->vertex_->isCompiled()){
		finalProg->vertex_->getShaderLog(log);
	}
	if (!finalProg->fragment_->isCompiled()){	
		finalProg->fragment_->getShaderLog(log);
	}
	printf(log.c_str());

	log="";
	hBlurBuffer = new ColorBuffer(1280,720);
	hBlurProg = new GLSLProgram("Data/Shaders/v_GBlur.glsl","Data/Shaders/f_gBlurHor.glsl");
	if (!hBlurProg->vertex_->isCompiled()){
		hBlurProg->vertex_->getShaderLog(log);
	}
	if (!hBlurProg->fragment_->isCompiled()){	
		hBlurProg->fragment_->getShaderLog(log);
	}
	printf(log.c_str());

	log="";
	glowBlurBuffer = new ColorBuffer(1280,720);
	vBlurProg = new GLSLProgram("Data/Shaders/v_GBlur.glsl","Data/Shaders/f_gBlurVert.glsl");
	if (!vBlurProg->vertex_->isCompiled()){
		vBlurProg->vertex_->getShaderLog(log);
	}
	if (!vBlurProg->fragment_->isCompiled()){	
		vBlurProg->fragment_->getShaderLog(log);
	}
	printf(log.c_str());
	glowEnabled = false;

	log="";
	motionBlurBuffer = new ColorBuffer(1280,720);
	mBlurProg = new GLSLProgram("Data/Shaders/v_GBlur.glsl","Data/Shaders/f_motionBlur.glsl");
	if (!mBlurProg->vertex_->isCompiled()){
		mBlurProg->vertex_->getShaderLog(log);
	}
	if (!mBlurProg->fragment_->isCompiled()){	
		mBlurProg->fragment_->getShaderLog(log);
	}
	printf(log.c_str());

	calcShadows = true;
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
	level->getLastTransforms();
	level->updateDynamicsWorld(keys,camera,fps);
	frustum->getFrustum(camera,view);
	cascadedShadowMap->buildShadowMaps(camera, view, frustum, level);
	PointLight **lights;
	int lightCount;
	if (calcShadows){
		lights = new PointLight*[100];
		lightCount = level->getAllPointLights(lights);
	} else {
		lights = new PointLight*[3];
		lightCount = level->getBestPointLights(lights,frustum,camera,2);
	}
	for (int i=0; i< lightCount; i++) {
		lights[i]->buildShadowMaps(frustum,level);
	}

	if (level->distanceFromEnd() < endDistance) {
		onFinish();
	}
}

void LevelState::render() {
	view->use3D(true);
	glLoadIdentity();

	camera->transform();

	glEnable(GL_LIGHTING);

	if (Globals::RENDERSTATE == NOSHADERS) {
		glColor3f(1.0,1.0,1.0);
		level->getDirectLight()->sendToShader(0);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		level->drawNoShaders(frustum);
	} else {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			lastCamera->transform();
			glMatrixMode(GL_TEXTURE);
			glActiveTextureARB(GL_TEXTURE1);
			glLoadIdentity();
			ArgoMatrix4 MV;
			MV.setAsModelViewMatrix();
			MV.multiplyToCurrent();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		gBuffer->bind();
			GLenum mrt[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT };
			glDrawBuffers(4, mrt);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glPushAttrib( GL_VIEWPORT_BIT );
			glViewport( 0, 0, gBuffer->getWidth(), gBuffer->getHeight());
			glEnable(GL_COLOR_MATERIAL);
			glDisable(GL_LIGHTING);
			glColor3f(0.0,0.0,0.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(0.0,0.0,-29.9);
			drawScreen(-100.0,-100.0,100.0,100.0);
			glLoadIdentity();
			camera->transform();
			glEnable(GL_LIGHTING);
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

		if (glowEnabled != keys['g']) {
			blurTexture(glowBlurBuffer,gBuffer->getGlowTex(),4.0);
		}

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

		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD,GL_FUNC_ADD);

		lightBuffer->bind();
			dLightProg->use();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glPushAttrib( GL_VIEWPORT_BIT );
				GLenum mrtLight[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
				glDrawBuffers(2, mrtLight);
				glViewport( 0, 0, lightBuffer->getWidth(), lightBuffer->getHeight());
				view->use3D(false);	
				glActiveTexture(GL_TEXTURE0); 
				gBuffer->bindDepthTex();
				glActiveTexture(GL_TEXTURE1); 
				gBuffer->bindNormalTex();
				glActiveTexture(GL_TEXTURE2); 
				gBuffer->bindColorTex();
				glActiveTexture(GL_TEXTURE3);
				if (glowEnabled != keys['g'])
					glowBlurBuffer->bindTexture();
				else
					gBuffer->bindGlowTex();
				dLightProg->sendUniform("depthTex",0);
				dLightProg->sendUniform("normalTex",1);
				dLightProg->sendUniform("colorTex",2);
				dLightProg->sendUniform("glowTex",3);
				dLightProg->sendUniform("cameraPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());
				dLightProg->sendUniform("near",view->getNear());
				dLightProg->sendUniform("far",view->getFar());
				float dir[4] = {-1.0,-2.0,-3.0,0.0};
				glLightfv(GL_LIGHT0,GL_POSITION,dir);
				level->getDirectLight()->sendToShader(dLightProg);
				cascadedShadowMap->sendToShader(dLightProg,view);
				drawScreen(0.0,0.0,1.0,1.0);
				glPopAttrib();
			dLightProg->disable();
		lightBuffer->unbind();

		PointLight **lights = new PointLight*[4];
		int lightCount = level->getBestPointLights(lights,frustum,camera,4);
		for (int i=0; i< lightCount; i++) {
			lightBuffer->bind();
			pLightProg->use();
				glClear(GL_DEPTH_BUFFER_BIT);
				glPushAttrib( GL_VIEWPORT_BIT );
				GLenum mrtLight[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
				glDrawBuffers(2, mrtLight);
				glViewport( 0, 0, lightBuffer->getWidth(), lightBuffer->getHeight());
				view->use3D(false);	
				glActiveTexture(GL_TEXTURE0); 
				gBuffer->bindDepthTex();
				glActiveTexture(GL_TEXTURE1); 
				gBuffer->bindNormalTex();
				glActiveTexture(GL_TEXTURE2); 
				gBuffer->bindColorTex();
				glActiveTexture(GL_TEXTURE3);
				lightBuffer->bindSpecTex();
				glActiveTexture(GL_TEXTURE4);
				lightBuffer->bindLightTex();
				pLightProg->sendUniform("depthTex",0);
				pLightProg->sendUniform("normalTex",1);
				pLightProg->sendUniform("colorTex",2);
				pLightProg->sendUniform("glowTex",3);
				pLightProg->sendUniform("lightTex",4);
				pLightProg->sendUniform("cameraPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());
				lights[i]->sendToShader(pLightProg);
				lights[i]->sendShadowsToShader(pLightProg);
				drawScreen(0.0,0.0,1.0,1.0);
				glPopAttrib();
			pLightProg->disable();
			lightBuffer->unbind();
		}

		glDisable(GL_BLEND);

		finalBuffer->bind();
			finalProg->use();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glPushAttrib( GL_VIEWPORT_BIT );
				glViewport( 0, 0, finalBuffer->getWidth(), finalBuffer->getHeight());
				view->use3D(false);
				glActiveTexture(GL_TEXTURE0); 
				gBuffer->bindColorTex();
				glActiveTexture(GL_TEXTURE1); 
				lightBuffer->bindLightTex();
				glActiveTexture(GL_TEXTURE2); 
				lightBuffer->bindSpecTex();
				finalProg->sendUniform("colorTex",0);
				finalProg->sendUniform("lightTex",1);
				finalProg->sendUniform("specTex",2);
				drawScreen(0.0,0.0,1.0,1.0);
				glPopAttrib();
			finalProg->disable();
		finalBuffer->unbind();

		motionBlurBuffer->bind();
			mBlurProg->use();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glPushAttrib( GL_VIEWPORT_BIT );
				glViewport( 0, 0, finalBuffer->getWidth(), finalBuffer->getHeight());
				view->use3D(false);
				glActiveTexture(GL_TEXTURE0); 
				finalBuffer->bindFinalTex();
				glActiveTexture(GL_TEXTURE1); 
				gBuffer->bindMotionTex();
				mBlurProg->sendUniform("tex",0);
				mBlurProg->sendUniform("velTex",1);
				mBlurProg->sendUniform("numSamples",8.0f);
				drawScreen(0.0,0.0,1.0,1.0);
				glPopAttrib();
			mBlurProg->disable();
		motionBlurBuffer->unbind();

		glDisable(GL_LIGHTING);
		glActiveTextureARB(GL_TEXTURE0);
		level->getMaterials()->getMaterial("Default")->useNoShaders(level->getTextures());
		if (keys['m']) {
			if (Globals::RENDERSTATE == FINAL) finalBuffer->bindFinalTex();
		} else {
			if (Globals::RENDERSTATE == FINAL) motionBlurBuffer->bindTexture();
		}
		if (Globals::RENDERSTATE == DEPTH) depthBuffer->bindLinearDepthTex();
		if (Globals::RENDERSTATE == NORMAL) gBuffer->bindNormalTex();
		if (Globals::RENDERSTATE == COLOR) gBuffer->bindColorTex();
		if (Globals::RENDERSTATE == LIGHTING) lightBuffer->bindLightTex();
		if (Globals::RENDERSTATE == SPECULAR) lightBuffer->bindSpecTex();
		if (Globals::RENDERSTATE == MOTION) gBuffer->bindMotionTex();
		view->use3D(false);
		glLoadIdentity();
		drawScreen(0.0,0.0,1.0,1.0);
	}

	glutSwapBuffers();
	*lastCamera = *camera;
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
		level->draw(gBufferProg,frustum);
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

void LevelState::onFinish() {
	glActiveTextureARB(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void LevelState::blurTexture(ColorBuffer *resultBuffer, GLuint texture, float scale) {
	hBlurBuffer->bind();
		hBlurProg->use();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glPushAttrib( GL_VIEWPORT_BIT );
		glViewport( 0, 0, hBlurBuffer->getWidth(), hBlurBuffer->getHeight());
		view->use3D(false);	
		glActiveTexture(GL_TEXTURE0); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		hBlurProg->sendUniform("tex",0);
		hBlurProg->sendUniform("width",(float)hBlurBuffer->getWidth());
		hBlurProg->sendUniform("size",scale);
		drawScreen(0.0,0.0,1.0,1.0);
		glPopAttrib();
		hBlurProg->disable();
	hBlurBuffer->unbind();

	resultBuffer->bind();
		vBlurProg->use();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glPushAttrib( GL_VIEWPORT_BIT );
		glViewport( 0, 0, resultBuffer->getWidth(), resultBuffer->getHeight());
		view->use3D(false);	
		glActiveTexture(GL_TEXTURE0);
		hBlurBuffer->bindTexture();
		vBlurProg->sendUniform("tex",0);
		vBlurProg->sendUniform("height",(float)resultBuffer->getHeight());
		vBlurProg->sendUniform("size",scale);
		drawScreen(0.0,0.0,1.0,1.0);
		glPopAttrib();
		vBlurProg->disable();
	resultBuffer->unbind();
}