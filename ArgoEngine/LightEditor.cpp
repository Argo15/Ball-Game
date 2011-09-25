#include "LightEditor.h"

LightEditor *LightEditor::pInstance = 0;

void LightEditor::Initialize(QGLWidget *parent)
{
	if (pInstance != 0) {
		delete pInstance;
	}
	pInstance=new LightEditor(parent);
}

LightEditor *LightEditor::Instance()
{
	return pInstance;
}

LightEditor::LightEditor(QGLWidget *parent)
	: QDialog(parent)
{
	dLightWgt = new DirectLightWidget(parent);
	pLightWgt = new PointLightWidget(parent,parent);

	lightTab = new QTabWidget();

	lightTab->addTab(dLightWgt,QString("Direct Light"));
	lightTab->addTab(pLightWgt,QString("Point Lights"));

	QHBoxLayout *mainLayout = new QHBoxLayout;

	mainLayout->addWidget(lightTab);

	setLayout(mainLayout);

	setWindowTitle(tr("Light Manager"));
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());
}

void LightEditor::updateEditor()
{
	dLightWgt->updateWidget();
	pLightWgt->updateWidget();
}