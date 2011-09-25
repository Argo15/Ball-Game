#ifndef DOCKEDACTOREDITOR_H
#define DOCKEDACTOREDITOR_H

#include <QGLWidget>
#include <QtGui>
#include "DockedActorEditorMainWidget.h"

class DockedActorEditorMainWidget;

class DockedActorEditor : public QDockWidget
{
    Q_OBJECT

private: 
	DockedActorEditor();
	static DockedActorEditor* pInstance;

	DockedActorEditorMainWidget *mainWidget;

public:
	static DockedActorEditor* Instance();
    static void Initialize();

	DockedActorEditorMainWidget *getMainWidget() {return mainWidget;}
};

#endif