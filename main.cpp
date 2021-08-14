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
  double volume{1 / 6.0};

  std::vector<std::vector<double>> audioData(numChannels, std::vector<double>{});

  Synthesizer synth{sampleRate, numChannels};
  // Notes to the first phrase of Ode to Joy
  synth.renderNote(audioData, "e4", crotchet, volume);
  synth.renderNote(audioData, "e4", crotchet, volume);
  synth.renderNote(audioData, "f4", crotchet, volume);
  synth.renderNote(audioData, "g4", crotchet, volume);
  synth.renderNote(audioData, "g4", crotchet, volume);
  synth.renderNote(audioData, "f4", crotchet, volume);
  synth.renderNote(audioData, "e4", crotchet, volume);
  synth.renderNote(audioData, "d4", crotchet, volume);
  synth.renderNote(audioData, "c4", crotchet, volume);
  synth.renderNote(audioData, "c4", crotchet, volume);
  synth.renderNote(audioData, "d4", crotchet, volume);
  synth.renderNote(audioData, "e4", crotchet, volume);
  synth.renderNote(audioData, "e4", crotchet*1.5, volume);
  synth.renderNote(audioData, "d4", crotchet*0.5, volume);
  synth.renderNote(audioData, "d4", crotchet*2, volume);

  WaveFile waveFile{sampleRate, numChannels, bitsPerSample};
  waveFile.pushSamples(audioData);
  waveFile.saveToFile("output.wav");

  return 0;
}
