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
	if (i > num_rows || j > num_cols) throw;

	return data[i * num_cols + j];
}

double matrix::operator()(int i, int j) const
{
	if (i > num_rows || j > num_cols) throw;

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

std::vector<double> matrix::getRawData()
{
	return data;
}

