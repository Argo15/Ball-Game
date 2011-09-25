#ifndef ARGOGLMAIN_H
#define ARGOGLMAIN_H

#include <QGLWidget>
#include <QtGui>

#include "ArgoView.h"
#include "ArgoRenderer.h"
#include "ArgoCamera.h"
#include "grid.h"
#include "ArgoObjModel.h"
#include "ArgoTgaTexture.h"
#include "ArgoDepthFBO.h"
#include "ArgoColorFBO.h"
#include "GLSLProgram.h"
#include "GLSLShader.h"
#include "ArgoGBuffer.h"
#include "ArgoLightBuffer.h"
#include "ArgoFinalBuffer.h"
#include "ArgoTextureManager.h"
#include "TextureEditor.h"
#include "ArgoMaterial.h"
#include "ArgoMaterialManager.h"
#include "MaterialEditor.h"
#include "ArgoFrustum.h"
#include "ArgoModelManager.h"
#include "ModelEditor.h"
#include "ArgoSceneManager.h"
#include "ArgoLinearDepthBuffer.h"
#include "Selection.h"
#include "ArgoDirectLight.h"
#include "ArgoCascadedShadowMap.h"
#include "LightEditor.h"
#include "Default.h"

class ArgoGLMain : public QGLWidget
{
    Q_OBJECT

private:
	ArgoView *view;
	ArgoRenderer *renderer;
	ArgoCamera *camera;
	grid *myGrid;
	GLSLProgram *texProg;
	GLSLProgram *shadowProg;
	ArgoGBuffer *gBuffers;
	ArgoLinearDepthBuffer *depthBuffer;
	ArgoLightBuffer *lightBuffer;
	ArgoFinalBuffer *finalBuffer;
	ArgoFrustum *frustum;
	ArgoCascadedShadowMap *cascadedShadowMap;
	
	bool wsad[4];
	bool shift, ctrl;
	bool q_key, e_key;
	float fps;

	QString bufferName;

	void shaderlessRender();

public:
    ArgoGLMain(QGLFormat fmt,QWidget *parent = 0);

	void setBuffer(QString buf) { bufferName = buf; }

protected:
    void initializeGL();
    void resizeGL(int width, int height);
	void paintGL() {update(fps); render();}
	void keyPressEvent (QKeyEvent *event);
	void keyReleaseEvent (QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);	

public:
	void setFPS(float fps) {this->fps=fps;}
    void update(float fps);
	void render();

	void drawScreen(float x1, float y1, float x2, float y2);
};

#endif