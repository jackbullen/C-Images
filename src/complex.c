#include "complex.h"
#include <math.h>

complex add(complex a, complex b) {
    complex c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
    return c;
}

complex sub(complex a, complex b) {
    complex c;
    c.real = a.real - b.real;
    c.imag = a.imag - b.imag;
    return c;
}

complex mul(complex a, complex b) {
    complex c;
    c.real = a.real * b.real - a.imag * b.imag;
    c.imag = a.real * b.imag + a.imag * b.real;
    return c;
}

complex div_c(complex a, complex b) {
    complex c;
    c.real = (a.real * b.real + a.imag * b.imag) / (b.real * b.real + b.imag * b.imag);
    c.imag = (a.imag * b.real - a.real * b.imag) / (b.real * b.real + b.imag * b.imag);
    return c;
}

complex exp_c(complex a, double n) {
    double r = sqrt(a.real * a.real + a.imag * a.imag);
    double theta = atan2(a.imag, a.real);

    complex c;
    c.real = pow(r, n) * cos(n * theta);
    c.imag = pow(r, n) * sin(n * theta);
    return c;
}

