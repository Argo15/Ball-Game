#include "DirectLightWidget.h"

DirectLightWidget::DirectLightWidget(QGLWidget *parent)
	: QWidget(parent)
{
	nameLbl = new QLabel("Name: ");
	colorLbl = new QLabel("Color: ");
	colorViewLbl = new QLabel("       ");
	colorViewLbl->setAutoFillBackground(true);
	ambientLbl = new QLabel("Ambient: ");
	diffuseLbl = new QLabel("Diffuse: ");
	specularLbl = new QLabel("Specular: ");
	QPalette palette;
	QBrush brush;
	brush = QBrush(Qt::white);
	brush.setStyle(Qt::SolidPattern);
	palette.setBrush(QPalette::Active, QPalette::Window, brush);
	palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
	colorViewLbl->setPalette(palette);

	enabledChk = new QCheckBox("Enabled");
	enabledChk->setCheckState(Qt::Checked);

	nameEdt = new QLineEdit(qPrintable(*ArgoSceneManager::Instance()->getDirectLight()->getName()));

	ambientSld = new QSlider(Qt::Horizontal);
	ambientSld->setRange(0,255);
	ambientSld->setValue(127);
	diffuseSld = new QSlider(Qt::Horizontal);
	diffuseSld->setRange(0,255);
	diffuseSld->setValue(127);
	specularSld = new QSlider(Qt::Horizontal);
	specularSld->setRange(0,255);
	specularSld->setValue(255);

	colorBtn = new QPushButton("...");
	colorBtn->setFixedWidth(50);

	QVBoxLayout *mainLayout = new QVBoxLayout;
		QHBoxLayout *nameLayout = new QHBoxLayout;
		QHBoxLayout *colorLayout = new QHBoxLayout;
		QHBoxLayout *ambientLayout = new QHBoxLayout;
		QHBoxLayout *diffuseLayout = new QHBoxLayout;
		QHBoxLayout *specLayout = new QHBoxLayout;

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

	mainLayout->addLayout(nameLayout);
	mainLayout->addWidget(enabledChk);
	mainLayout->addLayout(colorLayout);
	mainLayout->addLayout(ambientLayout);
	mainLayout->addLayout(diffuseLayout);
	mainLayout->addLayout(specLayout);

	setLayout(mainLayout);

	connect(ambientSld, SIGNAL(valueChanged(int)),this, SLOT(ambientChanged(int)));
	connect(diffuseSld, SIGNAL(valueChanged(int)),this, SLOT(diffuseChanged(int)));
	connect(specularSld, SIGNAL(valueChanged(int)),this, SLOT(specularChanged(int)));
	connect(nameEdt, SIGNAL(textChanged(QString)),this,SLOT(nameChanged(QString)));
	connect(colorBtn, SIGNAL(clicked()),this, SLOT(colorChanged()));
	connect(enabledChk, SIGNAL(clicked()),this, SLOT(enabledChanged()));


	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());

	updateWidget();
}

void DirectLightWidget::updateWidget()
{
}

void DirectLightWidget::ambientChanged(int value)
{
	ArgoSceneManager::Instance()->getDirectLight()->setAmbient((float)(value/255.0));
}

void DirectLightWidget::diffuseChanged(int value)
{
	ArgoSceneManager::Instance()->getDirectLight()->setDiffuse((float)(value/255.0));
}

void DirectLightWidget::specularChanged(int value)
{
	ArgoSceneManager::Instance()->getDirectLight()->setSpecular((float)(value/255.0));
}

void DirectLightWidget::nameChanged(QString name)
{
	ArgoSceneManager::Instance()->RenameActor(*ArgoSceneManager::Instance()->getDirectLight()->getName(),name);
}

void DirectLightWidget::colorChanged()
{
	int r,g,b,a;
	QColor color = QColorDialog::getColor(Qt::white,this);
	if (color.isValid())
	{
		color.getRgb (&r, &g, &b);
		ArgoSceneManager::Instance()->getDirectLight()->setColor((float)r/255.0,(float)g/255.0,(float)b/255.0);
	}

	QPalette palette;
	QBrush brush;
	brush = QBrush(color);
	brush.setStyle(Qt::SolidPattern);
	palette.setBrush(QPalette::Active, QPalette::Window, brush);
	palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
	colorViewLbl->setPalette(palette);
}

void DirectLightWidget::enabledChanged()
{
	ArgoSceneManager::Instance()->getDirectLight()->setEnabled(!ArgoSceneManager::Instance()->getDirectLight()->isenabled());
}