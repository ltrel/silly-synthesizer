#pragma once
#include <vector>

double mapRange(double input, double inMin, double inMax, double outMin, double outMax);

// Shorthand type names for vectors of samples, channels, and voices
using samples_vec = std::vector<double>;
using channels_vec = std::vector<samples_vec>; 
using voices_vec = std::vector<channels_vec>; 
