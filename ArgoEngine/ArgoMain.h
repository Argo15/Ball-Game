#ifndef ARGOMAIN_H
#define ARGOMAIN_H

#include <QMainWindow>
#include "timer.h"
#include "ArgoGLMain.h"
#include "TextureEditor.h"
#include "LightEditor.h"
#include "ArgoSaveFile.h"
#include "DockedActorEditor.h"
#include "ArgoGraphicsSettings.h"

// Main Window Class
class ArgoMain : public QMainWindow
{
	Q_OBJECT

private:
	ArgoGLMain *glWidget;
	QDockWidget *dockedWidget;
	CTimer timer;

	QComboBox *bufferCmb;
	QCheckBox *shaderChk;

public:
	ArgoMain();


protected:
	void closeEvent(QCloseEvent *event);

// action functions
private slots:
	void newFile();
	void open();
	void saveAs();
	void bufferChanged(QString buf);
	void shaderChanged();
	void openTextureManager();
	void openMaterialManager();
	void openModelManager();
	void openLightManager();
	void openActorManager();

private:
	// create funtions
	void createActions();
	void createMenus();

	// menus, actions, ect..
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *toolsMenu;
	QAction *newAction;
	QAction *openAction;
	QAction *saveAsAction;
	QAction *exitAction;
	QAction *texManagerAction;
	QAction *matManagerAction;
	QAction *modelManagerAction;
	QAction *lightManagerAction;
	QAction *actorManagerAction;

	QToolBar *toolBar;

	QLabel *fpsLabel;

protected:
	void timerEvent(QTimerEvent *event);

};

#endif