#include "utility.h"
#include <cstdlib>
#pragma once

bool doubles_equal(double lhs, double rhs) {
	return abs(lhs - rhs) < double_error;
}

double clamp(double& input, double min, double max)
{
	if (input < min) return min;
	if (input > max) return max;
	return input;
}