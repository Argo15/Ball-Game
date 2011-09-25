#include "PointLightWidget.h"

PointLightWidget::PointLightWidget(QGLWidget *parent,QGLWidget *shared)
	: QWidget(parent)
{
	currentLight = 0;

	attenWgt = new AttenuationWidget(this,shared);
	attenWgt->setAttenuation(0.0);
	attenWgt->setFixedWidth(150);
	attenWgt->setFixedHeight(150);

	nameLbl = new QLabel("Name: ");
	colorLbl = new QLabel("Color: ");
	colorViewLbl = new QLabel("       ");
	colorViewLbl->setAutoFillBackground(true);
	ambientLbl = new QLabel("Ambient: ");
	diffuseLbl = new QLabel("Diffuse: ");
	specularLbl = new QLabel("Specular: ");
	attenLbl = new QLabel("Attenuation: ");
	radiusLbl = new QLabel("Radius: ");

	QPalette palette;
	QBrush brush;
	brush = QBrush(Qt::white);
	brush.setStyle(Qt::SolidPattern);
	palette.setBrush(QPalette::Active, QPalette::Window, brush);
	palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
	colorViewLbl->setPalette(palette);

	enabledChk = new QCheckBox("Enabled");
	enabledChk->setCheckState(Qt::Checked);

	nameEdt = new QLineEdit();
	radiusEdt = new QLineEdit();

	ambientSld = new QSlider(Qt::Horizontal);
	ambientSld->setRange(0,255);
	diffuseSld = new QSlider(Qt::Horizontal);
	diffuseSld->setRange(0,255);
	specularSld = new QSlider(Qt::Horizontal);
	specularSld->setRange(0,255);
	attenSld = new QSlider(Qt::Horizontal);
	attenSld->setRange(1,50);

	colorBtn = new QPushButton("...");
	colorBtn->setFixedWidth(50);
	addLightBtn = new QPushButton("Add Light");

	lightCmb = new QComboBox();

	QHBoxLayout *mainLayout = new QHBoxLayout;
		QVBoxLayout *leftLayout = new QVBoxLayout;
		QVBoxLayout *rightLayout = new QVBoxLayout;
			QHBoxLayout *nameLayout = new QHBoxLayout;
			QHBoxLayout *colorLayout = new QHBoxLayout;
			QHBoxLayout *ambientLayout = new QHBoxLayout;
			QHBoxLayout *diffuseLayout = new QHBoxLayout;
			QHBoxLayout *specLayout = new QHBoxLayout;
			QHBoxLayout *attenLayout = new QHBoxLayout;
			QHBoxLayout *radiusLayout = new QHBoxLayout;

	nameLayout->addWidget(nameLbl);
	nameLayout->addWidget(nameEdt);

	colorLayout->addWidget(colorLbl);
	colorLayout->addWidget(colorViewLbl);
	colorLayout->addWidget(colorBtn);

	ambientLayout->addWidget(ambientLbl);
	ambientLayout->addWidget(ambientSld);

	diffuseLayout->addWidget(diffuseLbl);
	diffuseLayout->addWidget(diffuseSld);

	specLayout->addWidget(specularLbl);
	specLayout->addWidget(specularSld);

	attenLayout->addWidget(attenLbl);
	attenLayout->addWidget(attenSld);

	radiusLayout->addWidget(radiusLbl);
	radiusLayout->addWidget(radiusEdt);

	leftLayout->addWidget(attenWgt);
	leftLayout->addWidget(lightCmb);
	leftLayout->addWidget(addLightBtn);

	rightLayout->addLayout(nameLayout);
	rightLayout->addWidget(enabledChk);
	rightLayout->addLayout(colorLayout);
	rightLayout->addLayout(ambientLayout);
	rightLayout->addLayout(diffuseLayout);
	rightLayout->addLayout(specLayout);
	rightLayout->addLayout(attenLayout);
	rightLayout->addLayout(radiusLayout);

	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);

	setLayout(mainLayout);

	connect(ambientSld, SIGNAL(valueChanged(int)),this, SLOT(ambientChanged(int)));
	connect(diffuseSld, SIGNAL(valueChanged(int)),this, SLOT(diffuseChanged(int)));
	connect(specularSld, SIGNAL(valueChanged(int)),this, SLOT(specularChanged(int)));
	connect(attenSld, SIGNAL(valueChanged(int)),this, SLOT(attenuationChanged(int)));
	connect(nameEdt, SIGNAL(textChanged(QString)),this,SLOT(nameChanged(QString)));
	connect(radiusEdt, SIGNAL(textChanged(QString)),this,SLOT(radiusChanged(QString)));
	connect(colorBtn, SIGNAL(clicked()),this, SLOT(colorChanged()));
	connect(enabledChk, SIGNAL(clicked()),this, SLOT(enabledChanged()));
	connect(addLightBtn, SIGNAL(clicked()),this, SLOT(addNewLight()));
	connect(lightCmb, SIGNAL(activated(QString)),this, SLOT(currentLightChanged(QString)));

	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());

	updateWidget();
}

