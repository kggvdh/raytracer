#include <stdexcept>

#pragma once

class tuple
{
public:

	tuple();
	tuple(double _x, double _y, double _z, double _w);
	tuple(const tuple& t);

	void set(double _x, double _y, double _z, double _w = 0);

	tuple operator= (const tuple& other);

	double x;
	double y;
	double z;
	double w;

	// for when tuple is used for colours.
	double& r = x;
	double& g = y;
	double& b = z;
};

bool is_vector(const tuple& t);

double magnitude(const tuple& t);

tuple normalize(const tuple& t);

float dot(const tuple& lhs, const tuple& rhs);

tuple cross(const tuple& lhs, const tuple& rhs);

bool operator== (const tuple& lhs, const tuple& rhs);

tuple operator+ (const tuple& lhs, const tuple& rhs);

tuple operator* (const tuple& lhs, const double& rhs);
tuple operator* (const double& lhs, const tuple& rhs);

tuple operator* (const tuple& lhs, const tuple& rhs);

tuple operator/(const tuple& lhs, const double& rhs);

tuple operator- (const tuple& lhs, const tuple& rhs);

tuple operator- (const tuple& lhs);

tuple my_vector(double _x, double _y, double _z);

tuple my_point(double _x, double _y, double _z);

tuple colour(double _r, double _b, double _g);