#include <vector>
#include <cmath>
#include "wavefile.h"
#include "synthesizer.h"
#include "utils.h"

voices_vec bachPrelude(Synthesizer &synth);

int main(int argc, char *argv[])
{
  int sampleRate{44100};
  int numChannels{1};
  int bitsPerSample{16};

  SynthOptions options;
  options.baseVolume = 1 / 6.0;
  Synthesizer synth{sampleRate, numChannels, options};

  auto voices{bachPrelude(synth)};
  auto combined{synth.combineVoices(voices)};

  WaveFile waveFile{sampleRate, numChannels, bitsPerSample};
  waveFile.pushSamples(combined);
  waveFile.saveToFile("output.wav");

  return 0;
}

voices_vec bachPrelude(Synthesizer &synth)
{
  // Create a voice for each hand and get references to them
  voices_vec voices(2, channels_vec(synth.getNumChannels(), samples_vec{}));

  auto &v1{voices[0]};
  auto &v2{voices[1]};

  // Get length in seconds of a semiquaver
  double tempo{120.0};
  double crotchet{60.0 / tempo};
  double semiquaver{crotchet / 4};

  // Notes to Bach's Prelude in C Minor, BWV 847
  // Bar 1
  for (int i{0}; i < 2; ++i)
  {
    synth.renderNote(v1, "c5", semiquaver);
    synth.renderNote(v1, "eb4", semiquaver);
    synth.renderNote(v1, "d4", semiquaver);
    synth.renderNote(v1, "eb4", semiquaver);
    synth.renderNote(v1, "c4", semiquaver);
    synth.renderNote(v1, "eb4", semiquaver);
    synth.renderNote(v1, "d4", semiquaver);
    synth.renderNote(v1, "eb4", semiquaver);

    synth.renderNote(v2, "c3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "f3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "eb3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "f3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
  }
  // Bar 2
  for (int i{0}; i < 2; ++i)
  {
    synth.renderNote(v1, "ab4", semiquaver);
    synth.renderNote(v1, "f4", semiquaver);
    synth.renderNote(v1, "e4", semiquaver);
    synth.renderNote(v1, "f4", semiquaver);
    synth.renderNote(v1, "c4", semiquaver);
    synth.renderNote(v1, "f4", semiquaver);
    synth.renderNote(v1, "e4", semiquaver);
    synth.renderNote(v1, "f4", semiquaver);

    synth.renderNote(v2, "c3", semiquaver);
    synth.renderNote(v2, "ab3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "ab3", semiquaver);
    synth.renderNote(v2, "f3", semiquaver);
    synth.renderNote(v2, "ab3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "ab3", semiquaver);
  }
  // Bar 3
  for (int i{0}; i < 2; ++i)
  {
    synth.renderNote(v1, "b4", semiquaver);
    synth.renderNote(v1, "f4", semiquaver);
    synth.renderNote(v1, "eb4", semiquaver);
    synth.renderNote(v1, "f4", semiquaver);
    synth.renderNote(v1, "d4", semiquaver);
    synth.renderNote(v1, "f4", semiquaver);
    synth.renderNote(v1, "eb4", semiquaver);
    synth.renderNote(v1, "f4", semiquaver);

    synth.renderNote(v2, "c3", semiquaver);
    synth.renderNote(v2, "ab3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "ab3", semiquaver);
    synth.renderNote(v2, "f3", semiquaver);
    synth.renderNote(v2, "ab3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "ab3", semiquaver);
  }
  // Bar 4
  for (int i{0}; i < 2; ++i)
  {
    synth.renderNote(v1, "c5", semiquaver);
    synth.renderNote(v1, "g4", semiquaver);
    synth.renderNote(v1, "f4", semiquaver);
    synth.renderNote(v1, "g4", semiquaver);
    synth.renderNote(v1, "eb4", semiquaver);
    synth.renderNote(v1, "g4", semiquaver);
    synth.renderNote(v1, "f4", semiquaver);
    synth.renderNote(v1, "g4", semiquaver);

    synth.renderNote(v2, "c3", semiquaver);
    synth.renderNote(v2, "eb3", semiquaver);
    synth.renderNote(v2, "d3", semiquaver);
    synth.renderNote(v2, "eb3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "eb3", semiquaver);
    synth.renderNote(v2, "d3", semiquaver);
    synth.renderNote(v2, "eb3", semiquaver);
  }
  // Bar 5
  for (int i{0}; i < 2; ++i)
  {
    synth.renderNote(v1, "eb5", semiquaver);
    synth.renderNote(v1, "ab4", semiquaver);
    synth.renderNote(v1, "g4", semiquaver);
    synth.renderNote(v1, "ab4", semiquaver);
    synth.renderNote(v1, "eb4", semiquaver);
    synth.renderNote(v1, "ab4", semiquaver);
    synth.renderNote(v1, "g4", semiquaver);
    synth.renderNote(v1, "ab4", semiquaver);

    synth.renderNote(v2, "c3", semiquaver);
    synth.renderNote(v2, "c4", semiquaver);
    synth.renderNote(v2, "bb3", semiquaver);
    synth.renderNote(v2, "c4", semiquaver);
    synth.renderNote(v2, "ab3", semiquaver);
    synth.renderNote(v2, "c4", semiquaver);
    synth.renderNote(v2, "bb3", semiquaver);
    synth.renderNote(v2, "c4", semiquaver);
  }
  // Bar 6
  for (int i{0}; i < 2; ++i)
  {
    synth.renderNote(v1, "d5", semiquaver);
    synth.renderNote(v1, "f#4", semiquaver);
    synth.renderNote(v1, "e4", semiquaver);
    synth.renderNote(v1, "f#4", semiquaver);
    synth.renderNote(v1, "d4", semiquaver);
    synth.renderNote(v1, "f#4", semiquaver);
    synth.renderNote(v1, "e4", semiquaver);
    synth.renderNote(v1, "f#4", semiquaver);

    synth.renderNote(v2, "c3", semiquaver);
    synth.renderNote(v2, "a3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "a3", semiquaver);
    synth.renderNote(v2, "f#3", semiquaver);
    synth.renderNote(v2, "a3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "a3", semiquaver);
  }
  // Bar 7
  for (int i{0}; i < 2; ++i)
  {
    synth.renderNote(v1, "d5", semiquaver);
    synth.renderNote(v1, "g4", semiquaver);
    synth.renderNote(v1, "f#4", semiquaver);
    synth.renderNote(v1, "g4", semiquaver);
    synth.renderNote(v1, "d4", semiquaver);
    synth.renderNote(v1, "g4", semiquaver);
    synth.renderNote(v1, "f#4", semiquaver);
    synth.renderNote(v1, "g4", semiquaver);

    synth.renderNote(v2, "bb2", semiquaver);
    synth.renderNote(v2, "bb3", semiquaver);
    synth.renderNote(v2, "a3", semiquaver);
    synth.renderNote(v2, "bb3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "bb3", semiquaver);
    synth.renderNote(v2, "a3", semiquaver);
    synth.renderNote(v2, "bb3", semiquaver);
  }
  // Bar 8
  for (int i{0}; i < 2; ++i)
  {
    synth.renderNote(v1, "c5", semiquaver);
    synth.renderNote(v1, "e4", semiquaver);
    synth.renderNote(v1, "d4", semiquaver);
    synth.renderNote(v1, "e4", semiquaver);
    synth.renderNote(v1, "c4", semiquaver);
    synth.renderNote(v1, "e4", semiquaver);
    synth.renderNote(v1, "d4", semiquaver);
    synth.renderNote(v1, "e4", semiquaver);

    synth.renderNote(v2, "bb2", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "f3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "e3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
    synth.renderNote(v2, "f3", semiquaver);
    synth.renderNote(v2, "g3", semiquaver);
  }

  return voices;
}
