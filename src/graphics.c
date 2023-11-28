#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

Image* create_image(int width, int height) {
    Image *img = malloc(sizeof(Image));
    img->width = width;
    img->height = height;
    img->data = malloc(width * height * 3);
    return img;
}

void free_image(Image *img) {
    free(img->data);
    free(img);
}

#include "graphics.h"
#include <math.h>

void map_complex_to_pixel(Image *img, complex z, int x, int y) {
    // Example implementation: Color based on magnitude and phase

    // Calculate the magnitude and phase (angle) of the complex number
    double magnitude = sqrt(z.real * z.real + z.imag * z.imag);
    double phase = atan2(z.imag, z.real);

    // Normalize magnitude and phase to a range suitable for color mapping
    // Here, we're just using a simple method for demonstration purposes
    // You may want to scale these values based on the specific range of your complex function outputs
    double normalizedMagnitude = fmin(magnitude, 1.0); // Normalize to [0, 1]
    double normalizedPhase = (phase + M_PI) / (2.0 * M_PI); // Normalize to [0, 1]

    // Map the normalized magnitude and phase to RGB values
    // This is a simple mapping: you can use more sophisticated color mapping techniques
    unsigned char r = (unsigned char)(255 * normalizedMagnitude);
    unsigned char g = (unsigned char)(255 * normalizedPhase);
    unsigned char b = 255 - r;

    // Color the pixel at (x, y)
    color_pixel(img, x, y, r, g, b);
}


void color_pixel(Image *img, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
        int index = (y * img->width + x) * 3;
        img->data[index] = r;
        img->data[index + 1] = g;
        img->data[index + 2] = b;
    }
}

// Helper function to write a 4-byte integer in little-endian format
static void write_int(FILE *fp, int32_t value) {
    fputc(value & 0xFF, fp);
    fputc((value >> 8) & 0xFF, fp);
    fputc((value >> 16) & 0xFF, fp);
    fputc((value >> 24) & 0xFF, fp);
}

void save_image(Image *img, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error opening file for writing");
        return;
    }

    int32_t width = img->width;
    int32_t height = img->height;
    int32_t row_size = (width * 3 + 3) & ~3; // Each row is padded to a multiple of 4 bytes
    int32_t data_size = row_size * height;
    int32_t file_size = 54 + data_size; // 54-byte header + pixel data

    // Write BMP header
    fputs("BM", fp);                  // Signature
    write_int(fp, file_size);         // File size
    write_int(fp, 0);                 // Reserved
    write_int(fp, 54);                // Offset to pixel data
    write_int(fp, 40);                // Header size
    write_int(fp, width);             // Image width
    write_int(fp, height);            // Image height
    fputc(1, fp); fputc(0, fp);       // Number of color planes (must be 1)
    fputc(24, fp); fputc(0, fp);      // Bits per pixel
    write_int(fp, 0);                 // Compression (none)
    write_int(fp, data_size);         // Size of pixel data
    write_int(fp, 2835); write_int(fp, 2835); // Horizontal/Vertical resolution (pixels/meter)
    write_int(fp, 0);                 // Number of colors in the color palette (default)
    write_int(fp, 0);                 // Number of important colors used

    // Write pixel data (bottom-up)
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * 3;
            fputc(img->data[index + 2], fp); // Blue
            fputc(img->data[index + 1], fp); // Green
            fputc(img->data[index], fp);     // Red
        }
        // Padding for row
        for (int pad = width * 3; pad < row_size; ++pad) {
            fputc(0, fp);
        }
    }

    fclose(fp);
}