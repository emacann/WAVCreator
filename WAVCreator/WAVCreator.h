#ifndef __WAV_CREATOR_H__
#define __WAV_CREATOR_H__

#include "STDHeader.h"

#include <iostream>
#include <fstream>

#define PI 3.14159265

using namespace std;

class WAVCreator
{
private:
    char    * fileName;
    int16_t * data;

    uint16_t  bitsPerSample;
    uint16_t  numChannels;
    uint32_t  sampleRate;
    uint32_t  samples;
            
    void createHeader(char* header);
    
public:
    WAVCreator();

    WAVCreator(
        char* fileName, uint32_t samples, uint32_t sampleRate,
        uint16_t numChannels, uint16_t bitsPerSample = 16
        );

    WAVCreator(
        char* fileName, int16_t* data, uint32_t samples, uint32_t sampleRate,
        uint16_t numChannels, uint16_t bitsPerSample = 16
        );

    WAVCreator(
        char* fileName, uint32_t samples, int16_t* waveForm, size_t waveSamples,
        uint32_t sampleRate, uint16_t numChannels, uint16_t bitsPerSample = 16
        );
    
    WAVCreator(WAVCreator& X);
    WAVCreator& operator=(WAVCreator& X);
    
    virtual ~WAVCreator();
    
    bool toFile();
    void fillData(int16_t* waveForm, size_t waveSamples);
};

#endif // __WAV_CREATOR_H__