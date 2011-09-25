#ifndef DOCKEDACTOREDITORMAINWIDGET_H
#define DOCKEDACTOREDITORMAINWIDGET_H

#include <QGLWidget>
#include <QtGui>

class DockedActorWidget;
class DockedObjectWidget;

class DockedActorEditorMainWidget : public QWidget {
private:
	DockedActorWidget *actorWidget;
	DockedObjectWidget *objectWidget;

public:
	DockedActorEditorMainWidget();
	~DockedActorEditorMainWidget(){}

	void hideAll();

	DockedActorWidget *getActorWidget();
	DockedObjectWidget *getObjectWidget();
};

#endif