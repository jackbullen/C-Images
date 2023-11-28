#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
	double real;
	double imag;
} complex;

complex add(complex a, complex b);
complex sub(complex a, complex b);
complex mul(complex a, complex b);
complex div_c(complex a, complex b);

complex exp_c(complex a, double n);

#endif // COMPLEX_H