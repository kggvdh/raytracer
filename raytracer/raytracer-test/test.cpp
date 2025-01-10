#include "pch.h"
#include "../raytracer/tuple.h"
#include "../raytracer/canvas.h"
#include "../raytracer/matrix.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "../raytracer/utility.h"

// constructor tests
TEST(tuple_tests, tuple_constructor) {
	tuple a = tuple(4.3, -4.2, 3.1, 1.0);
	EXPECT_NEAR(a.x, 4.3, double_error);
	EXPECT_NEAR(a.y, -4.2, double_error);
	EXPECT_NEAR(a.z, 3.1, double_error);
	EXPECT_NEAR(a.w, 1.0, double_error);
}

TEST(tuple_tests, vector_constructor) {
	tuple a = tuple(4.3, -4.2, 3.1, 0.0);
	tuple b = my_vector(4.3, -4.2, 3.1);
	EXPECT_TRUE(a == b);
}

TEST(tuple_tests, point_constructor) {
	tuple a = tuple(4.3, -4.2, 3.1, 1.0);
	tuple b = my_point(4.3, -4.2, 3.1);
	EXPECT_TRUE(a == b);
}

// operator overload tests
TEST(tuple_tests, tuple_equality) {
	tuple a = tuple(1.5, 2.3, -3.7, 1.0);
	tuple b = tuple(1.5, 2.3, -3.7, 1.0);

	tuple c = tuple(1.2, 3.3, 3.7, 1.0);
	tuple d = tuple(1.2, 3.3, 3.7, 0.0);

	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a == c);
	EXPECT_FALSE(a == d);
}

TEST(tuple_tests, adding_two_tuples) {
	tuple a = tuple(3, -2, 5, 1);
	tuple b = tuple(-2, 3, 1, 0);

	EXPECT_TRUE(a + b == tuple(1, 1, 6, 1));
}

TEST(tuple_tests, negating_a_tuple) {
	tuple a = tuple(1, -2, 3, -4);

	EXPECT_TRUE(-a == tuple(-1, 2, -3, 4));
}


TEST(tuple_tests, subtracting_two_points) {
	tuple a = my_point(3, 2, 1);
	tuple b = my_point(5, 6, 7);

	EXPECT_TRUE(a - b == my_vector(-2, -4, -6));
}

TEST(tuple_tests, subtracting_vector_from_point) {
	tuple p = my_point(3, 2, 1);
	tuple v = my_vector(5, 6, 7);

	EXPECT_TRUE(p - v == my_point(-2, -4, -6));
}

TEST(tuple_tests, subtracting_two_vectors) {
	tuple a = my_vector(3, 2, 1);
	tuple b = my_vector(5, 6, 7);

	EXPECT_TRUE(a - b == my_vector(-2, -4, -6));
}

TEST(tuple_tests, multiplying_tuple_by_scalar) {
	tuple a = tuple(1, -2, 3, -4);

	EXPECT_TRUE(a * 3.5 == tuple(3.5, -7, 10.5, -14));
	EXPECT_TRUE(a * 0.5 == tuple(0.5, -1, 1.5, -2));
}

TEST(tuple_tests, dividing_tuple_by_scalar) {
	tuple a = tuple(1, -2, 3, -4);
	EXPECT_TRUE(a / 2 == tuple(0.5, -1, 1.5, -2));
}

TEST(tuple_tests, computing_vector_magnitudes) {
	tuple v1 = my_vector(1, 0, 0);
	EXPECT_NEAR(magnitude(v1), 1.0, double_error);

	tuple v2 = my_vector(0, 1, 0);
	EXPECT_NEAR(magnitude(v2), 1.0, double_error);

	tuple v3 = my_vector(0, 0, 1);
	EXPECT_NEAR(magnitude(v3), 1.0, double_error);

	tuple v4 = my_vector(1, 2, 3);
	EXPECT_NEAR(magnitude(v4), sqrt(14), double_error);

	tuple v5 = my_vector(-1, -2, -3);
	EXPECT_NEAR(magnitude(v5), sqrt(14), double_error);
}

