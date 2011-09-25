#ifndef DOCKEDOBJECTWIDGET_H
#define DOCKEDOBJECTWIDGET_H

#include <QtGui>
#include "ArgoObject.h"

class ArgoObject;

class DockedObjectWidget : public QWidget
{
    Q_OBJECT

private:
	QTableWidget *tableWidget;
	QTableWidgetItem *numTrianglesHdr, *physicsTrianglesHdr, *physicsTypeHdr;

	QLabel *numTrianglesLbl, *physicsTrianglesLbl;
	QComboBox *physicsTypeCmb;

	QString *currentObject;

public:
	DockedObjectWidget();
	~DockedObjectWidget(){}

	void createFromObject(ArgoObject *object);
	void updateWidget();

public slots:
};

#endif