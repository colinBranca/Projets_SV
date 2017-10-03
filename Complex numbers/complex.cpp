#pragma once

#include <sstream>
#include <iostream>

using namespace std;

#include "complex.h"

//default constructor
complex::complex() {
  re = 0.0f;
  im = 0.0f;
}

//constructor
complex::complex(float a, float b) {
  re = a;
  im = b;
}

//assignment
complex complex::operator=(complex z) {
  return complex(z.re, z.im);
}

//print complex number
void complex::printComplex() {
  std::cout << re << " + " << im << "i" <<'\n';
}

//add two complex numbers
complex complex::operator+(complex z) {
  complex sum;
  sum.re = this->re + z.re;
  sum.im = this->im + z.im;
  return sum;
}

//substract two complex numbers
complex complex::operator-(complex z) {
  complex sub;
  sub.re = this->re - z.re;
  sub.im = this->im - z.im;
  return sub;
}

//multiply two complex numbers
complex complex::operator*(complex z) {
  complex mul;
  mul.re = this->re * z.re - this->im * z.im;
  mul.im = this->re * z.im + this->im * z.re;
  return mul;
}

//divide two complex numbers
complex complex::operator/(complex z) {
  complex div;
  complex zConjugate = z.getConjugate();
  complex up;
  up.re = this->re * zConjugate.re;
  up.im = this->im * zConjugate.im;
  //complex up = this * z.getConjugate();
  float down = z.getModule();
  div.re = up.re / down;
  div.im = up.im / down;
  return div;
}

//equality test
bool complex::operator==(complex z) {
  return (this->re == z.re) && (this->im == z.im);
}

//return conjugate of complex number
complex complex::getConjugate() {
  complex conjugate = complex(this->re, - this->im);
  return conjugate;
}

//return module of complex number
float complex::getModule() {
  return this->re * this->re + this->im * this->im;
}

//return real part of complex number
float complex::getReal() {
  return this->re;
}

//return imaginary part of complex number
float complex::getImaginary() {
  return this->im;
}
