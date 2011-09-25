#include "ModelEditor.h"
#include "DockedActorWidget.h"

ModelEditor *ModelEditor::pInstance = 0;

void ModelEditor::Initialize(QGLWidget *parent)
{
	if (pInstance != 0) {
		delete pInstance;
	}
	pInstance=new ModelEditor(parent);
}

ModelEditor *ModelEditor::Instance()
{
	return pInstance;
}

ModelEditor::ModelEditor(QGLWidget *parent)
	: QDialog(parent)
{
	modelWidget = new ModelWidget(this,parent);
	modelWidget->setFixedWidth(300);
	modelWidget->setFixedHeight(400);
	currentModel=ArgoModelManager::Instance()->getDefault()->getName();
	currentMat=ArgoMaterialManager::Instance()->getDefault()->getName();
	modelWidget->setModel(currentModel);
	modelWidget->setMaterial(currentMat);

	nameEdt = new QLineEdit(qPrintable(*currentModel));

	modelLbl = new QLabel("Model: ");
	modelLbl->setFixedWidth(100);
	matLbl = new QLabel("Preview Material: ");
	matLbl->setFixedWidth(100);

	modelCmb = new QComboBox;
	matCmb = new QComboBox;

	loadModelBtn = new QPushButton("Load Model");
	addToSceneBtn = new QPushButton("Add To Scene");

	QHBoxLayout *mainLayout = new QHBoxLayout;
		QVBoxLayout *modelLayout = new QVBoxLayout;
			QHBoxLayout *modelListLayout = new QHBoxLayout;
			QHBoxLayout *matListLayout = new QHBoxLayout;

	modelListLayout->addWidget(modelLbl);
	modelListLayout->addWidget(modelCmb);

	matListLayout->addWidget(matLbl);
	matListLayout->addWidget(matCmb);

	modelLayout->addWidget(nameEdt);
	modelLayout->addWidget(modelWidget);
	modelLayout->addLayout(modelListLayout);
	modelLayout->addLayout(matListLayout);
	modelLayout->addWidget(loadModelBtn);
	modelLayout->addWidget(addToSceneBtn);

	mainLayout->addLayout(modelLayout);

	setLayout(mainLayout);

	connect(modelCmb, SIGNAL(activated(QString)),this, SLOT(currentModelChanged(QString)));
	connect(matCmb, SIGNAL(activated(QString)),this, SLOT(currentMatChanged(QString)));
	connect(loadModelBtn, SIGNAL(clicked()),this, SLOT(loadModel()));
	connect(addToSceneBtn, SIGNAL(clicked()),this, SLOT(addToScene()));
	connect(nameEdt, SIGNAL(textChanged(QString)),this,SLOT(nameChanged(QString)));


	setWindowTitle(tr("Model Manager"));
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());

	updateEditor();
}

void ModelEditor::updateEditor()
{
	QMap<QString,ArgoModel *> *modelMap = ArgoModelManager::Instance()->getModels();
	QMap<QString, ArgoModel *>::iterator imodel;
	modelCmb->clear();
	int index=0;
	int modelIndex=0;
	for (imodel = modelMap->begin(); imodel != modelMap->end(); ++imodel){
		modelCmb->addItem(qPrintable(*imodel.value()->getName()));
		if ((imodel.value()->getName())==currentModel)
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
		if ((imat.value()->getName())==currentMat)
			matIndex=index;
		index++;
	}
	matCmb->setCurrentIndex(matIndex);

    modelWidget->setModel(currentModel);
	modelWidget->repaint();
}

void ModelEditor::currentModelChanged(QString model)
{
	currentModel=ArgoModelManager::Instance()->getModel(model)->getName();
	modelWidget->setModel(currentModel);
	nameEdt->setText(qPrintable(*currentModel));
	updateEditor();
}

void ModelEditor::currentMatChanged(QString mat)
{
	currentMat=ArgoMaterialManager::Instance()->getMaterial(mat)->getName();
	modelWidget->setMaterial(currentMat);
	updateEditor();

}

void ModelEditor::addToScene()
{
	ArgoSceneManager::Instance()->AddObject(new ArgoObject(new QString(*currentModel+QString(" Actor")),currentModel,currentMat));
}

void ModelEditor::loadModel()
{
	QString filename = QFileDialog::getOpenFileName(this,tr("Load Object"),"Data/Models/AOBJ",tr("Objects (*.obj *.aobj)"));

	if (!filename.isEmpty()){
		ArgoModelManager::Instance()->LoadModel(filename);
	}
	updateEditor();
}

void ModelEditor::nameChanged(QString name)
{
	ArgoModelManager::Instance()->RenameModel(*currentModel,name);
	updateEditor();
	DockedActorEditor::Instance()->getMainWidget()->getActorWidget()->updateWidget();
}