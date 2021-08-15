#include "synthesizer.h"
#include "utils.h"
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <cmath>
#include <algorithm>

Synthesizer::Synthesizer(int sampleRate, int numChannels, SynthOptions options)
{
  this->sampleRate = sampleRate;
  this->numChannels = numChannels;
  synthOptions = options;
}

void Synthesizer::renderNote(std::vector<std::vector<double>> &dest,
                             std::string note, double seconds, double volume)
{
  if (dest.size() != static_cast<std::size_t>(numChannels))
  {
    throw "Destination contains wrong number of channels";
  }

  long numSamples{std::lround(sampleRate * seconds)};

  double realVolume{synthOptions.baseVolume * volume};
  double hz{noteToFreq(note)};
  double scale{hzToSinXScale(hz)};

  for (long i{0}; i < numSamples; i++)
  {
    // Apply attack and release modifier to note
    long reverseIndex{numSamples - 1 - i};
    double attack{std::min(i / (sampleRate * synthOptions.attackSeconds), 1.0)};
    double release{std::min(reverseIndex / (sampleRate * synthOptions.releaseSeconds), 1.0)};

    double sample{sin(i * scale) * realVolume * attack * release};
    // Add same sample to all channels for now
    for (auto &channel : dest)
    {
      channel.push_back(sample);
    }
  }
}

std::vector<std::vector<double>> Synthesizer::combineVoices(std::vector<std::vector<std::vector<double>>> &voices)
{
  // Check how many samples long each voice is and find the maximum
  std::vector<std::size_t> voiceLengths{};
  for (auto &voice : voices)
  {
    voiceLengths.push_back(voice[0].size());
  }
  std::size_t numSamples{*std::max_element(voiceLengths.begin(), voiceLengths.end())};

  // Create variable to hold output with same length as longest voice
  std::vector<std::vector<double>> result(numChannels, std::vector<double>(numSamples, 0.0));

  for (auto &voice : voices)
  {
    for (int i{0}; i < numChannels; i++)
    {
      // Sum the samples on this channel of the current voice with the samples
      // in the corresponding channel of the output
      std::vector<double> &inChannel = voice[i];
      std::vector<double> &outChannel = result[i];
      std::transform(inChannel.begin(), inChannel.end(), outChannel.begin(),
                     outChannel.begin(), std::plus<double>());
    }
  }
  return result;
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
  return synthOptions.tuningPitch * std::pow(2.0, semitones / 12.0);
}
