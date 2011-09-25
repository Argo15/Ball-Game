#include "ArgoMaterialManager.h"

ArgoMaterialManager *ArgoMaterialManager::pInstance = 0;

ArgoMaterialManager::ArgoMaterialManager()
{

}

void ArgoMaterialManager::Initialize()
{
	pInstance=new ArgoMaterialManager;
}

ArgoMaterialManager *ArgoMaterialManager::Instance()
{
	return pInstance;
}

void ArgoMaterialManager::AddMaterial(ArgoMaterial *material)
{
	QString name = *material->getName();
	if (!materials.contains(name)){
		materials[name]=material;
		return;
	}
	int i=0;
	QString newName;
	do
	{
		i++;
		newName = name + "(" + QString::number(i)+")";
	}while(materials.contains(newName));
	material->setName(newName);
	materials[newName]=material;
}

void ArgoMaterialManager::RenameMaterial(QString oldName, QString newName)
{
	ArgoMaterial *material = materials[oldName];
	materials.remove(oldName);
	material->setName(newName);
	QString name = newName;
	if (!materials.contains(newName)){
		materials[newName]=material;
		return;
	}
	int i=0;
	QString newName2;
	do
	{
		i++;
		newName2 = name + "(" + QString::number(i)+")";
	}while(materials.contains(newName2));
	material->setName(newName2);
	materials[newName2]=material;
}

void ArgoMaterialManager::DeleteMaterial(QString name)
{
	materials.remove(name);
}

void ArgoMaterialManager::DeleteAllMaterials()
{
	materials.clear();
}