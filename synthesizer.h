#pragma once
#include <vector>
#include <string>
#include "utils.h"

struct SynthOptions
{
  double baseVolume{1.0};
  double tuningPitch{440.0};
  double attackSeconds{0.01};
  double releaseSeconds{0.01};
};

class Synthesizer
{
private:
  int sampleRate;
  int numChannels;
  SynthOptions synthOptions{SynthOptions{}};

  double noteToFreq(std::string const &note);
  double hzToSinXScale(double frequency);

public:
  Synthesizer(int sampleRate, int numChannels, SynthOptions options = SynthOptions{});
  void renderNote(channels_vec &dest, std::string note,
                  double seconds, double volume = 1.0);
  void renderRest(channels_vec &dest, double seconds);

  channels_vec combineVoices(voices_vec &voices);

  int getSampleRate() { return sampleRate; }
  int getNumChannels() { return numChannels; }
  SynthOptions getOptions() { return synthOptions; }
  void setOptions(SynthOptions options) { this->synthOptions = options; }
};
