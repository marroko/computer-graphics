#pragma once
#include <stdio.h>

class Vector4
{
public:

	friend Vector4 operator*(const Vector4 &, double);

	Vector4() { data[0] = 0.0; data[1] = 0.0; data[2] = 0.0; data[3] = 1.0; }
	double data[4];

	void Print() { printf("(%2.3lf,%2.3lf,%2.3lf,%2.3lf)\n", data[0], data[1], data[2], data[3]); }
	void Set(double d1, double d2, double d3) { data[0] = d1; data[1] = d2; data[2] = d3; }

	double GetX() { return data[0]; }
	double GetY() { return data[1]; }
	double GetZ() { return data[2]; }
	Vector4 operator-(const Vector4 &);
};

class Matrix4 {

public:

	friend Vector4 operator*(const Matrix4, const Vector4);

	Matrix4();
	double data[4][4];

	void Print();
	Matrix4 operator*(const Matrix4) const;
};