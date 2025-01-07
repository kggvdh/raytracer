#include <vector>

#pragma once
class matrix
{
public:
	matrix(int rows, int cols);
	matrix(std::vector<std::vector<double>> d);
	
	double& operator()(int i, int j);
	double operator()(int i, int j) const;

	bool operator== (const matrix& other);
	bool operator!= (const matrix& other);

	std::vector<double> getRawData();

private:
	// matrix data is row then column rather than column then row.
	std::vector<double> data;

	int num_rows, num_cols;
};

