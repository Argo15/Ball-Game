#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "TextureRegistry.h"
#include "GLSLProgram.h"
using namespace std;

class Material {
private:
	float color[3];
	float emission[3];
	float specular;
	int shininess;

	float texOffset[2];
	float texScale[2];
	float texRotate;

	string texture;
	string normal;

	bool normalEnabled;
public:
	Material();
	~Material() {}

	void setColor(float r, float g, float b) {color[0]=r; color[1]=g; color[2]=b;}
	void setEmission(float r, float g, float b) {emission[0]=r; emission[1]=g; emission[2]=b;}
	void setSpecular(float i) {specular=i;}
	void setShine(int shine) {shininess=shine;}
	void setTexOffset(float u, float v) {texOffset[0]=u; texOffset[1]=v;}
	void setTexScale(float u, float v) {texScale[0]=u; texScale[1]=v;}
	void setTexRotate(float rot) {texRotate=rot;}
	void setTexture(string name) {texture=name;}
	void setNormal(string name) {normal=name;}
	void setNormalEnabled(bool enabled) {normalEnabled=enabled;}
	bool normalsEnabled() {return normalEnabled;}

	void use(TextureRegistry *textures, GLSLProgram *program);
	void useNoShaders(TextureRegistry *textures);
};

#endif