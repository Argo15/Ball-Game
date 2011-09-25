#include "TextureEditor.h"

TextureEditor *TextureEditor::pInstance = 0;

void TextureEditor::Initialize(QGLWidget *parent)
{
	if (pInstance != 0) {
		delete pInstance;
	}
	pInstance=new TextureEditor(parent);
}

TextureEditor *TextureEditor::Instance()
{
	return pInstance;
}

TextureEditor::TextureEditor(QGLWidget *parent)
	: QDialog(parent)
{
	QMap<QString,ArgoTexture *> *texMap = ArgoTextureManager::Instance()->getTextures();
	texWidget = new TextureWidget(this,parent);
	texWidget->setFixedWidth(200);
	texWidget->setFixedHeight(200);
	currentTex=texMap->begin().value()->getName();
	texWidget->setTexture(currentTex);

	nameEdt = new QLineEdit(qPrintable(*currentTex));

	textureCmb = new QComboBox;
	typeCmb = new QComboBox;
	typeCmb->addItem("Diffuse");
	typeCmb->addItem("Normal");

	typeLabel = new QLabel("Type: ");
	typeLabel->setFixedWidth(30);

	loadTextureBtn = new QPushButton("Load Texture");

	QVBoxLayout *mainLayout = new QVBoxLayout;
		QHBoxLayout *typeLayout = new QHBoxLayout;

	typeLayout->addWidget(typeLabel);
	typeLayout->addWidget(typeCmb);

	mainLayout->addWidget(nameEdt);
	mainLayout->addWidget(texWidget);
	mainLayout->addWidget(textureCmb);
	mainLayout->addLayout(typeLayout);
	mainLayout->addWidget(loadTextureBtn);
	

	setLayout(mainLayout);

	setWindowTitle(tr("Texture Manager"));
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());

	connect(textureCmb, SIGNAL(activated(QString)),this, SLOT(currentTexChanged(QString)));
	connect(typeCmb, SIGNAL(activated(QString)),this, SLOT(typeChanged(QString)));
	connect(loadTextureBtn, SIGNAL(clicked()),this, SLOT(loadTexture()));
	connect(nameEdt, SIGNAL(textChanged(QString)),this,SLOT(nameChanged(QString)));

	updateEditor();
}

void TextureEditor::updateEditor()
{
	QMap<QString,ArgoTexture *> *texMap = ArgoTextureManager::Instance()->getTextures();

	QMap<QString, ArgoTexture *>::iterator i;
	textureCmb->clear();
	int index=0;
	int texIndex=0;
	for (i = texMap->begin(); i != texMap->end(); ++i){
		textureCmb->addItem(qPrintable(*i.value()->getName()));
		if ((i.value()->getName())==currentTex)
			texIndex=index;
		index++;
	}
	textureCmb->setCurrentIndex(texIndex);

	ArgoTexture *current = ArgoTextureManager::Instance()->getTexture(*currentTex);

	if (current->getType() == "Diffuse") typeCmb->setCurrentIndex(0);
	if (current->getType() == "Normal") typeCmb->setCurrentIndex(1);
}

void TextureEditor::currentTexChanged(QString tex)
{
	currentTex=ArgoTextureManager::Instance()->getTexture(tex)->getName();
	texWidget->setTexture(currentTex);
	texWidget->repaint();
	nameEdt->setText(qPrintable(*currentTex));
}

void TextureEditor::loadTexture()
{
	QString filename = QFileDialog::getOpenFileName(this,tr("Load Targa Texture"),"Data/Textures/TGA",tr("Targa (*.tga)"));

	if (!filename.isEmpty()){
		ArgoTextureManager::Instance()->LoadTexture(filename);
	}

	updateEditor();
	MaterialEditor::Instance()->updateEditor();
}

void TextureEditor::nameChanged(QString name)
{
	ArgoTextureManager::Instance()->RenameTexture(*currentTex,name);
	updateEditor();
}

void TextureEditor::typeChanged(QString type)
{
	ArgoTextureManager::Instance()->getTexture(*currentTex)->setType(type);	
	MaterialEditor::Instance()->updateEditor();
}