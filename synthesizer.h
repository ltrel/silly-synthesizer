#pragma once
#include <vector>
#include <string>

class Synthesizer
{
private:
  int sampleRate;
  int numChannels;

  double noteToFreq(std::string const &note);
  double hzToSinXScale(double frequency);

public:
  Synthesizer(int sampleRate, int numChannels);
  void renderNote(std::vector<std::vector<double>> &dest, std::string note,
                  double seconds, double volume);

  int getSampleRate() { return sampleRate; }
  int getNumChannels() { return numChannels; }
};
