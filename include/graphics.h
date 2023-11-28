#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "complex.h"

typedef struct {
    int width;
    int height;
    unsigned char *data;
} Image;

Image* create_image(int width, int height);
void free_image(Image *image);
void map_complex_to_pixel(Image *image, complex z, int x, int y);
void color_pixel(Image *image, int x, int y, unsigned char r, unsigned char g, unsigned char b);
void save_image(Image *img, const char *filename);

#endif // GRAPHICS_H