#include "complex.h"
#include "graphics.h"
#include <stdio.h>
#include <math.h>

int main() {
    // Demonstrating complex number operations
    complex a = {1, 2};
    complex b = {3, 4};

    complex c = add(a, b);
    printf("add: %f + %fi\n", c.real, c.imag);

    c = sub(a, b);
    printf("sub: %f + %fi\n", c.real, c.imag);

    c = mul(a,b);
    printf("mul: %f + %fi\n", c.real, c.imag);

    c = div_c(a, b); // Updated from div to div_complex
    printf("div: %f + %fi\n", c.real, c.imag);

    c = exp_c(a, 2);
    printf("exp: %f + %fi\n", c.real, c.imag);

    // Demonstrating graphics module
    int width = 800;
    int height = 600;

    Image *img = create_image(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Scale and shift x and y to create more interesting patterns
            double scaledX = 4.0 * (x - width / 2.0) / width;
            double scaledY = 4.0 * (y - height / 2.0) / height;

            // Generate a complex number based on modified x and y values
            complex z = {scaledX, scaledY};

            // Apply a transformation to z for more dramatic visual effects
            complex transformedZ;
            transformedZ.real = cos(z.real) * cosh(z.imag);
            transformedZ.imag = sin(z.real) * sinh(z.imag);

            // Map the transformed complex number to the pixel
            map_complex_to_pixel(img, transformedZ, x, y);
        }
    }



    save_image(img, "output.bmp");

    free_image(img);

    return 0;
}