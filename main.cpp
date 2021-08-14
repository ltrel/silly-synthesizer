#include <vector>
#include <cmath>
#include "wavefile.h"
#include "synthesizer.h"
#include "utils.h"

int main(int argc, char *argv[])
{
  int sampleRate{44100};
  int numChannels{2};
  int bitsPerSample{24};

  double crotchet{0.8};

  std::vector<std::vector<double>> audioData(numChannels, std::vector<double>{});

  SynthOptions options;
  options.baseVolume = 1/6.0;
  Synthesizer synth{sampleRate, numChannels, options};

  // Notes to the first phrase of Ode to Joy
  synth.renderNote(audioData, "e4", crotchet);
  synth.renderNote(audioData, "e4", crotchet);
  synth.renderNote(audioData, "f4", crotchet);
  synth.renderNote(audioData, "g4", crotchet);
  synth.renderNote(audioData, "g4", crotchet);
  synth.renderNote(audioData, "f4", crotchet);
  synth.renderNote(audioData, "e4", crotchet);
  synth.renderNote(audioData, "d4", crotchet);
  synth.renderNote(audioData, "c4", crotchet);
  synth.renderNote(audioData, "c4", crotchet);
  synth.renderNote(audioData, "d4", crotchet);
  synth.renderNote(audioData, "e4", crotchet);
  synth.renderNote(audioData, "e4", crotchet*1.5);
  synth.renderNote(audioData, "d4", crotchet*0.5);
  synth.renderNote(audioData, "d4", crotchet*2);

  WaveFile waveFile{sampleRate, numChannels, bitsPerSample};
  waveFile.pushSamples(audioData);
  waveFile.saveToFile("output.wav");

  return 0;
}