void PointLightWidget::updateWidget()
{
	QMap<QString,ArgoPointLight *> *lightMap = ArgoSceneManager::Instance()->getPointLights();
	QMap<QString, ArgoPointLight *>::iterator i;
	lightCmb->clear();
	int index=0;
	int lightIndex=0;
	for (i = lightMap->begin(); i != lightMap->end(); ++i){
		lightCmb->addItem(qPrintable(*i.value()->getName()));
		if ((i.value()->getName())==currentLight)
			lightIndex=index;
		index++;
	}

	if (currentLight == 0)
		return;

	lightCmb->setCurrentIndex(lightIndex);

	ArgoPointLight *current = ArgoSceneManager::Instance()->getPointLight(*currentLight);

	float *color = current->getColor();

	QPalette palette;
	QBrush brush;
	brush = QBrush(QColor(color[0]*255,color[1]*255,color[2]*255));
	brush.setStyle(Qt::SolidPattern);
	palette.setBrush(QPalette::Active, QPalette::Window, brush);
	palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
	colorViewLbl->setPalette(palette);

	if (current->isenabled())
		enabledChk->setCheckState(Qt::Checked);
	else
		enabledChk->setCheckState(Qt::Unchecked);
	ambientSld->setValue(current->getAmbient()*255);
	diffuseSld->setValue(current->getDiffuse()*255);
	specularSld->setValue(current->getSpecular()*255);
	attenSld->setValue(current->getAttenuation()*10);
	radiusEdt->setText(QString::number(current->getRadius()));
	attenWgt->setAttenuation(current->getAttenuation());

}

void PointLightWidget::ambientChanged(int value)
{
	if (currentLight == 0) return;
	ArgoSceneManager::Instance()->getPointLight(*currentLight)->setAmbient((float)value/255.0);
	updateWidget();
}

void PointLightWidget::diffuseChanged(int value)
{
	if (currentLight == 0) return;
	ArgoSceneManager::Instance()->getPointLight(*currentLight)->setDiffuse((float)value/255.0);
	updateWidget();
}

void PointLightWidget::specularChanged(int value)
{
	if (currentLight == 0) return;
	ArgoSceneManager::Instance()->getPointLight(*currentLight)->setSpecular((float)value/255.0);
	updateWidget();
}

void PointLightWidget::attenuationChanged(int value)
{
	if (currentLight == 0) return;
	ArgoSceneManager::Instance()->getPointLight(*currentLight)->setAttenuation((float)value/10.0);
	updateWidget();
	attenWgt->repaint();
}

void PointLightWidget::nameChanged(QString name)
{
	if (currentLight == 0 || name == *currentLight) return;
	ArgoSceneManager::Instance()->RenamePointLight(*currentLight,name);
	updateWidget();
}

void PointLightWidget::radiusChanged(QString name)
{
	if (currentLight == 0) return;
	ArgoSceneManager::Instance()->getPointLight(*currentLight)->setRadius(name.toFloat());
	updateWidget();
}

void PointLightWidget::colorChanged()
{
	if (currentLight == 0) return;
	int r,g,b,a;
	QColor color = QColorDialog::getColor(Qt::white,this);
	if (color.isValid())
	{
		color.getRgb (&r, &g, &b);
		ArgoSceneManager::Instance()->getPointLight(*currentLight)->setColor((float)r/255.0,(float)g/255.0,(float)b/255.0);
	}
	updateWidget();
}

void PointLightWidget::enabledChanged()
{
	if (currentLight == 0) return;
	ArgoSceneManager::Instance()->getPointLight(*currentLight)->setEnabled(!ArgoSceneManager::Instance()->getPointLight(*currentLight)->isenabled());
	updateWidget();
}

void PointLightWidget::addNewLight()
{
	QString *name = new QString("Point Light");
	ArgoPointLight *newLight = new ArgoPointLight(name);
	ArgoSceneManager::Instance()->AddPointLight(newLight);
	currentLight = newLight->getName();
	nameEdt->setText(*currentLight);
	updateWidget();
	attenWgt->repaint();
}

void PointLightWidget::currentLightChanged(QString name)
{
	currentLight = ArgoSceneManager::Instance()->getPointLight(name)->getName();
	nameEdt->setText(*currentLight);
	if (ArgoSceneManager::Instance()->getSelected() != currentLight)
		ArgoSceneManager::Instance()->setSelected(currentLight);
	updateWidget();
	attenWgt->repaint();
}