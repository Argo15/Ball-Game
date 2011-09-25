#include <QtGui>

#include "ArgoMain.h"

/* Constructor */
ArgoMain::ArgoMain()
{
	QGLFormat fmt;
	fmt.setDirectRendering(true);
	fmt.setDoubleBuffer(true);
	glWidget = new ArgoGLMain(fmt,this);
	fpsLabel=new QLabel("FPS: ?");
	bufferCmb = new QComboBox();
	shaderChk = new QCheckBox("Shaders");
	fpsLabel->setAlignment(Qt::AlignHCenter);

	toolBar = addToolBar(tr("ToolBar"));
	bufferCmb->addItem("Final");
	bufferCmb->addItem("Depth");
	bufferCmb->addItem("Normal");
	bufferCmb->addItem("Color");
	bufferCmb->addItem("Specular");
	bufferCmb->addItem("Lighting");

	toolBar->addWidget(bufferCmb);
	toolBar->addSeparator();
	toolBar->addWidget(shaderChk);

	shaderChk->setCheckState(Qt::Checked);

	setCentralWidget(glWidget);

	createActions();
	createMenus();

	startTimer(0);

	statusBar()->addWidget(fpsLabel);

	DockedActorEditor::Initialize();

	this->addDockWidget(Qt::RightDockWidgetArea,DockedActorEditor::Instance());

	timer.Init();

	connect(bufferCmb, SIGNAL(activated(QString)),this, SLOT(bufferChanged(QString)));
	connect(shaderChk, SIGNAL(clicked()),this, SLOT(shaderChanged()));

	ArgoTextureManager::Initialize();
	ArgoMaterialManager::Initialize();
	ArgoModelManager::Initialize();
	ArgoSceneManager::Initialize();
	ArgoGraphicsSettings::Initialize();

	glWidget->showFullScreen();
}

/* createActions() */
void ArgoMain::createActions()
{
	newAction = new QAction(tr("&New"),this);
	newAction->setIcon(QIcon("Data/Icons/new.png"));
	newAction->setShortcut(QKeySequence::New);
	newAction->setStatusTip(tr("Create a new file"));
	connect(newAction,SIGNAL(triggered()),this,SLOT(newFile()));

	openAction = new QAction(tr("&Open"),this);
	openAction->setIcon(QIcon("Data/Icons/open.png"));
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open a file"));
	connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

	saveAsAction = new QAction(tr("Save &As"),this);
	saveAsAction->setIcon(QIcon("Data/Icons/save.png"));
	saveAsAction->setShortcut(tr("Ctrl+A"));
	saveAsAction->setStatusTip(tr("Save file"));
	connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));

	exitAction = new QAction(tr("E&xit"),this);
	exitAction->setStatusTip(tr("Exit the application"));
	connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

	texManagerAction = new QAction(tr("Texture Manager"),this);
	texManagerAction->setStatusTip(tr("Texture Manager"));
	connect(texManagerAction,SIGNAL(triggered()),this,SLOT(openTextureManager()));

	matManagerAction = new QAction(tr("Material Manager"),this);
	matManagerAction->setStatusTip(tr("Material Manager"));
	connect(matManagerAction,SIGNAL(triggered()),this,SLOT(openMaterialManager()));

	modelManagerAction = new QAction(tr("Model Manager"),this);
	modelManagerAction->setStatusTip(tr("Model Manager"));
	connect(modelManagerAction,SIGNAL(triggered()),this,SLOT(openModelManager()));

	lightManagerAction = new QAction(tr("Light Manager"),this);
	lightManagerAction->setStatusTip(tr("Light Manager"));
	connect(lightManagerAction,SIGNAL(triggered()),this,SLOT(openLightManager()));

	actorManagerAction = new QAction(tr("Actor Manager"),this);
	actorManagerAction->setStatusTip(tr("Actor Manager"));
	connect(actorManagerAction,SIGNAL(triggered()),this,SLOT(openActorManager()));
}

/* createMenus() */
void ArgoMain::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addAction(exitAction);

	editMenu = menuBar()->addMenu(tr("&Edit"));

	toolsMenu = menuBar()->addMenu(tr("&Tools"));
	toolsMenu->addAction(texManagerAction);
	toolsMenu->addAction(matManagerAction);
	toolsMenu->addAction(modelManagerAction);
	toolsMenu->addAction(lightManagerAction);
	toolsMenu->addAction(actorManagerAction);
}

void ArgoMain::newFile()
{
	ArgoSceneManager::Instance()->DeleteScene();
	ArgoModelManager::Instance()->DeleteAllModels();
	ArgoMaterialManager::Instance()->DeleteAllMaterials();
	ArgoTextureManager::Instance()->DeleteAllTextures();
	LoadDefaultScene();

	TextureEditor::Instance()->hide();
	MaterialEditor::Instance()->hide();
	ModelEditor::Instance()->hide();
	LightEditor::Instance()->hide();
	TextureEditor::Initialize(glWidget);
	MaterialEditor::Initialize(glWidget);
	ModelEditor::Initialize(glWidget);
	LightEditor::Initialize(glWidget);
}

void ArgoMain::open()
{
	QString filename =  QFileDialog::getOpenFileName(this, "Open","Data/Saves",tr("*.ascn"));
	if (!filename.isEmpty()){
		ArgoSceneManager::Instance()->DeleteScene();
		ArgoModelManager::Instance()->DeleteAllModels();
		ArgoMaterialManager::Instance()->DeleteAllMaterials();
		ArgoTextureManager::Instance()->DeleteAllTextures();

		ArgoSaveFile open;
		open.openScene(qPrintable(filename));

		TextureEditor::Instance()->hide();
		MaterialEditor::Instance()->hide();
		ModelEditor::Instance()->hide();
		LightEditor::Instance()->hide();
		TextureEditor::Initialize(glWidget);
		MaterialEditor::Initialize(glWidget);
		ModelEditor::Initialize(glWidget);
		LightEditor::Initialize(glWidget);
	}
}

void ArgoMain::saveAs()
{
	QString filename =  QFileDialog::getSaveFileName(this, "Save As","Data/Saves",tr("*.ascn"));
	if (!filename.isEmpty()){
		ArgoSaveFile save;
		save.saveScene(qPrintable(filename));
	}
}

void ArgoMain::bufferChanged(QString buf)
{
	glWidget->setBuffer(buf);
}

void ArgoMain::shaderChanged()
{
	ArgoGraphicsSettings::Instance()->setShadersEnabled(!ArgoGraphicsSettings::Instance()->shadersEnabled());
}

void ArgoMain::openTextureManager()
{
	TextureEditor::Instance()->show();
}

void ArgoMain::openMaterialManager()
{
	MaterialEditor::Instance()->show();
}

void ArgoMain::openModelManager()
{
	ModelEditor::Instance()->show();
}

void ArgoMain::openLightManager()
{
	LightEditor::Instance()->show();
}

void ArgoMain::openActorManager()
{
	DockedActorEditor::Instance()->show();
}

void ArgoMain::timerEvent(QTimerEvent *event)
{
	static float time = 0;
	static int frameCount = 0;
	float fps = timer.GetFPS();
	time+=1.0/fps;
	frameCount++;
	if (time>1.0){
		fpsLabel->setText("FPS: " + QString::number((int)(frameCount)));
		time=0;
		frameCount=0;
	}
	glWidget->setFPS(fps);
	glWidget->repaint();
}

void ArgoMain::closeEvent(QCloseEvent *event)
{
	exit(0);
}