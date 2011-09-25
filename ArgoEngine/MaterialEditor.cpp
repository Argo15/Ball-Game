#include "MaterialEditor.h"
#include "DockedActorWidget.h"

MaterialEditor *MaterialEditor::pInstance = 0;

void MaterialEditor::Initialize(QGLWidget *parent)
{
	if (pInstance != 0) {
		delete pInstance;
	}
	pInstance=new MaterialEditor(parent);
}

MaterialEditor *MaterialEditor::Instance()
{
	return pInstance;
}

MaterialEditor::MaterialEditor(QGLWidget *parent)
	: QDialog(parent)
{
	QMap<QString,ArgoMaterial *> *matMap = ArgoMaterialManager::Instance()->getMaterials();
	matWidget = new MaterialWidget(this,parent);
	matWidget->setFixedWidth(200);
	matWidget->setFixedHeight(200);
	currentMat=matMap->begin().value()->getName();
	matWidget->setMaterial(currentMat);

	texWidget = new TextureWidget(this,parent);
	texWidget->setFixedWidth(150);
	texWidget->setFixedHeight(150);
	texWidget->setTexture(ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getTexture());

	normalWidget = new TextureWidget(this,parent);
	normalWidget->setFixedWidth(150);
	normalWidget->setFixedHeight(150);
	normalWidget->setTexture(ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getTexture());

	nameEdt = new QLineEdit(qPrintable(*currentMat));
	uTexOffEdt = new QLineEdit("0");
	uTexOffEdt->setFixedWidth(40);
	vTexOffEdt = new QLineEdit("0");
	vTexOffEdt->setFixedWidth(40);
	uTexScaleEdt = new QLineEdit("1");
	uTexScaleEdt->setFixedWidth(40);
	vTexScaleEdt = new QLineEdit("1");
	vTexScaleEdt->setFixedWidth(40);

	nameLbl = new QLabel("Name: ");
	colorLbl = new QLabel("Color: ");
	colorViewLbl = new QLabel("      ");
	colorViewLbl->setFixedWidth(100);
	colorViewLbl->setAutoFillBackground(true);
	specLbl = new QLabel("Specular: ");
	shineLbl = new QLabel("Shine: ");
	glowLbl = new QLabel("Glow:  ");
	glowViewLbl = new QLabel("      ");
	glowViewLbl->setFixedWidth(100);
	glowViewLbl->setAutoFillBackground(true);
	textureLbl = new QLabel("Texture:");
	uvOffLbl = new QLabel("UV offset:");
	uvScaleLbl = new QLabel("UV scale: ");
	texRotateLbl = new QLabel("Rotate: ");
	normalLbl = new QLabel("Normal: ");

	specSld = new QSlider(Qt::Horizontal);
	specSld->setRange(0,255);
	shineSld = new QSlider(Qt::Horizontal);
	shineSld->setRange(5,128);
	texRotateSld = new QSlider(Qt::Horizontal);
	texRotateSld->setRange(0,360);

	matCmb = new QComboBox;
	textureCmb = new QComboBox;
	normalCmb = new QComboBox;

	newMaterialBtn = new QPushButton("Add New Material");
	colorBtn = new QPushButton("...");
	colorBtn->setFixedWidth(50);
	glowBtn = new QPushButton("...");
	glowBtn->setFixedWidth(50);

	normalChk = new QCheckBox("Enabled");
	normalChk->setCheckState(Qt::Checked);

	QHBoxLayout *mainLayout = new QHBoxLayout;
		QVBoxLayout *leftLayout = new QVBoxLayout;
		QVBoxLayout *rightLayout = new QVBoxLayout;
			QHBoxLayout *nameLayout = new QHBoxLayout;
			QHBoxLayout *colorLayout = new QHBoxLayout;
			QHBoxLayout *specLayout = new QHBoxLayout;
			QHBoxLayout *shineLayout = new QHBoxLayout;
			QHBoxLayout *glowLayout = new QHBoxLayout;
		QHBoxLayout *texturesLayout = new QHBoxLayout;
			QVBoxLayout *textureLayout = new QVBoxLayout;
				QHBoxLayout *texUVOffLayout = new QHBoxLayout;
				QHBoxLayout *texUVScaleLayout = new QHBoxLayout;
				QHBoxLayout *texRotateLayout = new QHBoxLayout;
			QVBoxLayout *normalLayout = new QVBoxLayout;

	nameLayout->addWidget(nameLbl);
	nameLayout->addWidget(nameEdt);

	colorLayout->addWidget(colorLbl);
	colorLayout->addWidget(colorViewLbl);
	colorLayout->addWidget(colorBtn);

	specLayout->addWidget(specLbl);
	specLayout->addWidget(specSld);

	shineLayout->addWidget(shineLbl);
	shineLayout->addWidget(shineSld);

	glowLayout->addWidget(glowLbl);
	glowLayout->addWidget(glowViewLbl);
	glowLayout->addWidget(glowBtn);

	rightLayout->addLayout(nameLayout);
	rightLayout->addLayout(colorLayout);
	rightLayout->addLayout(glowLayout);
	rightLayout->addLayout(specLayout);
	rightLayout->addLayout(shineLayout);
	rightLayout->addStretch();

	leftLayout->addWidget(matWidget);
	leftLayout->addStretch();
	leftLayout->addWidget(matCmb);
	leftLayout->addWidget(newMaterialBtn);

	textureLayout->addWidget(textureLbl);
	textureLayout->addWidget(texWidget);
	textureLayout->addWidget(textureCmb);

	texUVOffLayout->addWidget(uvOffLbl);
	texUVOffLayout->addWidget(uTexOffEdt);
	texUVOffLayout->addWidget(vTexOffEdt);

	texUVScaleLayout->addWidget(uvScaleLbl);
	texUVScaleLayout->addWidget(uTexScaleEdt);
	texUVScaleLayout->addWidget(vTexScaleEdt);

	texRotateLayout->addWidget(texRotateLbl);
	texRotateLayout->addWidget(texRotateSld);

	textureLayout->addLayout(texUVOffLayout);
	textureLayout->addLayout(texUVScaleLayout);
	textureLayout->addLayout(texRotateLayout);
	textureLayout->addStretch();

	normalLayout->addWidget(normalLbl);
	normalLayout->addWidget(normalWidget);
	normalLayout->addWidget(normalCmb);
	normalLayout->addWidget(normalChk);
	normalLayout->addStretch();
	
	texturesLayout->addLayout(textureLayout);
	texturesLayout->addLayout(normalLayout);

	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	mainLayout->addLayout(texturesLayout);

	setLayout(mainLayout);

	connect(matCmb, SIGNAL(activated(QString)),this, SLOT(currentMatChanged(QString)));
	connect(nameEdt, SIGNAL(textChanged(QString)),this,SLOT(nameChanged(QString)));
	connect(specSld, SIGNAL(valueChanged(int)),this, SLOT(specChanged(int)));
	connect(shineSld, SIGNAL(valueChanged(int)),this, SLOT(shineChanged(int)));
	connect(colorBtn, SIGNAL(clicked()),this, SLOT(colorChanged()));
	connect(glowBtn, SIGNAL(clicked()),this, SLOT(glowChanged()));
	connect(textureCmb, SIGNAL(activated(QString)),this, SLOT(currentTexChanged(QString)));
	connect(normalCmb, SIGNAL(activated(QString)),this, SLOT(currentNormChanged(QString)));
	connect(newMaterialBtn, SIGNAL(clicked()),this, SLOT(addNewMaterial()));
	connect(uTexOffEdt, SIGNAL(textChanged(QString)),this,SLOT(uTexOffChanged(QString)));
	connect(vTexOffEdt, SIGNAL(textChanged(QString)),this,SLOT(vTexOffChanged(QString)));
	connect(uTexScaleEdt, SIGNAL(textChanged(QString)),this,SLOT(uTexScaleChanged(QString)));
	connect(vTexScaleEdt, SIGNAL(textChanged(QString)),this,SLOT(vTexScaleChanged(QString)));
	connect(texRotateSld, SIGNAL(valueChanged(int)),this, SLOT(texRotateChanged(int)));
	connect(normalChk, SIGNAL(clicked()),this, SLOT(normalChanged()));

	setWindowTitle(tr("Material Manager"));
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());

	updateEditor();
}

