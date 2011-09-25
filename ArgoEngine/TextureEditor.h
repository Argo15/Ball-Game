#ifndef TEXTUREEDITOR_H
#define TEXTUREEDITOR_H

#include <QDialog>
#include <QtGUI>
#include <QGLWidget>
#include "ArgoTextureManager.h"
#include "MaterialEditor.h"
#include "TextureWidget.h"

class TextureEditor : public QDialog
{
	Q_OBJECT

private:
	TextureEditor(QGLWidget *parent = 0);
	static TextureEditor* pInstance;

	QLineEdit *nameEdt;
	TextureWidget *texWidget;
	QLabel *typeLabel;
	QComboBox *textureCmb, *typeCmb;
	QPushButton *loadTextureBtn;
	QString *currentTex;

public:
	static TextureEditor* Instance();
    static void Initialize(QGLWidget *parent = 0);

public slots:
	void updateEditor();

private slots:
	void currentTexChanged(QString tex);
	void typeChanged(QString type);
	void loadTexture();
	void nameChanged(QString name);
};

#endif