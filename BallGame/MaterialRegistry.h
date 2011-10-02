#ifndef MATERIALREGISTRY_H
#define MATERIALREGISTRY_H

#include <map>
#include <string>
#include "Material.h"
using namespace std;

class MaterialRegistry {
private:
	map<string,Material *> materials;

public:
	MaterialRegistry() {}
	~MaterialRegistry() { cleanup(); }
	void addMaterial(string name, Material *material) {materials[name]=material;}
	Material *getMaterial(string name) {return materials[name];}
	void cleanup() {
		map<string,Material *>::iterator i;
		for (i = materials.begin(); i != materials.end(); i++) {
			delete i->second;
		}
	}
};

#endif