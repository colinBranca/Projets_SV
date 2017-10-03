#pragma once

#include <stdio.h>
#include <assert.h>

#include "complex.h"

using namespace std;


int main() {
  complex x = complex(5.0f, 7.0f);
  complex y = complex(12.0f, 7.0f);

  //test print
  x.printComplex();
  y.printComplex();

  //test sum
  complex sum = x + y;
  assert(sum == complex(17.0f, 14.0f));

  //test substract
  complex sub = y - x;
  assert(sub == complex(7.0f, 0.0f));

  //test multiplication
  complex mul = x * y;
  assert(mul == complex(11.0f, 119.0f));

  //test division
  complex div = y / x;
  assert(div == complex(109.0f/74.0f, -49.0f/74.0f));

  printf("All test passed\n");



  return 0;
}