TEST(tuple_tests, computing_normalized_vectors) {
	tuple v1 = my_vector(4, 0, 0);
	EXPECT_TRUE(normalize(v1) == my_vector(1, 0, 0));

	tuple v2 = my_vector(1, 2, 3);
	EXPECT_TRUE(normalize(v2) == my_vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));

	tuple v3 = normalize(v2);
	EXPECT_NEAR(magnitude(v3), 1, double_error);
}

TEST(tuple_tests, computing_dot_product) {
	tuple a = my_vector(1, 2, 3);
	tuple b = my_vector(2, 3, 4);

	EXPECT_NEAR(dot(a, b), 20, double_error);
}

TEST(tuple_tests, computing_cross_product) {
	tuple a = my_vector(1, 2, 3);
	tuple b = my_vector(2, 3, 4);

	EXPECT_TRUE(cross(a, b) == my_vector(-1, 2, -1));
	EXPECT_TRUE(cross(b, a) == my_vector(1, -2, 1));
}

// colour tests

TEST(colour_tests, colours_are_tuples) {
	tuple c = colour(-0.5, 0.4, 1.7);
	EXPECT_NEAR(c.r, -0.5, double_error);
	EXPECT_NEAR(c.g, 0.4, double_error);
	EXPECT_NEAR(c.b, 1.7, double_error);
}

TEST(colour_tests, adding_two_colours) {
	tuple c1 = colour(0.9, 0.6, 0.75);
	tuple c2 = colour(0.7, 0.1, 0.25);

	EXPECT_TRUE(c1 + c2 == colour(1.6, 0.7, 1.0));
}

TEST(colour_tests, subtracting_two_colours) {
	tuple c1 = colour(0.9, 0.6, 0.75);
	tuple c2 = colour(0.7, 0.1, 0.25);

	EXPECT_TRUE(c1 - c2 == colour(0.2, 0.5, 0.5));
}

TEST(colour_tests, multiplying_colour_scalar) {
	tuple c1 = colour(0.2, 0.3, 0.4);

	EXPECT_TRUE(c1 * 2 == colour(0.4, 0.6, 0.8));
}

TEST(colour_tests, multiplying_two_colours) {
	tuple c1 = colour(1, 0.2, 0.4);
	tuple c2 = colour(0.9, 1, 0.1);
	EXPECT_TRUE(c1 * c2 == colour(0.9, 0.2, 0.04));
}

// canvas tests

TEST(canvas_tests, creating_a_canvas) {
	canvas c = canvas(10, 20);

	EXPECT_EQ(c.get_width(), 10);
	EXPECT_EQ(c.get_height(), 20);
}

TEST(canvas_tests, writing_pixels_to_canvas) {
	canvas c = canvas(10, 20);

	tuple red = colour(1, 0, 0);

	c.write_pixel(2, 3, red);

	EXPECT_TRUE(c.pixel_at(2, 3) == red);
}

TEST(canvas_tests, constructing_ppm_header) {
	canvas c = canvas(5, 3);
	std::string s = c.exportPPM();

	std::istringstream stream(s);
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(stream, line)) {
		lines.push_back(line);
	}

	ASSERT_GE(lines.size(), 3);

	std::string firstThreeLines = lines[0] + "\n" + lines[1] + "\n" + lines[2];

	EXPECT_TRUE(firstThreeLines == "P3\n5 3\n255");
}

