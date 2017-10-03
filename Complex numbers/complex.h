#pragma once

class complex {

private:
  //real and imaginary components of number
  float re, im;

public:
  //constructors
  complex();
  complex(float a, float b);

  //other functions
  void printComplex();
  complex getConjugate();
  float getModule();
  float getReal();
  float getImaginary();

  //operators
  complex operator=(complex);
  complex operator+(complex z);
  complex operator-(complex z);
  complex operator*(complex z);
  complex operator/(complex z);
  bool operator==(complex z);
};
