#include "matrix.h"
#include <exception>
#include "utility.h"

matrix::matrix(int rows, int cols)
{
	num_rows = rows;
	num_cols = cols;
	// initialize data
	data = std::vector<double>(num_rows * num_cols);
}

matrix::matrix(std::vector<std::vector<double>> d) {

	num_rows = d.size();
	num_cols = d[0].size();
	data = std::vector<double>(num_rows * num_cols);

	int index = 0;

	for (auto& row : d) {
		for (auto& num : row) {
			data[index] = num;
			index++;
		}
	}
}

double& matrix::operator()(int i, int j)
{
	if (i >= num_rows || j >= num_cols) throw;

	return data[i * num_cols + j];
}

double matrix::operator()(int i, int j) const
{
	if (i >= num_rows || j >= num_cols) throw;

	return data[i * num_cols + j];
}

bool matrix::operator==(const matrix& other)
{
	if (num_rows != other.num_rows || num_cols != other.num_cols) {
		return false;
	}

	for (int i = 0; i < data.size(); i++) {
		if (!doubles_equal(data[i], other.data[i])) {
			return false;
		}
	}

	// if we have got here then all elements are the same.
	return true;
}

bool matrix::operator!=(const matrix& other)
{
	return !(operator==(other));
}

tuple matrix::get_column_vector(int index)
{
	return tuple(get(0, index), get(1, index), get(2, index), get(3, index));
}

matrix matrix::operator*(const matrix& other)
{
	matrix m = matrix(4, 4);

	matrix& t = (*this);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m(i, j) =
				t(i, 0) * other(0, j) +
				t(i, 1) * other(1, j) +
				t(i, 2) * other(2, j) +
				t(i, 3) * other(3, j);
		}
	}

	return m;
}

matrix matrix::operator*(const double other)
{
	matrix n = matrix(num_rows, num_cols);

	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			n(i, j) = (*this)(i, j) * other;
		}
	}

	return n;
}

matrix matrix::operator/(const double other)
{
	return operator*(1 / other);
}

tuple matrix::operator*(const tuple& other)
{
	return other.x * get_column_vector(0) +
		other.y * get_column_vector(1) +
		other.z * get_column_vector(2) +
		other.w * get_column_vector(3);
}

bool matrix::is_equal(matrix& other, double threshold)
{
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			if (abs((*this)(i, j) - other(i, j)) > threshold) {
				return false;
			}
		}
	}

	return true;
}

std::vector<double> matrix::getRawData()
{
	return data;
}

double& matrix::get(int i, int j)
{
	return (*this)(i, j);
}

matrix identity(int size)
{
	matrix m = matrix(size, size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m(i, j) = (i == j ? 1 : 0);
		}
	}

	return m;
}

matrix submatrix(matrix& m, int row, int column)
{
	matrix to_return = matrix(m.num_rows - 1, m.num_cols - 1);

	for (int i = 0; i < m.num_rows; i++) {
		for (int j = 0; j < m.num_cols; j++) {
			if (i != row && j != column) {
				to_return(i > row ? i - 1 : i, j > column ? j - 1 : j) = m(i, j);
			}
		}
	}

	return to_return;
}

matrix transpose(matrix& m)
{
	// create a new matrix with num_rows and num_cols switched
	matrix n = matrix(m.num_cols, m.num_rows);
	for (int i = 0; i < m.num_rows; i++) {
		for (int j = 0; j < m.num_cols; j++) {
			n(j, i) = m(i, j);
		}
	}

	return n;
}

double det(matrix& m)
{
	if (m.num_rows != m.num_cols) return 0;

	double det = 0;

	// check if we have a 2x2 matrix (base case)
	if (m.num_cols == 2) {
		det += m(0, 0) * m(1, 1) -
			m(0, 1) * m(1, 0);
	}
	else {
		for (int i = 0; i < m.num_cols; i++) {
			det += m(0, i) * cofactor(m, 0, i);
		}
	}

	return det;
}

double minor(matrix& m, int row, int col)
{
	matrix a = submatrix(m, row, col);
	return det(a);
}

double cofactor(matrix& m, int row, int col)
{
	return ((row + col) % 2 == 1 ? -1 : 1) * minor(m, row, col);
}

bool is_invertible(matrix& m)
{
	return !doubles_equal(det(m), 0);
}

matrix inverse(matrix& m)
{
	if (!is_invertible(m)) {
		throw;
	}

	matrix n = matrix(m.num_cols, m.num_cols);

	for (int i = 0; i < m.num_rows; i++) {
		for (int j = 0; j < m.num_cols; j++) {
			n(i, j) = cofactor(m, i, j);
		}
	}

	matrix n_transpose = transpose(n);

	matrix m_inverse = n_transpose / det(m);

	return m_inverse;
}