void MaterialEditor::updateEditor()
{
	QMap<QString,ArgoMaterial *> *matMap = ArgoMaterialManager::Instance()->getMaterials();
	QMap<QString, ArgoMaterial *>::iterator imat;
	matCmb->clear();
	int index=0;
	int matIndex=0;
	for (imat = matMap->begin(); imat != matMap->end(); ++imat){
		matCmb->addItem(qPrintable(*imat.value()->getName()));
		if ((imat.value()->getName())==currentMat)
			matIndex=index;
		index++;
	}
	matCmb->setCurrentIndex(matIndex);

	QMap<QString,ArgoTexture *> *texMap = ArgoTextureManager::Instance()->getTextures();
	QMap<QString, ArgoTexture *>::iterator itex;
	textureCmb->clear();
	index=0;
	int texIndex=0;
	QString *currentTex = ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getTexture();
	for (itex = texMap->begin(); itex != texMap->end(); ++itex){
		if (itex.value()->getType() == "Diffuse"){
			textureCmb->addItem(qPrintable(*itex.value()->getName()));
			if ((itex.value()->getName())==currentTex)
				texIndex=index;
			index++;
		}
	}
	textureCmb->setCurrentIndex(texIndex);

	normalCmb->clear();
	index=0;
	texIndex=0;
	QString *currentNorm = ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getNormal();
	for (itex = texMap->begin(); itex != texMap->end(); ++itex){
		if (itex.value()->getType() == "Normal"){
			normalCmb->addItem(qPrintable(*itex.value()->getName()));
			if ((itex.value()->getName())==currentNorm)
				texIndex=index;
			index++;
		}
	}
	normalCmb->setCurrentIndex(texIndex);

	float *color = ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getColor();
	float *emission = ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getEmission();
	float specular = ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getSpecular();
	int shine = ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getShine();
	bool normalsEnabled = ArgoMaterialManager::Instance()->getMaterial(*currentMat)->normalsEnabled();

	QPalette palette;
	QBrush brush;

	brush = QBrush(QColor(color[0]*255, color[1]*255, color[2]*255, 255));
	brush.setStyle(Qt::SolidPattern);
	palette.setBrush(QPalette::Active, QPalette::Window, brush);
	palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
	colorViewLbl->setPalette(palette);

	brush = QBrush(QColor(emission[0]*255, emission[1]*255, emission[2]*255, 255));
	brush.setStyle(Qt::SolidPattern);
	palette.setBrush(QPalette::Active, QPalette::Window, brush);
	palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
	glowViewLbl->setPalette(palette);

	specSld->setValue((int)(specular*255));
	shineSld->setValue(shine);

	if (normalsEnabled)
		normalChk->setCheckState(Qt::Checked);
	else
		normalChk->setCheckState(Qt::Unchecked);

	texWidget->setTexture(currentTex);
	normalWidget->setTexture(currentNorm);

	matWidget->repaint();
	texWidget->repaint();
	normalWidget->repaint();

	if (ModelEditor::Instance() != 0)
		ModelEditor::Instance()->updateEditor();
}

