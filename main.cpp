#include <iostream>
#include "liniearGausian.h"
#include "Matrix.h"
using namespace std;

void transpose(double A[], size_t size){
	for (unsigned int diagIndex = 0; diagIndex < size; ++diagIndex){
		for (unsigned int remaindingIndex = diagIndex+1; remaindingIndex < size; ++remaindingIndex){
			swap(A[size*remaindingIndex+diagIndex], A[size*diagIndex+remaindingIndex]);
		}
	}
}

int main(int argc, char** argv){
	double A[100*100];
	double B[100];
	double AA[100][100];
	A[3*0+0] = 1; A[3*0+1] = 2; A[3*0+2] = 3;
	A[3*1+0] = 5; A[3*1+1] = 7; A[3*1+2] = 9;
	A[3*2+0] = 2; A[3*2+1] = 1; A[3*2+2] = 6;

	Matrix<3> mat;
	mat.A[0][0] = 1; mat.A[0][1] = 2; mat.A[0][2] = 3;
	mat.A[1][0] = 5; mat.A[1][1] = 7; mat.A[1][2] = 9;
	mat.A[2][0] = 2; mat.A[2][1] = 1; mat.A[2][2] = 6;
	B[0] = 5;
	B[1] = 2;
	B[2] = 3;
	mat.B[0] = 5;
	mat.B[1] = 2;
	mat.B[2] = 3;
	mat.resetDeterminantFactor();
	while(1){
		mat.print();
		cout <<
			"what to do?\n"
			"[0] Row add\n"
			"[1] Switch rows\n"
			"[2] Multiply row\n"
			"[3] Divide row\n"
			"[4] Determinant\n"
			"[5] autoSolve" << endl;
		unsigned int operation;
		cin >> operation;
		switch(operation){
			case 0:{
				unsigned int takeRow;
				double multiplyWith;
				unsigned int addToRow;
				cout << "Row to Take" << endl;
				cin >> takeRow;
				--takeRow;
				cout << "Multiply with" << endl;
				cin >> multiplyWith;
				cout << "Row to add" << endl;
				cin >> addToRow;
				--addToRow;
				mat.rowAddRow(takeRow, multiplyWith, addToRow);
				break;
			}
			case 1:{
				unsigned int rowA;
				unsigned int rowB;
				cout << "First row:" << endl;
				cin >> rowA;
				--rowA;
				cout << "Second row:" << endl;
				cin >> rowB;
				--rowB;
				mat.swapRows(rowA, rowB);
				break;
			}
			case 2:{
				cout << "Please select row:\n";
				unsigned int row;
				cin >> row;
				--row;
				cout << "Multiply with:" << endl;
				double factor;
				cin >> factor;
				mat.multiplyRow(row, factor);
				break;
			}
			case 3:{
				cout << "Please select row:\n";
				unsigned int row;
				cin >> row;
				--row;
				cout << "Divide with:" << endl;
				double factor;
				cin >> factor;
				mat.divideRow(row, factor);
				break;
			}
			case 4:
				cout << "determinant = " << mat.determinant() << endl;
			case 5:
				mat.autoSolve();
		}
	}
	return 0;
}
