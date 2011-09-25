#include "ArgoSceneManager.h"
#include "ArgoGraphicsSettings.h"

ArgoSceneManager* ArgoSceneManager::pInstance = 0;

ArgoSceneManager::ArgoSceneManager()
{
	selectedActor = 0;
	directLight = 0;
	entrance = 0;
	exit = 0;
}

ArgoSceneManager* ArgoSceneManager::Instance()
{
	return pInstance;
}

void ArgoSceneManager::Initialize()
{
	pInstance = new ArgoSceneManager;
}

void ArgoSceneManager::AddObject(ArgoObject *object)
{
	AddActor(object);
	objects[*object->getName()]=object;
}

void ArgoSceneManager::AddPointLight(ArgoPointLight *light)
{
	AddActor(light);
	pointLights[*light->getName()]=light;
}

void ArgoSceneManager::DrawScene(ArgoFrustum *frustum, GLSLProgram *program)
{
	QMap<QString, ArgoActor *>::iterator it;
	for (it = actors.begin(); it != actors.end(); ++it){
		ArgoActor *actor = it.value();
		if (frustum->isInFrustum(actor->getTranslateV(),actor->getScaledRadius())){
			glPushMatrix();
				actor->transform();
				ArgoMaterialManager::Instance()->UseMaterial(*(actor->getMaterial()),program);
				if (ArgoGraphicsSettings::Instance()->shadersEnabled()) {
					ArgoModelManager::Instance()->DrawModel(*(actor->getModel()));
				} else {
					ArgoModelManager::Instance()->DrawModelSelection(*(actor->getModel()));
				}
			glPopMatrix();
		}
	}

	if (selectedActor != 0){
		glColor3f(1.0,1.0,1.0);
		glActiveTexture(GL_TEXTURE0); 
		ArgoTextureManager::Instance()->BindWhite();
		Transformer::draw(selectedActor,false);
	}
}

void ArgoSceneManager::RenameObject(QString oldName, QString newName)
{
	if (oldName == newName)
		return;
	QString *name = objects[oldName]->getName();
	RenameActor(oldName,newName);
	objects[*name]=objects[oldName];
	objects.remove(oldName);
}

void ArgoSceneManager::RenamePointLight(QString oldName, QString newName)
{
	if (oldName == newName)
		return;
	QString *name = pointLights[oldName]->getName();
	RenameActor(oldName,newName);
	pointLights[*name]=pointLights[oldName];
	pointLights.remove(oldName);
}

void ArgoSceneManager::RenameActor(QString oldName, QString newName)
{
	if (oldName == newName)
		return;
	ArgoActor *actor = actors[oldName];
	actors.remove(oldName);
	actor->setName(newName);
	QString name = newName;
	if (!actors.contains(newName)){
		actors[newName]=actor;
		return;
	}
	int i=0;
	QString newName2;
	do
	{
		i++;
		newName2 = name + "(" + QString::number(i)+")";
	}while(actors.contains(newName2));
	actor->setName(newName2);
	actors[newName2]=actor;
}

void ArgoSceneManager::RenameActorSmart(QString oldName, QString newName)
{
	if (objects.contains(oldName)){
		RenameObject(oldName,newName);
	} else if (directLight != 0 && directLight->getName() == oldName){
		RenameActor(oldName,newName);
	} else if (pointLights.contains(oldName)){
		RenamePointLight(oldName,newName);
	}
}

void ArgoSceneManager::AddActor(ArgoActor *actor)
{
   QString name = *actor->getName();
	if (!actors.contains(name)){
		actors[name]=actor;
		setSelected(actor->getName());
		return;
	}
	int i=0;
	QString newName;
	do
	{
		i++;
		newName = name + "(" + QString::number(i)+")";
	}while(actors.contains(newName));
	actor->setName(newName);
	actors[newName]=actor;
	setSelected(actor->getName());
}

void ArgoSceneManager::DeleteActor(QString name)
{
	if (objects.contains(name)){
		objects.remove(name);
		actors.remove(name);
	}
}

void ArgoSceneManager::deleteSelected()
{
	if (selectedActor == 0)
		return;
	DeleteActor(*selectedActor);

	selectedActor = 0;
}

void ArgoSceneManager::setSelected(QString *selected)
{
	selectedActor=selected;
	DockedActorEditor::Instance()->getMainWidget()->hideAll();
	if (selectedActor) {
		actors[*selectedActor]->updateDockedWidget();
		if (pointLights.contains(*selectedActor)){
			LightEditor::Instance()->getPointLightWidget()->currentLightChanged(*selectedActor);
		}
	}
}

void ArgoSceneManager::setDirectLight(ArgoDirectLight *dLight)
{
	if (directLight != 0) 
		DeleteActor(*(directLight->getName()));
	AddActor(dLight);
	directLight=dLight;
}

void ArgoSceneManager::setEntrance(ArgoPort *entrance)
{
	if (entrance != 0)
		DeleteActor(*(entrance->getName()));
	AddActor(entrance);
	this->entrance=entrance;
}

void ArgoSceneManager::setExit(ArgoPort *exit)
{
	if (exit != 0)
		DeleteActor(*(exit->getName()));
	AddActor(exit);
	this->exit=exit;
}

void ArgoSceneManager::DeleteScene()
{
	actors.clear();
	objects.clear();
	pointLights.clear();
	directLight = 0;
}