#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>
#include <cmath>

// #define _DEBUG_MATRIX_AUTOSOLVE_

/**
 * @brief      Class for square matrix with vector.
 *
 *             This is used to solve equations of type A*x=b. Where A is the
 *             square matrix, x is the coefficient vector = {x1, x2, x3 ...} and
 *             b is vector with results. When solving A until is a identity
 *             matrix, b will have the solution of every coefficient. Proof:
 *             A*x=b => A^-1*A*x=A^-1*b => I*x=A^-1*b => x=A^-1*b where A^-1*b is the
 *             solution to the coefficient vector x.
 *
 * @tparam     size  size of square matrix.
 */
template<size_t size>
class Matrix
{
public:
	/**
	 * @brief      Basic add row operation for this matrix.
	 *
	 * @param[in]  takeRow       The row to take
	 * @param[in]  multiplyWith  Multiply takeRow with this number
	 * @param[in]  addToRow      Answer will be added to addToRow
	 */
	void rowAddRow(int takeRow, double multiplyWith, int addToRow){
		for (unsigned int colIndex = 0; colIndex < size; ++colIndex){
			A[addToRow][colIndex] += A[takeRow][colIndex] * multiplyWith;
		}
		B[addToRow] += B[takeRow] * multiplyWith;
	}
	/**
	 * @brief      Switch two rows of this matrix
	 *
	 * @param[in]  rowA  The row a
	 * @param[in]  rowB  The row b
	 */
	void swapRows(unsigned int rowA, unsigned int rowB){
		if(rowA == rowB)
			return;
		std::swap(A[rowA], A[rowB]);
		std::swap(B[rowA], B[rowB]);
		determinantFactor *= -1;
	}
	/**
	 * @brief      Multiply a row in this matrix
	 *
	 * @param[in]  row     The row
	 * @param[in]  factor  The factor
	 */
	void multiplyRow(unsigned int row, double factor){
		for (unsigned int colIndex = 0; colIndex < size; ++colIndex)
			A[row][colIndex] *= factor;
		B[row] *= factor;
		determinantFactor /= factor;
	}
	/**
	 * @brief      Divide a row in this matrix
	 *
	 * @param[in]  row     The row
	 * @param[in]  factor  The factor
	 */
	void divideRow(unsigned int row, double factor){
		for (unsigned int colIndex = 0; colIndex < size; ++colIndex)
			A[row][colIndex] /= factor;
		B[row] /= factor;
		determinantFactor *= factor;
	}
	/**
	 * @brief      Determine the determinant. Will yield valid result when
	 *             matrix is echelon sorted.
	 *
	 *             Accounts for previous operations done to the matrix on order
	 *             to get to a echelon matrix.
	 *
	 * @return     The determinant
	 */
	double determinant() const{
		double determinant = determinantFactor;
		for (unsigned int diagIndex = 0; diagIndex < size; ++diagIndex)
			determinant *= A[diagIndex][diagIndex];
		return determinant;
	}
	/**
	 * @brief      Solve the matrix to a echelon matrix. This makes the
	 *             determinant accessible.
	 */
	void autoSolve(){
		#ifdef _DEBUG_MATRIX_AUTOSOLVE_
		print();
		std::cout << '\n';
		#endif
		// Sort pivots. Results in less rounding errors.
		for (unsigned int diagIndex = 0; diagIndex < size; ++diagIndex){
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
				print();
				std::cout << '\n';
				#endif
			}
		}
		// Now make matrix echelon
		for (unsigned int diagIndex = 0; diagIndex < size; ++diagIndex){
			for (unsigned int rowIndex = diagIndex+1; rowIndex < size; ++rowIndex){
				double factor = -A[rowIndex][diagIndex] / A[diagIndex][diagIndex];
				rowAddRow(diagIndex, factor, rowIndex);
				// Should be zero, but subtracting floating points can have very
				// small rounding errors. Thus we force it to be zero.
				A[rowIndex][diagIndex] = 0;
				#ifdef _DEBUG_MATRIX_AUTOSOLVE_
				std::cout << "Add row " << diagIndex+1 << " to " << rowIndex+1 << " by factor " << factor << '\n';
				print();
				std::cout << '\n';
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
				print();
				std::cout << '\n';
				#endif
			}
			divideRow(diagIndex, A[diagIndex][diagIndex]);
			#ifdef _DEBUG_MATRIX_AUTOSOLVE_
			std::cout << "Normalized row " << diagIndex+1 << '\n';
			print();
			std::cout << '\n';
			#endif
		}

	}
	/**
	 * @brief      Print current matrix to the terminal.
	 */
	void print() const{
		for (unsigned int rowIndex = 0; rowIndex < size; ++rowIndex){
			for (unsigned int colIndex = 0; colIndex < size; ++colIndex){
				std::cout.width(12);
				std::cout << A[rowIndex][colIndex];
			}
			std::cout << '|';
			std::cout.width(12);
			std::cout << B[rowIndex] << std::endl;
		}
	}
	/**
	 * @brief      Reset determinant factors as of the current matrix is the
	 *             original non modified matrix.
	 */
	void resetDeterminantFactor(){determinantFactor = 1;}
	double A[size][size];
	double B[size];
	double determinantFactor = 1;
};

#endif //_MATRIX_H_
