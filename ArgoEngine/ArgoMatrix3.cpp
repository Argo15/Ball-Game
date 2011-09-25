#include "ArgoMatrix.h"


ArgoMatrix3::ArgoMatrix3()
{
	this->identity();
}

ArgoMatrix3::ArgoMatrix3(float v)
{
	for (int i=0;i<9;i++)
		data[i]=v;
}

ArgoMatrix3::ArgoMatrix3(float *v)
{
	for (int i=0;i<9;i++)
		data[i]=v[i];
}	

ArgoMatrix3::ArgoMatrix3(ArgoMatrix3 &m)
{
	*this=m;
}

ArgoMatrix3::ArgoMatrix3(ArgoMatrix4 &m)
{
	*this=m;
}

float ArgoMatrix3::operator [](unsigned int i)
{
	return data[i];
}

ArgoMatrix3& ArgoMatrix3::operator =(ArgoMatrix3 &m)
{
	for (int i=0;i<9;i++)
		data[i]=m[i];
	return *this;
}

ArgoMatrix3& ArgoMatrix3::operator =(ArgoMatrix4 &m)
{
	this->identity();
	data[0]=m[0];
	data[1]=m[1];
	data[2]=m[2];
	data[3]=m[4];
	data[4]=m[5];
	data[5]=m[6];
	data[6]=m[8];
	data[7]=m[9];
	data[8]=m[10];
	return *this;
}


ArgoMatrix3	&ArgoMatrix3::operator +=(const ArgoMatrix3 &m)
{
	*this=*this+m;
	return *this;
}

ArgoMatrix3	&ArgoMatrix3::operator -= (const ArgoMatrix3 &m)
{
	*this=*this-m;
	return *this;
}

ArgoMatrix3	&ArgoMatrix3::operator /= (const ArgoMatrix3 &m)
{
	*this=*this/m;
	return *this;
}

ArgoMatrix3	&ArgoMatrix3::operator *= (const ArgoMatrix3 &m)
{
	*this=*this*m;
	return *this;
}

ArgoMatrix3	&ArgoMatrix3::operator *= (float f)
{
	for (int i=0;i<9;i++)
		data[i]=data[i]*f;
	return *this;
}

bool ArgoMatrix3::operator ==(const ArgoMatrix3 &m)
{
	for (int i=0;i<9;i++)
		if (data[i]!=m.data[i])
			return false;

	return true;
}

bool ArgoMatrix3::operator !=(const ArgoMatrix3 &m)
{
	return !(*this==m);
}

ArgoMatrix3 ArgoMatrix3::operator +(const ArgoMatrix3 &m)
{
	for (int i=0;i<9;i++)
		data[i]=data[i]+m.data[i];
	return *this;
}

ArgoMatrix3 ArgoMatrix3::operator -(const ArgoMatrix3 &m)
{
	for (int i=0;i<9;i++)
		data[i]=data[i]+m.data[i];
	return *this;
}

ArgoMatrix3 ArgoMatrix3::operator /(const ArgoMatrix3 &m)
{
	// not implemented
	return *this;
}

ArgoMatrix3 ArgoMatrix3::operator *(const ArgoMatrix3 &m)
{
	ArgoVector3 row[3];
	ArgoVector3 col[3];

	row[0].set(data[0],data[3],data[6]);
	row[1].set(data[1],data[4],data[7]);
	row[2].set(data[2],data[5],data[8]);
	col[0].set(m.data[0],m.data[1],m.data[2]);
	col[1].set(m.data[3],m.data[4],m.data[5]);
	col[2].set(m.data[6],m.data[7],m.data[8]);
	data[0]=row[0].dot(col[0]);
	data[1]=row[1].dot(col[0]);
	data[2]=row[2].dot(col[0]);
	data[3]=row[0].dot(col[1]);
	data[4]=row[1].dot(col[1]);
	data[5]=row[2].dot(col[1]);
	data[6]=row[0].dot(col[2]);
	data[7]=row[1].dot(col[2]);
	data[8]=row[2].dot(col[2]);
	return *this;
}

ArgoVector3 ArgoMatrix3::operator *(ArgoVector3 &v)
{
	ArgoVector3 ret;
	ArgoVector3 row[3];

	row[0].set(data[0],data[3],data[6]);
	row[1].set(data[1],data[4],data[7]);
	row[2].set(data[2],data[5],data[8]);

	ret.set(row[0].dot(v),row[1].dot(v),row[2].dot(v));
	return ret;
}

ArgoMatrix3 &ArgoMatrix3::identity()
{
	for(int i=0;i<9;i++)
		data[i]=0;
	data[0]=1.0;
	data[4]=1.0;
	data[8]=1.0;
	return *this;
}

ArgoMatrix3 &ArgoMatrix3::transpose()
{
	ArgoMatrix3 m;
	m.data[0]=data[0];
	m.data[1]=data[3];
	m.data[2]=data[6];
	m.data[3]=data[1];
	m.data[4]=data[4];
	m.data[5]=data[7];
	m.data[6]=data[2];
	m.data[7]=data[5];
	m.data[8]=data[8];
	*this=m;
	return *this;
}