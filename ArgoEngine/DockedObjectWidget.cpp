#include "DockedObjectWidget.h"
#include "ArgoSceneManager.h"

DockedObjectWidget::DockedObjectWidget() 
	: QWidget(0)
{
	currentObject = 0;

	numTrianglesLbl = new QLabel;
	physicsTrianglesLbl = new QLabel;
	physicsTypeCmb = new QComboBox;
	physicsTypeCmb->addItem("Static");
	physicsTypeCmb->addItem("Kinematic");
	physicsTypeCmb->addItem("Dynamic");

	tableWidget = new QTableWidget(3, 3, this);
	tableWidget->horizontalHeader()->hide();
	numTrianglesHdr = new QTableWidgetItem("Triangles");
	physicsTrianglesHdr = new QTableWidgetItem("Phys Triangles");
	physicsTypeHdr = new QTableWidgetItem("Physics Type");
	tableWidget->setVerticalHeaderItem(0,numTrianglesHdr);
	tableWidget->setVerticalHeaderItem(1,physicsTrianglesHdr);
	tableWidget->setVerticalHeaderItem(2,physicsTypeHdr);
	tableWidget->setSpan(0,0,1,3);
	tableWidget->setSpan(1,0,1,3);
	tableWidget->setSpan(2,0,1,3);
	tableWidget->setColumnWidth(0,46);
	tableWidget->setColumnWidth(1,46);
	tableWidget->setColumnWidth(2,46);
	tableWidget->resizeRowsToContents();
	tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	tableWidget->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
	tableWidget->setFixedHeight(tableWidget->verticalHeader()->sizeHint().height()*3);

	tableWidget->setCellWidget(0,0,numTrianglesLbl);
	tableWidget->setCellWidget(1,0,physicsTrianglesLbl);
	tableWidget->setCellWidget(2,0,physicsTypeCmb);

	QVBoxLayout *mainLayout = new QVBoxLayout;

	mainLayout->addWidget(tableWidget);

	setLayout(mainLayout);

	layout()->setContentsMargins(0,0,0,0);
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());
}

void DockedObjectWidget::createFromObject(ArgoObject *object)
{
	//numTrianglesLbl->setText
}

void DockedObjectWidget::updateWidget() {
	if (currentObject == 0)
		return;
	createFromObject(ArgoSceneManager::Instance()->getObject(*currentObject));
}