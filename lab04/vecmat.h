//Extremely simple vector and matrix classes by Janusz Malinowski. 
#include <stdio.h>

struct Vector
{
	 Vector() { data[0] = 0.0; data[1] = 0.0; data[2] = 1.0; }

	 double GetX() { return data[0]; }
	 double GetY() { return data[1]; }
	 void Print(void) { printf("(%2.3lf,%2.3lf,%2.3lf)\n", data[0], data[1], data[2]); }
	 void Set(double d1, double d2) { data[0] = d1; data[1] = d2; }
	 double data[3];
};

struct Matrix
{
	 friend Vector operator*(const Matrix, const Vector);

	 Matrix() {
		 for (int i = 0; i < 3; ++i)
			 for (int j = 0; j < 3; ++j)
				 data[i][j] = 0.0;

		data[2][2] = 1.0;
	 }

	 void Print(void);
	 Matrix operator*(const Matrix);
	 double data[3][3];
};

void Matrix::Print(void)
{
	printf("\n|%2.3lf,%2.3lf,%2.3lf|\n",data[0][0], data[0][1], data[0][2]);
	printf("|%2.3lf,%2.3lf,%2.3lf|\n",data[1][0], data[1][1], data[1][2]);
	printf("|%2.3lf,%2.3lf,%2.3lf|\n",data[2][0], data[2][1], data[2][2]);
}

Matrix Matrix::operator*(const Matrix gMatrix)
{
	Matrix tmp;

	for (int i=0;i<3;i++)
		for (int j=0;j<3;j++) {

			tmp.data[i][j]=0.0;
			for (int k=0;k<3;k++)
				tmp.data[i][j] = tmp.data[i][j]+(data[i][k]*gMatrix.data[k][j]);
		}
	return tmp;
}

Vector operator*(const Matrix gMatrix,const Vector gVector)
{
	unsigned int i,j;
	Vector tmp;

	for (i=0;i<3;i++) {

		tmp.data[i]=0.0;
		for (j=0;j<3;j++) 
			tmp.data[i]=tmp.data[i]+(gMatrix.data[i][j]*gVector.data[j]);
	}
	return tmp;
}