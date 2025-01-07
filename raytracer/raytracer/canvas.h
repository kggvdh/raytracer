#include <vector>
#include <string>
#include "tuple.h"

#pragma once
class canvas
{
public:
	canvas(int w, int h);

	void clear_canvas();
	void resize_canvas(int w, int h);

	int get_width();
	int get_height();

	void write_pixel(int x, int y, tuple c);
	tuple& pixel_at(int x, int y);

	std::string exportPPM();

private:
	int width;
	int height;

	std::vector<std::vector<tuple>> pixels;
};

