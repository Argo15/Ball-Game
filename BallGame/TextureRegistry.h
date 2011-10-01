#ifndef TEXTUREREGISTRY_H
#define TEXTUREREGISTRY_H

#include <map>
#include <string>
#include "Texture.h"
using namespace std;

class TextureRegistry {
private:
	map<string,Texture *> textures;

public:
	TextureRegistry() {}
	~TextureRegistry() { cleanup(); }
	void addTexture(string name, Texture *texture) {textures[name]=texture;}
	Texture *getTexture(string name) {return textures[name];}
	void cleanup() {
		map<string,Texture *>::iterator i;
		for (i = textures.begin(); i != textures.end(); i++) {
			i->second->remove();
			delete i->second;
		}
	}

};

#endif