#include "tuple.h"
#include <cstdlib>
#include "utility.h"
#pragma once

tuple::tuple() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

tuple::tuple(double _x, double _y, double _z, double _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

tuple::tuple(const tuple& t) {
	x = t.x;
	y = t.y;
	z = t.z;
	w = t.w;
}

void tuple::set(double _x, double _y, double _z, double _w) {
	x = _x, y = _y, z = _z; w = _w;
}

tuple tuple::operator= (const tuple& other) {
	return tuple(other);
}

bool is_vector(const tuple& t) {
	return doubles_equal(t.w, 0.0);
}

double magnitude(const tuple& t) {
	if (!is_vector(t)) {
		throw std::invalid_argument("Cannot take the magnitude of a non-vector");
	}
	return sqrt(t.x * t.x + t.y * t.y + t.z * t.z);
}

tuple normalize(const tuple& t) {
	if (!is_vector(t)) {
		throw std::invalid_argument("Cannot normalize a non-vector");
	}
	double m = magnitude(t);
	return t / m;
}

float dot(const tuple& lhs, const tuple& rhs) {
	if (!(is_vector(lhs) && is_vector(rhs))) {
		throw std::invalid_argument("Cannot take the dot products of non-vectors");
	}
	return	lhs.x * rhs.x + 
			lhs.y * rhs.y + 
			lhs.z * rhs.z + 
			lhs.w * rhs.w;
}


tuple cross(const tuple& lhs, const tuple& rhs) {
	if (!(is_vector(lhs) && is_vector(rhs))) {
		throw std::invalid_argument("Cannot take the dot products of non-vectors");
	}
	return	my_vector(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x);
}

bool operator== (tuple const& lhs, tuple const& rhs) {
	return doubles_equal(lhs.x, rhs.x) &&
		doubles_equal(lhs.y, rhs.y) &&
		doubles_equal(lhs.z, rhs.z) &&
		doubles_equal(lhs.w, rhs.w);
}

tuple operator+ (tuple const& lhs, tuple const& rhs) {
	return tuple(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

tuple operator* (const tuple& lhs, const double& rhs) {
	return tuple(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
}
tuple operator* (const double& lhs, const tuple& rhs) {
	return rhs * lhs;
}

// this is only used for colour multiplication - it's just pairwise multiplication
tuple operator* (const tuple& lhs, const tuple& rhs) {
	return tuple(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, 0);
}

tuple operator/(const tuple& lhs, const double& rhs) {
	return lhs * (1.0 / rhs);
}

tuple operator- (const tuple& lhs, const tuple& rhs) {
	return lhs + (-rhs);
}

tuple operator- (const tuple& lhs) {
	return tuple(-lhs.x, -lhs.y, -lhs.z, -lhs.w);
}

tuple my_vector(double _x, double _y, double _z) {
	return tuple(_x, _y, _z, 0.0);
}

tuple my_point(double _x, double _y, double _z) {
	return tuple(_x, _y, _z, 1.0);
}


tuple colour(double _r, double _b, double _g) {
	return tuple(_r, _b, _g, 0);
}