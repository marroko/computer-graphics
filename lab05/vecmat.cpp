#include "vecmat.h"

Vector4 Vector4::operator-(const Vector4 &gVector)
{
	Vector4 Result;
	for (unsigned int i = 0; i < 4; i++)
		Result.data[i] = data[i] - gVector.data[i];
	return Result;
}

Vector4 operator*(const Vector4 &gVector, double val)
{
	Vector4 Result;
	for (unsigned int i = 0; i < 4; i++)
		Result.data[i] = gVector.data[i] * val;
	return Result;
}

Matrix4::Matrix4()
{
	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			data[i][j] = 0.0;

	data[3][3] = 1.0; // always initialized
}

void Matrix4::Print()
{
	printf("\n|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n", data[0][0], data[0][1], data[0][2], data[0][3]);
	printf("|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n", data[1][0], data[1][1], data[1][2], data[1][3]);
	printf("|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n", data[2][0], data[2][1], data[2][2], data[2][3]);
	printf("|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n", data[3][0], data[3][1], data[3][2], data[2][3]);
}

Matrix4 Matrix4::operator*(const Matrix4 gMatrix) const
{
	int i, j, k;
	Matrix4 tmp;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			tmp.data[i][j] = 0.0;
			for (k = 0; k < 4; k++)
				tmp.data[i][j] = tmp.data[i][j] + (data[i][k] * gMatrix.data[k][j]);
		}
	return tmp;
}

Vector4 operator*(const Matrix4 gMatrix, const Vector4 gVector)
{
	Vector4 tmp;

	for (unsigned int i = 0; i < 4; i++)
	{
		tmp.data[i] = 0.0;
		for (unsigned int j = 0; j < 4; j++)
			tmp.data[i] = tmp.data[i] + (gMatrix.data[i][j] * gVector.data[j]);
	}
	return tmp;
}