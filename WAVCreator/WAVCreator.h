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
    
    uint32_t sampleRate;
    uint16_t duration;
    
    int16_t lAmp;
    double  lFreq;
    double  lPhase;
    
    int16_t rAmp;
    double  rFreq;
    double  rPhase;
    
    void createHeader(
        char* header, uint32_t sampleRate, uint16_t duration,
        uint16_t numChannels = 2, uint16_t bitsPerSample = 16
        );
    
public:
    WAVCreator();
    
    WAVCreator(
        char* fileName, uint32_t sampleRate, uint16_t duration,
        int16_t lAmp, double lFreq, double lPhase,
        int16_t rAmp, double rFreq, double rPhase
        );
    
    WAVCreator(WAVCreator& X);
    
    WAVCreator& operator=(WAVCreator& X);
    
    virtual ~WAVCreator();
    
    bool toFile();
};

#endif // __WAV_CREATOR_H__