void MaterialEditor::currentMatChanged(QString mat)
{
	ArgoMaterial *theMat = ArgoMaterialManager::Instance()->getMaterial(mat);
	currentMat=ArgoMaterialManager::Instance()->getMaterial(mat)->getName();
	matWidget->setMaterial(currentMat);
	matWidget->repaint();
	
	float *uvTexOff = ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getTexOffset();
	float *uvTexScale = ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getTexScale();
	float texRotate = ArgoMaterialManager::Instance()->getMaterial(*currentMat)->getTexRotate();
	uTexOffEdt->setText(QString::number(uvTexOff[0]));
	vTexOffEdt->setText(QString::number(uvTexOff[1]));
	uTexScaleEdt->setText(QString::number(uvTexScale[0]));
	vTexScaleEdt->setText(QString::number(uvTexScale[1]));
	texRotateSld->setValue(texRotate);
	nameEdt->setText(*currentMat);
}

void MaterialEditor::nameChanged(QString name)
{
	ArgoMaterialManager::Instance()->RenameMaterial(*currentMat,name);
	updateEditor();
	DockedActorEditor::Instance()->getMainWidget()->getActorWidget()->updateWidget();
}

void MaterialEditor::specChanged(int value)
{
	ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setSpecular((float)value/255.0);
	updateEditor();
}

void MaterialEditor::shineChanged(int value)
{
	ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setShine(value);
	updateEditor();
}

void MaterialEditor::colorChanged()
{
	int r,g,b,a;
	QColor color = QColorDialog::getColor(Qt::white,this);
	if (color.isValid())
	{
		color.getRgb (&r, &g, &b);
		ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setColor((float)r/255.0,(float)g/255.0,(float)b/255.0);
	}
	updateEditor();
}

void MaterialEditor::glowChanged()
{
	int r,g,b,a;
	QColor color = QColorDialog::getColor(Qt::white,this);
	if (color.isValid())
	{
		color.getRgb (&r, &g, &b);
		ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setEmission((float)r/255.0,(float)g/255.0,(float)b/255.0);
	}
	updateEditor();
}

void MaterialEditor::currentTexChanged(QString tex)
{
	ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setTexture(ArgoTextureManager::Instance()->getTexture(tex)->getName());
	updateEditor();
}

void MaterialEditor::currentNormChanged(QString tex)
{
	ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setNormal(ArgoTextureManager::Instance()->getTexture(tex)->getName());
	updateEditor();
}

void MaterialEditor::addNewMaterial()
{
	QString *name = new QString("New Material");
	ArgoMaterial *newMaterial = new ArgoMaterial(new QString);
	*newMaterial = *ArgoMaterialManager::Instance()->getDefault();
	newMaterial->setName(name);
	ArgoMaterialManager::Instance()->AddMaterial(newMaterial);
	updateEditor();
	DockedActorEditor::Instance()->getMainWidget()->getActorWidget()->updateWidget();
}

void MaterialEditor::uTexOffChanged(QString value)
{
	ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setUTexOffset(value.toFloat());
	updateEditor();
}

void MaterialEditor::vTexOffChanged(QString value)
{
	ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setVTexOffset(value.toFloat());
	updateEditor();
}

void MaterialEditor::uTexScaleChanged(QString value)
{
	ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setUTexScale(value.toFloat());
	updateEditor();
}

void MaterialEditor::vTexScaleChanged(QString value)
{
	ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setVTexScale(value.toFloat());
	updateEditor();
}

void MaterialEditor::texRotateChanged(int value)
{
	ArgoMaterialManager::Instance()->getMaterial(*currentMat)->setTexRotate(value);
	updateEditor();
}

void MaterialEditor::normalChanged()
{
	ArgoMaterialManager::Instance()->getMaterial(*currentMat)->enableNormal(!ArgoMaterialManager::Instance()->getMaterial(*currentMat)->normalsEnabled());
	updateEditor();
}