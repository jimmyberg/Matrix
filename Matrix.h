#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>
#include <cmath>
#include <vector>

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
 */
class Matrix
{
public:
	Matrix(size_t size);
	~Matrix();
	/**
	 * @brief      Basic add row operation for this matrix.
	 *
	 * @param[in]  takeRow       The row to take
	 * @param[in]  multiplyWith  Multiply takeRow with this number
	 * @param[in]  addToRow      Answer will be added to addToRow
	 */
	void rowAddRow(int takeRow, double multiplyWith, int addToRow);
	/**
	 * @brief      Switch two rows of this matrix
	 *
	 * @param[in]  rowA  The row a
	 * @param[in]  rowB  The row b
	 */
	void swapRows(unsigned int rowA, unsigned int rowB);
	/**
	 * @brief      Multiply a row in this matrix
	 *
	 * @param[in]  row     The row
	 * @param[in]  factor  The factor
	 */
	void multiplyRow(unsigned int row, double factor);
	/**
	 * @brief      Divide a row in this matrix
	 *
	 * @param[in]  row     The row
	 * @param[in]  factor  The factor
	 */
	void divideRow(unsigned int row, double factor);
	/**
	 * @brief      Determine the determinant. Will yield valid result when
	 *             matrix is echelon sorted.
	 *
	 *             Accounts for previous operations done to the matrix on order
	 *             to get to a echelon matrix.
	 *
	 * @return     The determinant
	 */
	double determinant() const;
	/**
	 * @brief      Solve the matrix to a echelon matrix. This makes the
	 *             determinant accessible.
	 */
	void autoSolve();
	/**
	 * @brief      Reset determinant factors as of the current matrix is the
	 *             original non modified matrix.
	 */
	void resetDeterminantFactor(){determinantFactor = 1;}
	std::vector<double*> A;
	std::vector<double> B;
	size_t size;
	double determinantFactor = 1;
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

#endif //_MATRIX_H_
