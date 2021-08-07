#include "wavefile.h"

#include <math.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>

WaveFile::WaveFile(int sampleRate, int numChannels, int bitsPerSample)
{
  // Values that don't divide by 8 are tricky to work with and values above 32
  // may result in samples too large to fit into a long on certain platforms
  if (bitsPerSample % 8 != 0 || bitsPerSample < 8 || bitsPerSample > 32)
  {
    throw "bitsPerSample must be 8, 16, 24, or 32";
  }

  // Initialize the header struct
  header.sampleRate = sampleRate;
  header.numChannels = numChannels;
  header.bitsPerSample = bitsPerSample;
  int bytesPerSample{bitsPerSample / 8};
  header.byteRate = header.sampleRate * header.numChannels * bytesPerSample;
  header.blockAlign = header.numChannels * bytesPerSample;
}

void WaveFile::pushSamples(std::vector<std::vector<long>> &newAudioData)
{
  // Ensure the new audio data has the right number of channels and  and equal
  // number of samples in each channel
  if (newAudioData.size() != header.numChannels)
  {
    throw "Wrong number of channels supplied";
  }

  std::size_t const firstSize{newAudioData.front().size()};
  bool sizesEqual{std::all_of(
      newAudioData.begin(),
      newAudioData.end(),
      [firstSize](const std::vector<long> &x)
      { return x.size() == firstSize; })};
  if (!sizesEqual)
  {
    throw "Channels do not contain an equal number of samples";
  }

  // Reserve enough space for the new samples
  std::size_t newSize{rawAudioData.size() + newAudioData[0].size() *
                                                sizeof(long) *
                                                header.numChannels};
  rawAudioData.reserve(newSize);

  int bytesPerSample{header.bitsPerSample / 8};
  // Loop over number of samples
  for (std::size_t i{0}; i < newAudioData[0].size(); i++)
  {
    // Loop over number of channels
    for (std::size_t j{0}; j < newAudioData.size(); j++)
    {
      // Append the first N bytes of the long containing the sample, where N
      // is the number of bytes a sample wil occupy in the file
      char *sampleAsChar = reinterpret_cast<char *>(&newAudioData[j][i]);
      rawAudioData.insert(
          rawAudioData.end(), sampleAsChar, sampleAsChar + bytesPerSample);
    }
  }
}

void WaveFile::saveToFile(std::filesystem::path path)
{
  // Set the remaining header fields
  header.subchunk2Size = rawAudioData.size();
  header.chunkSize = HEADER_SIZE + header.subchunk2Size;

  // Write the header and audio data to the file path specified
  std::ofstream outStream{path, std::ios::binary};
  outStream.write(reinterpret_cast<char *>(&header), sizeof(header));
  outStream.write(reinterpret_cast<char *>(&rawAudioData[0]),
                  rawAudioData.size());
  outStream.close();
}