TEST(canvas_tests, constructing_ppm_body) {
	canvas c = canvas(5, 3);
	tuple c1 = colour(1.5, 0, 0);
	tuple c2 = colour(0, 0.5, 0);
	tuple c3 = colour(-0.5, 0, 1);

	c.write_pixel(0, 0, c1);
	c.write_pixel(2, 1, c2);
	c.write_pixel(4, 2, c3);

	std::string s = c.exportPPM();

	std::istringstream stream(s);
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(stream, line)) {
		lines.push_back(line);
	}

	ASSERT_GE(lines.size(), 6);

	std::string contentLines = lines[3] + "\n" + lines[4] + "\n" + lines[5];

	EXPECT_TRUE(contentLines ==
		"255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
		"0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
		"0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}

// matrix tests

TEST(matrix_tests, matrix_addressing) {

	std::vector<std::vector<double>> arr = {
		{1, 2, 3, 4},
		{5.5, 6.5, 7.5, 8.5},
		{9, 10, 11, 12},
		{13.5, 14.5, 15.5, 16.5}
	};

	matrix m = matrix(arr);

	EXPECT_NEAR(m(0, 0), 1, double_error);
	EXPECT_NEAR(m(0, 3), 4, double_error);
	EXPECT_NEAR(m(1, 0), 5.5, double_error);
	EXPECT_NEAR(m(1, 2), 7.5, double_error);
	EXPECT_NEAR(m(2, 2), 11, double_error);
	EXPECT_NEAR(m(3, 0), 13.5, double_error);
	EXPECT_NEAR(m(3, 2), 15.5, double_error);

	matrix m2 = matrix(2, 2);
	m2(0, 0) = -3;
	m2(0, 1) = 5;
	m2(1, 0) = 1;
	m2(1, 1) = -2;

	EXPECT_NEAR(m2(0, 0), -3, double_error);
	EXPECT_NEAR(m2(1, 1), -2, double_error);
}

TEST(matrix_tests, matrix_equality) {
	std::vector<std::vector<double>> arr = {
	{1, 2, 3, 4},
	{5, 6, 7, 8},
	{9, 8, 7, 6},
	{5, 4, 3, 2}
	};

	std::vector<std::vector<double>> arr2 = {
	{2, 3, 4, 5},
	{6, 7, 8, 9},
	{8, 7, 6, 5},
	{4, 3, 2, 1}
	};

	matrix A = matrix(arr);
	matrix B = matrix(arr);
	matrix C = matrix(arr2);

	EXPECT_TRUE(A == B);
	EXPECT_TRUE(A != C);
}

TEST(matrix_tests, multiply_two_matrices) {
	std::vector<std::vector<double>> arr = {
	{1, 2, 3, 4},
	{5, 6, 7, 8},
	{9, 8, 7, 6},
	{5, 4, 3, 2}
	};

	std::vector<std::vector<double>> arr2 = {
	{-2, 1, 2, 3},
	{3, 2, 1, -1},
	{3, 2, 6, 5},
	{1, 2, 7, 8}
	};


	std::vector<std::vector<double>> arr3 = {
	{17, 19, 50, 48},
	{37, 47, 114, 108},
	{33, 51, 110, 102},
	{13, 23, 46, 42}
	};


	matrix A = matrix(arr);
	matrix B = matrix(arr2);
	matrix C = matrix(arr3);

	matrix D = A * B;

	EXPECT_TRUE(D == C);
}

TEST(matrix_tests, multiply_matrix_vector) {
	std::vector<std::vector<double>> arr = {
	{1, 2, 3, 4},
	{2, 4, 4, 2},
	{8, 6, 4, 1},
	{0, 0, 0, 1}
	};

	matrix A = matrix(arr);
	tuple b = tuple(1, 2, 3, 1);

	EXPECT_TRUE(A * b == tuple(18, 24, 33, 1));
}

TEST(matrix_tests, identity_matrix) {
	std::vector<std::vector<double>> arr = {
	{0, 1, 2, 4},
	{1, 2, 4, 8},
	{2, 4, 8, 16},
	{4, 8, 16, 32}
	};

	matrix A = matrix(arr);
	matrix ident = identity(4);

	EXPECT_TRUE(ident * A == A);

	tuple t = tuple(1, 2, 3, 4);
	EXPECT_TRUE(ident * t == t);
}

TEST(matrix_tests, matrix_transpose) {
	std::vector<std::vector<double>> arr = {
	{0, 9, 3, 0},
	{9, 8, 0, 8},
	{1, 8, 5, 3},
	{0, 0, 5, 8}
	};

	std::vector<std::vector<double>> arr2 = {
	{0, 9, 1, 0},
	{9, 8, 8, 0},
	{3, 0, 5, 5},
	{0, 8, 3, 8}
	};

	matrix A = matrix(arr);
	matrix B = transpose(A);
	matrix C = matrix(arr2);

	EXPECT_TRUE(B == C);

	matrix D = transpose(B);

	EXPECT_TRUE(D == A);

	matrix ident = identity(4);

	EXPECT_TRUE(transpose(ident) == ident);
}

TEST(matrix_tests, submatrix) {
	std::vector<std::vector<double>> arr = {
	{1, 5, 0},
	{-3, 2, 7},
	{0, 6, -3}
	};

	std::vector<std::vector<double>> arr2 = {
	{-3, 2},
	{0, 6}
	};

	matrix A = matrix(arr);
	matrix B = submatrix(A, 0, 2);
	matrix C = matrix(arr2);

	EXPECT_TRUE(B == C);

	std::vector<std::vector<double>> arr3 = {
	{-6, 1, 1, 6},
	{-8, 5, 8, 6},
	{-1, 0, 8, 2},
	{-7, 1, -1, 1}
	};

	std::vector<std::vector<double>> arr4 = {
	{-6, 1, 6},
	{-8, 8, 6},
	{-7, -1, 1}
	};

	matrix D = matrix(arr3);
	matrix E = matrix(arr4);

	EXPECT_TRUE(submatrix(D, 2, 1) == E);
}

TEST(matrix_tests, calculating_minors) {
	std::vector<std::vector<double>> arr = {
	{3, 5, 0},
	{2, -1, -7},
	{6, -1, 5}
	};

	matrix A = matrix(arr);
	matrix B = submatrix(A, 1, 0);

	EXPECT_NEAR(det(B), 25, double_error);
	EXPECT_NEAR(minor(A, 1, 0), 25, double_error);
}

TEST(matrix_tests, calculating_cofactors) {
	std::vector<std::vector<double>> arr = {
	{3, 5, 0},
	{2, -1, -7},
	{6, -1, 5}
	};

	matrix A = matrix(arr);

	EXPECT_NEAR(minor(A, 0, 0), -12, double_error);
	EXPECT_NEAR(cofactor(A, 0, 0), -12, double_error);

	EXPECT_NEAR(minor(A, 1, 0), 25, double_error);
	EXPECT_NEAR(cofactor(A, 1, 0), -25, double_error);
}

TEST(matrix_tests, calculating_determinants_large_matrices) {
	std::vector<std::vector<double>> arr = {
	{1, 2, 6},
	{-5, 8, -4},
	{2, 6, 4}
	};

	matrix A = matrix(arr);

	EXPECT_NEAR(cofactor(A, 0, 0), 56, double_error);
	EXPECT_NEAR(cofactor(A, 0, 1), 12, double_error);
	EXPECT_NEAR(cofactor(A, 0, 2), -46, double_error);
	EXPECT_NEAR(det(A), -196, double_error);

	std::vector<std::vector<double>> arr2 = {
		{-2, -8, 3, 5},
		{-3, 1, 7, 3},
		{1, 2, -9, 6},
		{-6, 7, 7, -9}
	};

	matrix B = matrix(arr2);

	EXPECT_NEAR(cofactor(B, 0, 0), 690, double_error);
	EXPECT_NEAR(cofactor(B, 0, 1), 447, double_error);
	EXPECT_NEAR(cofactor(B, 0, 2), 210, double_error);
	EXPECT_NEAR(cofactor(B, 0, 3), 51, double_error);
	EXPECT_NEAR(det(B), -4071, double_error);
}

TEST(matrix_tests, is_invertible) {
	std::vector<std::vector<double>> arr = {
		{6, 4, 4, 4},
		{5, 5, 7, 6},
		{4, -9, 3, -7},
		{9, 1, 7, -6}
	};
	matrix A = matrix(arr);	
	
	std::vector<std::vector<double>> arr2 = {
		{-4, 2, -2, -3},
		{9, 6, 2, 6},
		{0, -5, 1, -5},
		{0, 0, 0, 0}
	};
	matrix B = matrix(arr2);

	EXPECT_NEAR(det(A), -2120, double_error);

	EXPECT_TRUE(is_invertible(A));
	EXPECT_FALSE(is_invertible(B));
	EXPECT_NEAR(det(B), 0, double_error);
}

TEST(matrix_tests, calculate_matrix_inverse) {
	std::vector<std::vector<double>> arr = {
		{-5, 2, 6, -8},
		{1, -5, 1, 8},
		{7, 7, -6, -7},
		{1, -3, 7, 4}
	};
	matrix A = matrix(arr);

	matrix B = inverse(A);

	std::vector<std::vector<double>> arr2 = {
	{0.21805, 0.45113, 0.24060, -0.04511},
	{-0.80827, -1.45677, -0.44361, 0.52068},
	{-0.07895, -0.22368, -0.05263, 0.19737},
	{-0.52256, -0.81391, -0.30075, 0.30639}
	};
	matrix C = matrix(arr2);

	double rounding_error = 0.00001;

	EXPECT_NEAR(det(A), 532, rounding_error);
	EXPECT_NEAR(minor(A, 2, 3), 160, rounding_error);
	EXPECT_NEAR(cofactor(A, 2, 3), -160, rounding_error);
	EXPECT_NEAR(B(3, 2), -160.0 / 532, rounding_error);
	EXPECT_NEAR(cofactor(A, 3, 2), 105, rounding_error);
	EXPECT_NEAR(B(2, 3), 105.0 / 532, rounding_error);

	EXPECT_TRUE(B.is_equal(C, rounding_error));
}

TEST(matrix_tests, calculate_matrix_inverse_2) {
	std::vector<std::vector<double>> arr = {
		{ 8 , -5 , 9 , 2},
		{ 7 , 5 , 6 , 1},
		{-6 , 0 , 9 , 6},
		{-3 , 0 , -9 , -4}
	};
	matrix A = matrix(arr);

	matrix B = inverse(A);

	std::vector<std::vector<double>> arr2 = {
	{ -0.15385 , -0.15385 , -0.28205 , -0.53846 },
	{-0.07692 , 0.12308 , 0.02564 , 0.03077},
	{ 0.35897 , 0.35897 , 0.43590 , 0.92308},
	{ -0.69231 , -0.69231 , -0.76923 , -1.92308}
	};
	matrix C = matrix(arr2);

	double rounding_error = 0.00001;

	EXPECT_TRUE(B.is_equal(C, rounding_error));
}

TEST(matrix_tests, calculate_matrix_inverse_3) {
	std::vector<std::vector<double>> arr = {
		{9, 3, 0, 9},
		{-5, -2, -6, -3},
		{-4, 9, 6, 4},
		{-7, 6, 6, 2}
	};
	matrix A = matrix(arr);

	matrix B = inverse(A);

	std::vector<std::vector<double>> arr2 = {
	{-0.04074 , -0.07778 , 0.14444 , -0.22222},
	{-0.07778 , 0.03333 , 0.36667 , -0.33333 },
	{-0.02901 , -0.14630 , -0.10926 , 0.12963},
	{ 0.17778 , 0.06667 , -0.26667 , 0.33333 }
	};
	matrix C = matrix(arr2);

	double rounding_error = 0.00001;

	EXPECT_TRUE(B.is_equal(C, rounding_error));
}

TEST(matrix_tests, multiplying_product_by_inverse) {
	std::vector<std::vector<double>> arr = {
	{3, -9, 7, 3},
	{3, -8, 2, -9},
	{-4, 4, 4, 1},
	{-6, 5, -1, 1}
	};
	matrix A = matrix(arr);

	std::vector<std::vector<double>> arr2 = {
	{8, 2, 2, 2},
	{3, -1, 7, 0},
	{7, 0, 5, 4},
	{6, -2, 0, 5}
	};
	matrix B = matrix(arr2);

	matrix C = A * B;

	EXPECT_TRUE(C * inverse(B) == A);
}