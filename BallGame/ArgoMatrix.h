#ifndef ARGOMATRIX_H
#define ARGOMATRIX_H

#include <windows.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include <math.h>

class ArgoMatrix3;
class ArgoMatrix4;
class ArgoVector3;
class ArgoVector4;

class ArgoMatrix4
{
private:
	float data[16];	  /*| 0  4  8   12 |
						| 1  5  9   13 |
						| 2  6  10  14 |
						| 3  7  11  15 |*/
public:
	// constructors
	ArgoMatrix4();
	ArgoMatrix4(float v);
	ArgoMatrix4(float *v);
	ArgoMatrix4(ArgoMatrix4 &m);
	ArgoMatrix4(ArgoMatrix3 &m);

	// operators
	float		 operator [] (unsigned int i);
	ArgoMatrix4	&operator =  (ArgoMatrix4 &m);
	ArgoMatrix4	&operator =  (ArgoMatrix3 &m);
	ArgoMatrix4	&operator += (ArgoMatrix4 &m);
	ArgoMatrix4	&operator -= (ArgoMatrix4 &m);
	ArgoMatrix4	&operator /= (ArgoMatrix4 &m);
	ArgoMatrix4	&operator *= (ArgoMatrix4 &m);
	ArgoMatrix4	&operator *= (float f);
	bool		 operator == (ArgoMatrix4 &m);
	bool		 operator != (ArgoMatrix4 &m);
	ArgoMatrix4	 operator +	 (ArgoMatrix4 &m);
	ArgoMatrix4	 operator -	 (ArgoMatrix4 &m);
	ArgoMatrix4	 operator /	 (ArgoMatrix4 &m);
	ArgoMatrix4	 operator *	 (ArgoMatrix4 &m);
	ArgoVector4  operator *  (ArgoVector4 &v);

	// methods
	ArgoMatrix4 &identity();
	ArgoMatrix4 &transpose();
	ArgoMatrix4 &inverse();
	ArgoMatrix4 &setAsModelViewProjection();
	ArgoMatrix4 &setAsModelViewMatrix();
	ArgoMatrix4 &setAsProjectionMatrix();
	void multiplyToCurrent() {glMultMatrixf(data);}
};











class ArgoMatrix3
{
private:
	float data[9];	  /*| 0  3  6 |
						| 1  4  7 |
						| 2  5  8 |*/
public:
	// constructors
	ArgoMatrix3();
	ArgoMatrix3(float v);
	ArgoMatrix3(float *v);
	ArgoMatrix3(ArgoMatrix3 &m);
	ArgoMatrix3(ArgoMatrix4 &m);

	// operators
	float		 operator [] (unsigned int i);
	ArgoMatrix3	&operator =  (ArgoMatrix3 &m);
	ArgoMatrix3	&operator =  (ArgoMatrix4 &m);
	ArgoMatrix3	&operator += (const ArgoMatrix3 &m);
	ArgoMatrix3	&operator -= (const ArgoMatrix3 &m);
	ArgoMatrix3	&operator /= (const ArgoMatrix3 &m);
	ArgoMatrix3	&operator *= (const ArgoMatrix3 &m);
	ArgoMatrix3	&operator *= (float f);
	bool		 operator == (const ArgoMatrix3 &m);
	bool		 operator != (const ArgoMatrix3 &m);
	ArgoMatrix3  operator +	 (const ArgoMatrix3 &m);
	ArgoMatrix3  operator -	 (const ArgoMatrix3 &m);
	ArgoMatrix3  operator /	 (const ArgoMatrix3 &m);
	ArgoMatrix3  operator *	 (const ArgoMatrix3 &m);
	ArgoVector3  operator *  (ArgoVector3 &v);

	// methods
	ArgoMatrix3 &identity();
	ArgoMatrix3 &transpose();
};











class ArgoVector4
{
private:
	float data[4];

public:
	// constructors
	ArgoVector4();
	ArgoVector4(float v);
	ArgoVector4(float x,float y,float z,float w);
	ArgoVector4(ArgoVector4 &v);
	ArgoVector4(ArgoVector3 &v);

	// operators
	float		&operator [] (unsigned int i);
	ArgoVector4	&operator =  (ArgoVector4 &v);
	ArgoVector4	&operator =  (ArgoVector3 &v);
	ArgoVector4	&operator += (ArgoVector4 &v);
	ArgoVector4	&operator -= (ArgoVector4 &v);
	ArgoVector4	&operator /= (ArgoVector4 &v);
	ArgoVector4	&operator *= (ArgoVector4 &v);
	ArgoVector4	&operator *= (float f);
	bool		 operator == (ArgoVector4 &v);
	bool		 operator != (ArgoVector4 &v);
	ArgoVector4  operator +	 (ArgoVector4 &v);
	ArgoVector4  operator -	 (ArgoVector4 &v);
	ArgoVector4  operator /	 (ArgoVector4 &v);
	ArgoVector4  operator *	 (ArgoVector4 &v);
	ArgoVector4  operator *	 (float f);

	// methods
	void set(float x, float y, float z, float w);
	float length();
	bool isZero();
	ArgoVector4 &normalize();
	float dot(ArgoVector4 &v);
	void rotate(float angle, float x, float y, float z);
};










class ArgoVector3
{
private:
	float data[3];

public:
	// constructors
	ArgoVector3();
	ArgoVector3(float v);
	ArgoVector3(float x,float y,float z);
	ArgoVector3(ArgoVector3 &v);
	ArgoVector3(ArgoVector4 &v);

	// operators
	float		&operator [] (unsigned int i);
	ArgoVector3	&operator =  (ArgoVector3 &v);
	ArgoVector3	&operator =  (ArgoVector4 &v);
	ArgoVector3	&operator += (ArgoVector3 &v);
	ArgoVector3	&operator -= (ArgoVector3 &v);
	ArgoVector3	&operator /= (ArgoVector3 &v);
	ArgoVector3	&operator *= (ArgoVector3 &v);
	ArgoVector3	&operator *= (float f);
	bool		 operator == (ArgoVector3 &v);
	bool		 operator != (ArgoVector3 &v);
	ArgoVector3  operator +	 (ArgoVector3 &v);
	ArgoVector3  operator -	 (ArgoVector3 &v);
	ArgoVector3  operator /	 (ArgoVector3 &v);
	ArgoVector3  operator *	 (ArgoVector3 &v);
	ArgoVector3  operator *	 (float f);

	// methods
	void set(float x, float y, float z);
	float length();
	bool isZero();
	ArgoVector3 &normalize();
	float dot(ArgoVector3 &v);
	ArgoVector3 cross(ArgoVector3 &v);
};


class ArgoQuaternion
{
private:
	ArgoVector3 v_data;
	float		s_data;

public:
	ArgoQuaternion();
	ArgoQuaternion(float s, float v1, float v2, float v3);
	void createQuaternion(float angle, float axis_x, float axis_y, float axis_z);
	ArgoQuaternion normalize();
	ArgoMatrix4 getMatrix();

	float			&operator [] (unsigned int i);
	ArgoQuaternion	&operator *= (ArgoQuaternion &q);
	bool			operator ==  (ArgoQuaternion &q);
	bool			operator !=  (ArgoQuaternion &q);
	ArgoQuaternion  operator *	 (ArgoQuaternion &q);
};

#endif