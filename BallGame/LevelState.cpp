#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "LevelState.h"
#include "Globals.h"
#include "MainMenuState.h"
#include "SoundManager.h"

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

	cascadedShadowMap = new CascadedShadowMap(512);

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

	ballProg = new GLSLProgram("Data/Shaders/v_environment.glsl","Data/Shaders/f_environment.glsl");
	log="";
	if (!ballProg->vertex_->isCompiled()){
		ballProg->vertex_->getShaderLog(log);
	}
	if (!ballProg->fragment_->isCompiled()){	
		ballProg->fragment_->getShaderLog(log);
	}
	printf(log.c_str());

	log="";
	depthBuffer = new LinearDepthBuffer(1280,720);
	depthBlurBuffer = new ColorBuffer(1280,720);
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
	dLightLowProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_dlightlow.glsl");
	if (!dLightLowProg->vertex_->isCompiled()){
		dLightLowProg->vertex_->getShaderLog(log);
	}
	if (!dLightLowProg->fragment_->isCompiled()){	
		dLightLowProg->fragment_->getShaderLog(log);
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
	pLightLowProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_plightlow.glsl");
	if (!pLightLowProg->vertex_->isCompiled()){
		pLightLowProg->vertex_->getShaderLog(log);
	}
	if (!pLightLowProg->fragment_->isCompiled()){	
		pLightLowProg->fragment_->getShaderLog(log);
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

	log="";
	SSAOBuffer = new ColorBuffer(1280,720);
	mSSAOProg = new GLSLProgram("Data/Shaders/v_light.glsl","Data/Shaders/f_ssao.glsl");
	if (!mSSAOProg->vertex_->isCompiled()){
		mSSAOProg->vertex_->getShaderLog(log);
	}
	if (!mSSAOProg->fragment_->isCompiled()){	
		mSSAOProg->fragment_->getShaderLog(log);
	}
	printf(log.c_str());

	calcShadows = true;
	pCube = new ParticleCube();

	//stop the menu music when any level is loaded
	SoundManager::Instance()->stopSound("MenuMusic");

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
	profiler.init();
	profiler.update(fps);
	//update the location of the openal listener
	SoundManager::Instance()->updateListenerPosition(camera);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	profiler.profile("Clear Buffers");
	level->getLastTransforms();
	level->updateDynamicsWorld(keys,camera,fps,&profiler);
	profiler.profile("Update Dynamics World");
	frustum->getFrustum(camera,view);
	cascadedShadowMap->buildShadowMaps(camera, view, frustum, level);
	profiler.profile("Build Cascaded Shadow Maps");
	PointLight **lights;
	int lightCount;
	if (calcShadows){
		lights = new PointLight*[100];
		lightCount = level->getAllPointLights(lights);
	} else {
		lights = new PointLight*[4];
		lightCount = level->getBestPointLights(lights,frustum,camera,4);
	}
	for (int i=0; i< lightCount; i++) {
		lights[i]->buildShadowMaps(frustum,level,calcShadows);
	}
	calcShadows = false;

	profiler.profile("Build Point Light Shadow Maps");

	pCube->Update(level->getStart(),level->getEnd());
	if (level->distanceFromEnd() < endDistance) {
		onFinish();
		return;
	}
	
}

void LevelState::render() {
	profiler.profile("Start Render");
	view->use3D(true);
	glLoadIdentity();

	camera->transform();

	glEnable(GL_LIGHTING);

	if (Globals::RENDERSTATE == NOSHADERS) {
		glDisable(GL_BLEND);
		glColor3f(1.0,1.0,1.0);
		level->getDirectLight()->sendToShader(0);
		PointLight **lights = new PointLight*[4];
		int lightCount = level->getBestPointLights(lights,frustum,camera,4);
		for (int i=0; i<lightCount; i++) {
			glEnable(GL_LIGHT1+i);
			lights[i]->sendToShader(0,GL_LIGHT1+i);
		}
		level->drawNoShaders(frustum);
		pCube->Render();
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
			camera->transform();
			glEnable(GL_LIGHTING);
			renderGBuffer();
			glPopAttrib();
		gBuffer->unbind();

		profiler.profile("Gbuffer Render");

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

		if (Globals::glowEnabled) {
			blurTexture(glowBlurBuffer,gBuffer->getGlowTex(),4.0);
			blurTexture(glowBlurBuffer,glowBlurBuffer->getTexture(),3.0);
			blurTexture(glowBlurBuffer,glowBlurBuffer->getTexture(),2.0);
		}

		profiler.profile("Glow Blur");

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

		profiler.profile("Linear Depth Buffer");

		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD,GL_FUNC_ADD);

		lightBuffer->bind();
			GLSLProgram *dlightProgram;
			if (Globals::highQualityShadows)
				dlightProgram = dLightProg;
			else
				dlightProgram = dLightLowProg;
			dlightProgram->use();
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
				if (Globals::glowEnabled)
					glowBlurBuffer->bindTexture();
				else
					gBuffer->bindGlowTex();
				dlightProgram->sendUniform("depthTex",0);
				dlightProgram->sendUniform("normalTex",1);
				dlightProgram->sendUniform("colorTex",2);
				dlightProgram->sendUniform("glowTex",3);
				dlightProgram->sendUniform("cameraPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());
				dlightProgram->sendUniform("near",view->getNear());
				dlightProgram->sendUniform("far",view->getFar());
				float dir[4] = {-1.0,-2.0,-3.0,0.0};
				glLightfv(GL_LIGHT0,GL_POSITION,dir);
				level->getDirectLight()->sendToShader(dlightProgram);
				cascadedShadowMap->sendToShader(dlightProgram,view);
				drawScreen(0.0,0.0,1.0,1.0);
				glPopAttrib();
			dlightProgram->disable();
		lightBuffer->unbind();

		profiler.profile("Direct Light Shading");

		PointLight **lights = new PointLight*[5];
		int lightCount = level->getBestPointLights(lights,frustum,camera,4);
		GLSLProgram *pointLightProg = pLightLowProg;
		if (Globals::highQualityShadows)
			pointLightProg = pLightProg;
		for (int i=0; i< lightCount; i++) {
			lightBuffer->bind();
			pointLightProg->use();
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
				pointLightProg->sendUniform("depthTex",0);
				pointLightProg->sendUniform("normalTex",1);
				pointLightProg->sendUniform("colorTex",2);
				pointLightProg->sendUniform("glowTex",3);
				pointLightProg->sendUniform("lightTex",4);
				pointLightProg->sendUniform("cameraPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());
				lights[i]->sendToShader(pointLightProg);
				lights[i]->sendShadowsToShader(pointLightProg);
				drawScreen(0.0,0.0,1.0,1.0);
				glPopAttrib();
			pointLightProg->disable();
			lightBuffer->unbind();
		}

		glDisable(GL_BLEND);
		profiler.profile("Point Light Shading");

		if (!Globals::ambientOcclusion) {
			SSAOBuffer->bind();
			glClearColor(1.0,1.0,1.0,1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0,0.0,0.0,1.0);
			SSAOBuffer->unbind();
		} else {
			//blurTexture(depthBlurBuffer,depthBuffer->getDepthTex(),8);
			//blurTexture(depthBlurBuffer,depthBuffer->getDepthTex(),5);
			blurTexture(depthBlurBuffer,depthBuffer->getDepthTex(),4);

			SSAOBuffer->bind();
				mSSAOProg->use();
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glPushAttrib( GL_VIEWPORT_BIT );
					glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
					glViewport( 0, 0, lightBuffer->getWidth(), lightBuffer->getHeight());
					view->use3D(false);	
					glActiveTexture(GL_TEXTURE0); 
					depthBuffer->bindLinearDepthTex();
					glActiveTexture(GL_TEXTURE1); 
					depthBlurBuffer->bindTexture();
					mSSAOProg->sendUniform("depthTex",0);
					mSSAOProg->sendUniform("depthBlurTex",1);
					//mSSAOProg->sendUniform("near",view->getNear());
					//mSSAOProg->sendUniform("far",view->getFar());
					drawScreen(0.0,0.0,1.0,1.0);
					glPopAttrib();
				mSSAOProg->disable();
			SSAOBuffer->unbind();

			blurTexture(SSAOBuffer,SSAOBuffer->getTexture(),5.0);
			blurTexture(SSAOBuffer,SSAOBuffer->getTexture(),3.0);
		}

		profiler.profile("SSAO");

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
				glActiveTexture(GL_TEXTURE3); 
				SSAOBuffer->bindTexture();
				finalProg->sendUniform("colorTex",0);
				finalProg->sendUniform("lightTex",1);
				finalProg->sendUniform("specTex",2);
				finalProg->sendUniform("ssaoTex",3);
				drawScreen(0.0,0.0,1.0,1.0);
				glPopAttrib();
			finalProg->disable();
		finalBuffer->unbind();

		profiler.profile("Final Buffer Generation");

		if (Globals::motionblur) {
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
					mBlurProg->sendUniform("numSamples",10.0f);
					drawScreen(0.0,0.0,1.0,1.0);
					glPopAttrib();
				mBlurProg->disable();
			motionBlurBuffer->unbind();
		}

		profiler.profile("Motion Blur");

		glDisable(GL_LIGHTING);
		glActiveTextureARB(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		level->getMaterials()->getMaterial("Default")->useNoShaders(level->getTextures());
		if (!Globals::motionblur) {
			if (Globals::RENDERSTATE == FINAL) finalBuffer->bindFinalTex();
		} else {
			if (Globals::RENDERSTATE == FINAL) motionBlurBuffer->bindTexture();
		}
		if (Globals::RENDERSTATE == DEPTH) depthBuffer->bindLinearDepthTex();
		if (Globals::RENDERSTATE == NORMAL) gBuffer->bindNormalTex();
		if (Globals::RENDERSTATE == COLOR) gBuffer->bindColorTex();
		if (Globals::RENDERSTATE == LIGHTING) lightBuffer->bindLightTex();
		if (Globals::RENDERSTATE == SSAO) SSAOBuffer->bindTexture();
		if (Globals::RENDERSTATE == SPECULAR) lightBuffer->bindSpecTex();
		if (Globals::RENDERSTATE == MOTION) gBuffer->bindMotionTex();
		view->use3D(false);
		glLoadIdentity();
		drawScreen(0.0,0.0,1.0,1.0);
		if (Globals::showHelp) {
			glDepthFunc(GL_ALWAYS);
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glActiveTexture(GL_TEXTURE0); 
			glDisable(GL_TEXTURE_2D);
			glColor3f(1.0f, 1.0f, 1.0f);
			glRasterPos2f(0.0f,0.34f);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char *)"Right Click to move camera");
			glRasterPos2f(0.0f,0.31f);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char *)"WASD to move");
			glRasterPos2f(0.0f,0.28f);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char *)"G to toggle glow");
			glRasterPos2f(0.0f,0.25f);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char *)"L to toggle lighting quality");
			glRasterPos2f(0.0f,0.22f);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char *)"O to toggle ambient occlusion");
			glRasterPos2f(0.0f,0.19f);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char *)"+ and - to change reflection factor");
			glRasterPos2f(0.0f,0.16f);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char *)"ZXCV to change ball material");
			glRasterPos2f(0.0f,0.13f);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char *)"M to toggle motion blur");
			glRasterPos2f(0.0f,0.10f);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char *)"H to toggle help");
			glDepthFunc(GL_LEQUAL);
		}
		glEnable(GL_TEXTURE_2D);
		profiler.profile("Finish Shader Render");
	}

	glutSwapBuffers();
	*lastCamera = *camera;
	profiler.profile("Finish Render");
}

