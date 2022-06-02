#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <math.h>

  int addition(int a, int b);
  int subtraction(int a, int b);
  int multiplication(int a, int b);
  int division(int a, int b);
  double calc_exp(double a,double b);

#ifdef __cplusplus
}
#endif

#endif // _CALCULATOR_H_