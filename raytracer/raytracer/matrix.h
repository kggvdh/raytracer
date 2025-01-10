#include <vector>
#include "tuple.h"

#pragma once
class matrix
{
public:
	int num_rows, num_cols;

	matrix(int rows, int cols);
	matrix(std::vector<std::vector<double>> d);
	
	double& operator()(int i, int j);
	double operator()(int i, int j) const;

	bool operator== (const matrix& other);
	bool operator!= (const matrix& other);

	tuple get_column_vector(int index);

	matrix operator* (const matrix& other);
	matrix operator* (const double other);
	matrix operator/ (const double other);
	tuple operator* (const tuple& other);

	bool is_equal(matrix& other, double threshold);

	std::vector<double> getRawData();

private:
	// matrix data is row then column rather than column then row.
	std::vector<double> data;

	double& get(int i, int j);
};

matrix identity(int size);
matrix submatrix(matrix& m, int row, int column);

matrix transpose(matrix& m);

double det(matrix& m);

double minor(matrix& m, int row, int col);

double cofactor(matrix& m, int row, int col);

bool is_invertible(matrix& m);

matrix inverse(matrix& m);

