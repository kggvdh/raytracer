#pragma once
const double double_error = 1.0E-10;

bool doubles_equal(double lhs, double rhs);

double clamp(double& input, double min = 0, double max = 1);