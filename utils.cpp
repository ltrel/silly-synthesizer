#include "utils.h"

#include <math.h>

double mapRange(double input, double inMin, double inMax, double outMin, double outMax)
{
  return (input - inMin) * ((outMax - outMin) / (inMax - inMin)) + outMin;
}

double hzToSinScale(double frequency, int sampleRate)
{
  return (frequency * 2 * M_PI) / sampleRate;
}
