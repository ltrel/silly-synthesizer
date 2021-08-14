#include "utils.h"

double mapRange(double input, double inMin, double inMax, double outMin, double outMax)
{
  return (input - inMin) * ((outMax - outMin) / (inMax - inMin)) + outMin;
}
