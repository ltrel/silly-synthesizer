#include <cmath>
#include <string>
#include <map>
#include <locale>
#include "utils.h"

double mapRange(double input, double inMin, double inMax, double outMin, double outMax)
{
  return (input - inMin) * ((outMax - outMin) / (inMax - inMin)) + outMin;
}

double hzToSinScale(double frequency, int sampleRate)
{
  return (frequency * 2 * M_PI) / sampleRate;
}

int noteToSemitones(std::string const &note)
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

  return semitones;
}

double noteToFreq(std::string const &note)
{
  int semitones = noteToSemitones(note);
  return 440.0 * std::pow(2.0, semitones / 12.0);
}
