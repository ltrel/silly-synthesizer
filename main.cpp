#include <vector>
#include <math.h>
#include "wavefile.h"

double mapRange(double input, double inMin, double inMax, double outMin, double outMax)
{
  return (input - inMin) * ((outMax - outMin) / (inMax - inMin)) + outMin;
}

double hzToSinScale(double frequency, int sampleRate)
{
  return (frequency * 2 * M_PI) / sampleRate;
}

int main(int argc, char *argv[])
{
  int sampleRate{44100};
  int numChannels{2};
  int bitsPerSample{24};

  int seconds{5};
  double volume{1 / 6.0};
  long numSamples{seconds * sampleRate};
  std::vector<std::vector<long>> audioData(numChannels, std::vector<long>(numSamples));

  // 220Hz in left channel
  double scale{hzToSinScale(220, sampleRate)};
  for (int i{0}; i < numSamples; i++)
  {
    double sample{sin(i * scale) * volume};
    audioData[0][i] = floor(mapRange(sample, -1.0, 1.0, -8388608, 8388607));
  }

  // 275Hz in right channel
  scale = hzToSinScale(275, sampleRate);
  for (int i{0}; i < numSamples; i++)
  {
    double sample{sin(i * scale) * volume};
    audioData[1][i] = floor(mapRange(sample, -1.0, 1.0, -8388608, 8388607));
  }

  WaveFile waveFile{sampleRate, numChannels, bitsPerSample};
  waveFile.pushSamples(audioData);
  waveFile.saveToFile("output.wav");

  return 0;
}
