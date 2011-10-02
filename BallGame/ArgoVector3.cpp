#include <math.h>
#include "ArgoMatrix.h"


ArgoVector3::ArgoVector3()
{
	for (int i=0;i<3;i++)
		data[i]=0;
}

ArgoVector3::ArgoVector3(float v)
{
	for (int i=0;i<3;i++)
		data[i]=v;
}

ArgoVector3::ArgoVector3(float x,float y,float z)
{
	data[0]=x;
	data[1]=y;
	data[2]=z;
}

ArgoVector3::ArgoVector3(ArgoVector3 &v)
{
	*this=v;
}

ArgoVector3::ArgoVector3(ArgoVector4 &v)
{
	*this=v;
}

float &ArgoVector3::operator [](unsigned int i)
{
	return  data[i];
}

ArgoVector3	&ArgoVector3::operator =(ArgoVector3 &v)
{
	for (int i=0;i<3;i++)
		data[i]=v[i];
	return *this;
}

ArgoVector3	&ArgoVector3::operator =(ArgoVector4 &v)
{
	for (int i=0;i<3;i++)
		data[i]=v[i];
	return *this;
}


ArgoVector3	&ArgoVector3::operator +=(ArgoVector3 &v)
{
	*this=*this+v;
	return *this;
}

ArgoVector3	&ArgoVector3::operator -=(ArgoVector3 &v)
{
	*this=*this-v;
	return *this;
}

ArgoVector3	&ArgoVector3::operator /=(ArgoVector3 &v)
{
	*this=*this/v;
	return *this;
}

ArgoVector3	&ArgoVector3::operator *=(ArgoVector3 &v)
{
	*this=*this*v;
	return *this;
}

ArgoVector3	&ArgoVector3::operator *=(float f)
{
	data[0]=data[0]*f;
	data[1]=data[1]*f;
	data[2]=data[2]*f;
	return *this;
}

bool ArgoVector3::operator ==(ArgoVector3 &v)
{
	for (int i=0;i<3;i++)
		if (data[i]!=v[i])
			return false;

	return true;
}

bool ArgoVector3::operator !=(ArgoVector3 &v)
{
	return !(*this==v);
}

ArgoVector3  ArgoVector3::operator +(ArgoVector3 &v)
{
	ArgoVector3 ret = *this;
	for (int i=0;i<3;i++)
		ret[i]=ret[i]+v[i];
	return ret;
}

ArgoVector3  ArgoVector3::operator -(ArgoVector3 &v)
{
	ArgoVector3 ret = *this;
	for (int i=0;i<3;i++)
		ret[i]=ret[i]-v[i];
	return ret;
}

ArgoVector3  ArgoVector3::operator /(ArgoVector3 &v)
{
	ArgoVector3 ret = *this;
	for (int i=0;i<3;i++)
		ret[i]=ret[i]/v[i];
	return ret;
}

ArgoVector3  ArgoVector3::operator *(ArgoVector3 &v)
{
	ArgoVector3 ret = *this;
	for (int i=0;i<3;i++)
		ret[i]=ret[i]*v[i];
	return ret;
}

ArgoVector3  ArgoVector3::operator *(float f)
{
	ArgoVector3 ret = *this;
	for (int i=0;i<3;i++)
		ret[i]=ret[i]*f;
	return ret;
}

void ArgoVector3::set(float x, float y, float z)
{
	data[0]=x;
	data[1]=y;
	data[2]=z;
}

float ArgoVector3::length()
{
	return sqrtf(data[0]*data[0]+data[1]*data[1]+data[2]*data[2]);
}

bool ArgoVector3::isZero()
{
	return (data[0]==0 && data[1]==0 && data[2]==0);

}

ArgoVector3 &ArgoVector3::normalize()
{
	float length = this->length();
	for (int i=0;i<3;i++)
		data[i]/=length;
	return *this;
}

float ArgoVector3::dot(ArgoVector3 &v)
{
	return (data[0]*v[0]+data[1]*v[1]+data[2]*v[2]);
}

ArgoVector3 ArgoVector3::cross(ArgoVector3 &v)
{
	return ArgoVector3(data[1]*v[2]-data[2]*v[1],data[2]*v[0]-data[0]*v[2],data[0]*v[1]-data[1]*v[0]);
}