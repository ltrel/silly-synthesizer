#pragma once
#include <cstdint>
#include <vector>
#include <filesystem>

class WaveFile
{
private:
  static const int HEADER_SIZE{36};
#pragma pack(push, 1)
  struct WaveHeader
  {
    // RIFF Header
    char chunkId[4]{'R', 'I', 'F', 'F'};
    std::uint32_t chunkSize;
    char format[4]{'W', 'A', 'V', 'E'};

    // Format subchunk
    char subchunk1ID[4]{'f', 'm', 't', ' '};
    std::uint32_t subchunk1Size{16};
    std::uint16_t audioFormat{1};
    std::uint16_t numChannels;
    std::uint32_t sampleRate;
    std::uint32_t byteRate;
    std::uint16_t blockAlign;
    std::uint16_t bitsPerSample{16};

    // Start of data subchunk
    char subchunk2ID[4]{'d', 'a', 't', 'a'};
    std::uint32_t subchunk2Size;
  } header;
#pragma pack(pop)

  long minAmplitude;
  long maxAmplitude;
  std::vector<char> rawAudioData;

  long formatSample(double input);

public:
  WaveFile(int sampleRate, int numChannels, int bitsPerSample);
  int getSampleRate() { return header.sampleRate; }
  int getNumChannels() { return header.numChannels; }
  int getBitsPerSample() { return header.bitsPerSample; }
  void pushSamples(std::vector<std::vector<double>> &newAudioData);
  void saveToFile(std::filesystem::path path);
};
