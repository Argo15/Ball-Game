#ifndef DOCKEDACTORWIDGET_H
#define DOCKEDACTORWIDGET_H

#include <QtGui>
#include "ArgoActor.h"

class ArgoActor;

class DockedActorWidget : public QWidget
{
    Q_OBJECT

private:
	QTableWidget *tableWidget;
	QTableWidgetItem *nameHdr, *modelHdr, *materialHdr, *transHdr, *rotHdr, *scaleHdr;

	QString *currentActor;

	QComboBox *matCmb,*modelCmb;
	QPushButton *editMatBtn;
	QLineEdit *nameEdt, *posXEdt, *posYEdt, *posZEdt,
				*rotXEdt, *rotYEdt, *rotZEdt,
				*scaleXEdt, *scaleYEdt, *scaleZEdt;

public:
	DockedActorWidget();
	~DockedActorWidget(){}

	void createFromActor(ArgoActor *actor);
	void updateWidget();

public slots:
	void nameChanged(QString name);
	void currentMatChanged(QString material);
	void currentModelChanged(QString model);
	void editMaterial();
	void changePosition();
	void changeScale();
};

#endif