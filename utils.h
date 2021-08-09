#pragma once
#include <string>

double mapRange(double input, double inMin, double inMax, double outMin, double outMax);
double hzToSinScale(double frequency, int sampleRate);
double noteToFreq(std::string const &note);
