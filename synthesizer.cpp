#include "synthesizer.h"
#include "utils.h"
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <cmath>

Synthesizer::Synthesizer(int sampleRate, int numChannels)
{
  this->sampleRate = sampleRate;
  this->numChannels = numChannels;
}

void Synthesizer::renderNote(std::vector<std::vector<double>> &dest,
                             std::string note, double seconds, double volume)
{
  if (dest.size() != static_cast<std::size_t>(numChannels))
  {
    throw "Destination contains wrong number of channels";
  }

  long numSamples{std::lround(sampleRate * seconds)};

  double hz{noteToFreq(note)};
  double scale{hzToSinXScale(hz)};
  double attackSeconds{0.01};
  double releaseSeconds{0.01};

  for (long i{0}; i < numSamples; i++)
  {
    // Apply attack and release modifier to note
    long reverseIndex{numSamples - 1 - i};
    double attack{std::min(i / (sampleRate * attackSeconds), 1.0)};
    double release{std::min(reverseIndex / (sampleRate * releaseSeconds), 1.0)};

    double sample{sin(i * scale) * volume * attack * release};
    // Add same sample to all channels for now
    for (auto &channel : dest)
    {
      channel.push_back(sample);
    }
  }
}

double Synthesizer::hzToSinXScale(double frequency)
{
  return (frequency * 2 * M_PI) / sampleRate;
}

double Synthesizer::noteToFreq(std::string const &note)
{
  static const std::map<char, int> letterSemitonesMap{
      {'c', 0},
      {'d', 2},
      {'e', 4},
      {'f', 5},
      {'g', 7},
      {'a', 9},
      {'b', 11}};

  if (note.size() < 2)
  {
    throw "Note must contain at least two characters: a letter and a number";
  }

  // First character is always the letter
  char letter{std::tolower(note[0], std::locale())};
  // Last character is always the octave number
  int octave{std::stoi(std::string(1, note.back()))};

  // Sum the accidentals in the middle of the string
  int accidentalSum{0};
  for (std::size_t i{1}; i < note.size() - 1; i++)
  {
    char c = std::tolower(note[i], std::locale());
    if (c == '#')
      accidentalSum += 1;
    else if (c == 'b')
      accidentalSum -= 1;
    else
      throw "Invalid accidental";
  }

  // Number of semitones relative to C0
  int semitones{letterSemitonesMap.at(letter) + accidentalSum + octave * 12};
  // Offset by 57 so the number is relative to A4 instead
  semitones -= 57;

  // Calculate and return the frequency in Hz
  return 440.0 * std::pow(2.0, semitones / 12.0);
}
