#include "canvas.h"
#include <sstream>
#include "utility.h"

canvas::canvas(int w, int h) 
	: width(w), height(h), pixels(width, std::vector<tuple>(height)) {

	clear_canvas();
}

void canvas::clear_canvas() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            pixels[i][j].set(0, 0, 0);
        }
    }
}

void canvas::resize_canvas(int w, int h) {
    width = w;
    height = h;
    pixels.resize(width);

    for (auto& column : pixels) {
        column.resize(height);
    }
}

int canvas::get_width()
{
    return width;
}

int canvas::get_height()
{
    return height;
}

void canvas::write_pixel(int x, int y, tuple c)
{
    pixels[x][y].set(c.r, c.g, c.b);
}

tuple& canvas::pixel_at(int x, int y)
{
    return pixels[x][y];
}

std::string canvas::exportPPM()
{
    // Use a stringstream to build the PPM content
    std::ostringstream ppmStream;

    // Write the PPM header
    ppmStream << "P3\n" << width << " " << height << "\n255\n";

    int counter = 0;

    // Write the RGB data
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Get the RGB values
            tuple& pixel = pixel_at(x, y);
            double r = clamp(pixel.r);
            double g = clamp(pixel.g);
            double b = clamp(pixel.b);

            // Scale to [0, 255] and convert to integers
            int red = std::round(r * 255);
            int green = std::round(g * 255);
            int blue = std::round(b * 255);

            // Write the RGB value
            // Only add trailing whitespace if pixel is not last in row or in line in the ppm
            ppmStream << red << " " << green << " " << blue << (x == width - 1 || counter + 6 >= 60 ? "" : " ");
            counter += 12;

            if(counter >= 60 && x != width - 1) {
                counter = 0;
                // add a newline to split longer lines into <70 character sublines
                ppmStream << "\n";
            }
        }
        ppmStream << "\n"; // Newline after each row
        counter = 0;
    }

    // Return the generated PPM content as a string
    return ppmStream.str();
}


