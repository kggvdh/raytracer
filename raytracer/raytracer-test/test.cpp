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