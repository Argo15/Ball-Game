#include "DockedActorEditorMainWidget.h"
#include "DockedObjectWidget.h"
#include "DockedActorWidget.h"

DockedActorEditorMainWidget::DockedActorEditorMainWidget() 
	: QWidget(0)
{
	actorWidget = new DockedActorWidget;
	objectWidget = new DockedObjectWidget;

	QVBoxLayout *mainLayout = new QVBoxLayout;

	mainLayout->addWidget(actorWidget);
	mainLayout->addWidget(objectWidget);
	mainLayout->addStretch();

	setLayout(mainLayout);
	layout()->setContentsMargins(0,0,0,0);

	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());
}

void DockedActorEditorMainWidget::hideAll()
{
	actorWidget->hide();
	objectWidget->hide();
}

DockedActorWidget *DockedActorEditorMainWidget::getActorWidget()
{
	return actorWidget;
}

DockedObjectWidget *DockedActorEditorMainWidget::getObjectWidget()
{
	return objectWidget;
}