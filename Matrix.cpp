
#include "Matrix.h"

// #define _DEBUG_MATRIX_AUTOSOLVE_

Matrix::Matrix(size_t size):size(size){
	A.resize(size);
	B.resize(size);
	for (unsigned int rowIndex = 0; rowIndex < size; ++rowIndex)
	{
		A[rowIndex] = new double[size];
	}
	resetDeterminantFactor();
}
Matrix::~Matrix(){
	for (unsigned int rowIndex = 0; rowIndex < size; ++rowIndex)
	{
		A[rowIndex] = new double[size];
	}
}

void Matrix::rowAddRow(int takeRow, double multiplyWith, int addToRow){
	for (unsigned int colIndex = 0; colIndex < size; ++colIndex){
		A[addToRow][colIndex] += A[takeRow][colIndex] * multiplyWith;
	}
	B[addToRow] += B[takeRow] * multiplyWith;
}

void Matrix::swapRows(unsigned int rowA, unsigned int rowB){
	if(rowA == rowB)
		return;
	std::swap(A[rowA], A[rowB]);
	std::swap(B[rowA], B[rowB]);
	determinantFactor *= -1;
}

void Matrix::multiplyRow(unsigned int row, double factor){
	for (unsigned int colIndex = 0; colIndex < size; ++colIndex)
		A[row][colIndex] *= factor;
	B[row] *= factor;
	determinantFactor /= factor;
}

void Matrix::divideRow(unsigned int row, double factor){
	for (unsigned int colIndex = 0; colIndex < size; ++colIndex)
		A[row][colIndex] /= factor;
	B[row] /= factor;
	determinantFactor *= factor;
}

double Matrix::determinant() const{
	double determinant = determinantFactor;
	for (unsigned int diagIndex = 0; diagIndex < size; ++diagIndex)
		determinant *= A[diagIndex][diagIndex];
	return determinant;
}

void Matrix::autoSolve(){
	#ifdef _DEBUG_MATRIX_AUTOSOLVE_
	std::cout << *this << '\n';
	std::cout << std::endl;
	#endif
	// Make matrix echelon
	for (unsigned int diagIndex = 0; diagIndex < size; ++diagIndex){
		// Sort pivot. Results in less rounding errors.
		double currentMaxVal = std::abs(A[diagIndex][diagIndex]);
		unsigned int currentMaxIndex = diagIndex;
		// Look for larger values down of current diagonal value
		for (unsigned int rowIndex = diagIndex+1; rowIndex < size; ++rowIndex){
			double currentVal = std::abs(A[rowIndex][diagIndex]);
			if(currentVal > currentMaxVal){
				currentMaxVal = currentVal;
				currentMaxIndex = rowIndex;
			}
		}

		// Conclude if swap is required.
		if(currentMaxIndex != diagIndex){
			swapRows(currentMaxIndex, diagIndex);
			#ifdef _DEBUG_MATRIX_AUTOSOLVE_
			std::cout << "Swaped row " << currentMaxIndex+1 << " and " << diagIndex+1 << '\n';
			std::cout << *this << '\n';
			std::cout << std::endl;
			#endif
		}
		// Make everything below the current diagonal zero
		for (unsigned int rowIndex = diagIndex+1; rowIndex < size; ++rowIndex){
			double factor = -A[rowIndex][diagIndex] / A[diagIndex][diagIndex];
			rowAddRow(diagIndex, factor, rowIndex);
			// Should be zero, but subtracting floating points can have very
			// small rounding errors. Thus we force it to be zero.
			A[rowIndex][diagIndex] = 0;
			#ifdef _DEBUG_MATRIX_AUTOSOLVE_
			std::cout << "Add row " << diagIndex+1 << " to " << rowIndex+1 << " by factor " << factor << '\n';
			std::cout << *this << '\n';
			std::cout << std::endl;
			#endif
		}
	}

	// Turn into unity matrix.
	for (unsigned int diagIndex = size; diagIndex-- != 0;){
		for (unsigned int rowIndex = diagIndex; rowIndex-- != 0;){
			double factor = -A[rowIndex][diagIndex] / A[diagIndex][diagIndex];
			rowAddRow(diagIndex, factor, rowIndex);
			// Should be zero, but subtracting floating points can have very
			// small rounding errors. Thus we force it to be zero.
			A[rowIndex][diagIndex] = 0;
			#ifdef _DEBUG_MATRIX_AUTOSOLVE_
			std::cout << "Add row " << diagIndex+1 << " to " << rowIndex+1 << " by factor " << factor << '\n';
			std::cout << *this << '\n';
			std::cout << std::endl;
			#endif
		}
		divideRow(diagIndex, A[diagIndex][diagIndex]);
		#ifdef _DEBUG_MATRIX_AUTOSOLVE_
		std::cout << "Normalized row " << diagIndex+1 << '\n';
		std::cout << *this << '\n';
		std::cout << std::endl;
		#endif
	}

}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
	for (unsigned int rowIndex = 0; rowIndex < matrix.size; ++rowIndex){
		for (unsigned int colIndex = 0; colIndex < matrix.size; ++colIndex){
			os.width(12);
			os << matrix.A[rowIndex][colIndex];
		}
		os << '|';
		os.width(12);
		os << matrix.B[rowIndex] << std::endl;
	}
	return os;
}