void LevelState::renderGBuffer() {
	ballProg->use();
		glBindAttribLocation(ballProg->getHandle(), 0, "v_vertex");
		glBindAttribLocation(ballProg->getHandle(), 1, "v_texture");
		glBindAttribLocation(ballProg->getHandle(), 2, "v_normal");
		glBindAttribLocation(ballProg->getHandle(), 3, "v_tangent");
		glBindAttribLocation(ballProg->getHandle(), 4, "v_bitangent");
		glBindAttribLocation(ballProg->getHandle(), 5, "v_color");
		glVertexAttrib3f(5,1.0,1.0,1.0);
		ballProg->sendUniform("cameraPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());
		level->drawBall(ballProg,frustum);
	ballProg->disable();
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
	SoundManager::Instance()->startSound("BeatLevel",false);
	pCube->nullify();
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE0);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	delete gBufferProg;
	delete depthProg;
	delete dLightProg;
	delete dLightLowProg;
	delete pLightProg;
	delete pLightLowProg;
	delete finalProg;
	delete hBlurProg;
	delete vBlurProg;
	delete mBlurProg;
	delete mSSAOProg;
	delete gBuffer;
	delete depthBuffer;
	delete lightBuffer;
	delete SSAOBuffer;
	delete finalBuffer;
	delete hBlurBuffer;
	delete glowBlurBuffer;
	delete motionBlurBuffer;
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	profiler.saveProfile("Data/Profiler.txt");
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_COLOR_MATERIAL);
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