#include "ArgoModelManager.h"

ArgoModelManager* ArgoModelManager::pInstance = 0;

ArgoModelManager::ArgoModelManager()
{
	
}

ArgoModelManager* ArgoModelManager::Instance()
{
	return pInstance;
}

void ArgoModelManager::Initialize()
{
	pInstance = new ArgoModelManager;

}

void ArgoModelManager::LoadModel(QString filename, QString name)
{
	ArgoModel *model;
	QStringList fields = filename.split('.');
	QString type = fields.takeLast();
	if (type=="obj")
		model = new ArgoObjModel;
	else if (type=="aobj")
		model = new ArgoAObjModel;
	else
		return;
	model->load(qPrintable(filename));
	if (name.length() == 0) 
		name = *model->getName();
	if (!models.contains(name)){
		model->setName(name);
		models[name]=model;
		return;
	}
	int i=0;
	QString newName;
	do
	{
		i++;
		newName = name + "(" + QString::number(i)+")";
	}while(models.contains(newName));
	model->setName(newName);
	models[newName]=model;
}

void ArgoModelManager::DrawModel(QString name)
{
	models[name]->draw();
}

void ArgoModelManager::DrawModelSelection(QString name)
{
	models[name]->drawSelection();
}

void ArgoModelManager::RenameModel(QString oldName, QString newName)
{
	ArgoModel *model = models[oldName];
	models.remove(oldName);
	model->setName(newName);
	QString name = newName;
	if (!models.contains(newName)){
		models[newName]=model;
		return;
	}
	int i=0;
	QString newName2;
	do
	{
		i++;
		newName2 = name + "(" + QString::number(i)+")";
	}while(models.contains(newName2));
	model->setName(newName2);
	models[newName2]=model;
}

void ArgoModelManager::DeleteModel(QString name)
{
	if (models.contains(name)){
		models[name]->remove();
		models.remove(name);
	}
}

void ArgoModelManager::DeleteAllModels()
{
	models.clear();
}