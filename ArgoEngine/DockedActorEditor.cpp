#include "DockedActorEditor.h"

DockedActorEditor *DockedActorEditor::pInstance = 0;

void DockedActorEditor::Initialize()
{
	if (pInstance != 0) {
		delete pInstance;
	}
	pInstance=new DockedActorEditor();
}

DockedActorEditor *DockedActorEditor::Instance()
{
	return pInstance;
}

DockedActorEditor::DockedActorEditor()
	: QDockWidget("Actor Manager")
{
	mainWidget = new DockedActorEditorMainWidget();

	setWidget(mainWidget);
}