#include "DockedActorWidget.h"
#include "ArgoMaterialManager.h"
#include "ArgoModelManager.h"
#include "ArgoSceneManager.h"
#include "MaterialEditor.h"

DockedActorWidget::DockedActorWidget() 
	: QWidget(0)
{
	currentActor = 0;

	matCmb = new QComboBox;
	modelCmb = new QComboBox;

	editMatBtn = new QPushButton("Edit");

	nameEdt = new QLineEdit;
	posXEdt = new QLineEdit;
	posYEdt = new QLineEdit;
	posZEdt = new QLineEdit;
	rotXEdt = new QLineEdit;
	rotYEdt = new QLineEdit;
	rotZEdt = new QLineEdit;
	scaleXEdt = new QLineEdit;
	scaleYEdt = new QLineEdit;
	scaleZEdt = new QLineEdit;

	tableWidget = new QTableWidget(5, 3, this);
	tableWidget->horizontalHeader()->hide();
	nameHdr = new QTableWidgetItem("Name");
	modelHdr = new QTableWidgetItem("Model");
	materialHdr = new QTableWidgetItem("Material");
	transHdr = new QTableWidgetItem("Position");
	scaleHdr = new QTableWidgetItem("Scale");
	tableWidget->setVerticalHeaderItem(0,nameHdr);
	tableWidget->setVerticalHeaderItem(1,modelHdr);
	tableWidget->setVerticalHeaderItem(2,materialHdr);
	tableWidget->setVerticalHeaderItem(3,transHdr);
	tableWidget->setVerticalHeaderItem(4,scaleHdr);
	tableWidget->setSpan(0,0,1,3);
	tableWidget->setSpan(1,0,1,3);
	tableWidget->setSpan(2,0,1,2);
	tableWidget->setColumnWidth(0,60);
	tableWidget->setColumnWidth(1,60);
	tableWidget->setColumnWidth(2,60);
	tableWidget->resizeRowsToContents();
	tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	tableWidget->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
	tableWidget->setFixedHeight(tableWidget->verticalHeader()->sizeHint().height()*5);

	tableWidget->setCellWidget(0,0,nameEdt);
	tableWidget->setCellWidget(1,0,modelCmb);
	tableWidget->setCellWidget(2,0,matCmb);
	tableWidget->setCellWidget(2,2,editMatBtn);
	tableWidget->setCellWidget(3,0,posXEdt);
	tableWidget->setCellWidget(3,1,posYEdt);
	tableWidget->setCellWidget(3,2,posZEdt);
	tableWidget->setCellWidget(4,0,scaleXEdt);
	tableWidget->setCellWidget(4,1,scaleYEdt);
	tableWidget->setCellWidget(4,2,scaleZEdt);

	QVBoxLayout *mainLayout = new QVBoxLayout;

	mainLayout->addWidget(tableWidget);

	setLayout(mainLayout);

	connect(nameEdt,SIGNAL(textChanged(QString)),this,SLOT(nameChanged(QString)));
	connect(matCmb, SIGNAL(activated(QString)),this, SLOT(currentMatChanged(QString)));
	connect(modelCmb, SIGNAL(activated(QString)),this, SLOT(currentModelChanged(QString)));
	connect(editMatBtn, SIGNAL(clicked()),this, SLOT(editMaterial()));
	connect(posXEdt, SIGNAL(textEdited(QString)),this, SLOT(changePosition()));
	connect(posYEdt, SIGNAL(textEdited(QString)),this, SLOT(changePosition()));
	connect(posZEdt, SIGNAL(textEdited(QString)),this, SLOT(changePosition()));
	connect(scaleXEdt, SIGNAL(textEdited(QString)),this, SLOT(changeScale()));
	connect(scaleYEdt, SIGNAL(textEdited(QString)),this, SLOT(changeScale()));
	connect(scaleZEdt, SIGNAL(textEdited(QString)),this, SLOT(changeScale()));

	layout()->setContentsMargins(0,0,0,0);
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());
}

void DockedActorWidget::createFromActor(ArgoActor *actor)
{
	if (!actor)
		return;

	currentActor = actor->getName();

	QMap<QString,ArgoModel *> *modelMap = ArgoModelManager::Instance()->getModels();
	QMap<QString, ArgoModel *>::iterator imodel;
	modelCmb->clear();
	int index=0;
	int modelIndex=0;
	for (imodel = modelMap->begin(); imodel != modelMap->end(); ++imodel){
		modelCmb->addItem(qPrintable(*imodel.value()->getName()));
		if ((imodel.value()->getName())==*actor->getModel())
			modelIndex=index;
		index++;
	}
	modelCmb->setCurrentIndex(modelIndex);

	QMap<QString,ArgoMaterial *> *matMap = ArgoMaterialManager::Instance()->getMaterials();
	QMap<QString, ArgoMaterial *>::iterator imat;
	matCmb->clear();
	index=0;
	int matIndex=0;
	for (imat = matMap->begin(); imat != matMap->end(); ++imat){
		matCmb->addItem(qPrintable(*imat.value()->getName()));
		if ((imat.value()->getName())==*actor->getMaterial())
			matIndex=index;
		index++;
	}
	matCmb->setCurrentIndex(matIndex);

	nameEdt->setText(*actor->getName());
	posXEdt->setText(QString::number(actor->getTranslate()[0]));
	posYEdt->setText(QString::number(actor->getTranslate()[1]));
	posZEdt->setText(QString::number(actor->getTranslate()[2]));
	scaleXEdt->setText(QString::number(actor->getScale()[0]));
	scaleYEdt->setText(QString::number(actor->getScale()[1]));
	scaleZEdt->setText(QString::number(actor->getScale()[2]));
}

void DockedActorWidget::updateWidget() {
	if (currentActor == 0)
		return;
	createFromActor(ArgoSceneManager::Instance()->getActor(*currentActor));
}

void DockedActorWidget::nameChanged(QString name)
{
	if (currentActor == 0)
		return;
	ArgoSceneManager::Instance()->RenameActorSmart(*currentActor,name);
}

void DockedActorWidget::currentMatChanged(QString mat) {
	if (currentActor == 0)
		return;
	ArgoSceneManager::Instance()->getActor(*currentActor)->setMaterial(ArgoMaterialManager::Instance()->getMaterial(mat)->getName());
}

void DockedActorWidget::currentModelChanged(QString model) {
	if (currentActor == 0)
		return;
	ArgoSceneManager::Instance()->getActor(*currentActor)->setModel(ArgoModelManager::Instance()->getModel(model)->getName());
}

void DockedActorWidget::editMaterial() {
	if (currentActor == 0)
		return;
	MaterialEditor::Instance()->currentMatChanged(*ArgoSceneManager::Instance()->getActor(*currentActor)->getMaterial());
	MaterialEditor::Instance()->show();
}

void DockedActorWidget::changePosition() {
	if (currentActor == 0)
		return;
	ArgoActor *actor = ArgoSceneManager::Instance()->getActor(*currentActor);
	actor->setTranslate(posXEdt->text().toFloat(),
						posYEdt->text().toFloat(),
						posZEdt->text().toFloat());
}

void DockedActorWidget::changeScale() {
	if (currentActor == 0)
		return;
	ArgoActor *actor = ArgoSceneManager::Instance()->getActor(*currentActor);
	actor->setScale(scaleXEdt->text().toFloat(),
					scaleYEdt->text().toFloat(),
					scaleZEdt->text().toFloat());
}