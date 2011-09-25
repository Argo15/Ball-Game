#include "ArgoTextureManager.h"

ArgoTextureManager* ArgoTextureManager::pInstance = 0;

ArgoTextureManager::ArgoTextureManager()
{
	
}

ArgoTextureManager* ArgoTextureManager::Instance()
{
	return pInstance;
}

void ArgoTextureManager::Initialize()
{
	pInstance = new ArgoTextureManager;

}

void ArgoTextureManager::LoadTexture(QString filename, QString name)
{
	ArgoTexture *texture = new ArgoTgaTexture;
	texture->load(qPrintable(filename));
	if (name.length() == 0) 
		name = *texture->getName();
	if (!textures.contains(name)){
		textures[name]=texture;
		return;
	}
	int i=0;
	QString newName;
	do
	{
		i++;
		newName = name + "(" + QString::number(i)+")";
	}while(textures.contains(newName));
	texture->setName(newName);
	textures[newName]=texture;
}

void ArgoTextureManager::BindTexture(QString name)
{
	textures[name]->use();
}

void ArgoTextureManager::RenameTexture(QString oldName, QString newName)
{
	ArgoTexture *texture = textures[oldName];
	textures.remove(oldName);
	texture->setName(newName);
	QString name = newName;
	if (!textures.contains(newName)){
		textures[newName]=texture;
		return;
	}
	int i=0;
	QString newName2;
	do
	{
		i++;
		newName2 = name + "(" + QString::number(i)+")";
	}while(textures.contains(newName2));
	texture->setName(newName2);
	textures[newName2]=texture;
}

void ArgoTextureManager::DeleteTexture(QString name)
{
	textures[name]->remove();
	delete textures[name];
	textures.remove(name);
}

void ArgoTextureManager::DeleteAllTextures()
{
	textures.clear();
}