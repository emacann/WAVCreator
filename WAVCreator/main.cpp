#include "WAVCreator.h"

#define WAVE_SZ     100
#define SAMPLES     1000
#define FREQ        44100
#define CHANNELS    1

int 
main(int argc, char ** pp_argv)
{
    WAVCreator * wave;
    
    int16_t * h = new int16_t[WAVE_SZ];

    size_t slope = (UINT16_MAX) / (WAVE_SZ);

    for (size_t i = 0; i < WAVE_SZ; i++)
    {
        h[i] = slope * i - (INT16_MAX - 1);
    }

    wave = new WAVCreator(
        "PLS.wav",
        SAMPLES,
        h,
        WAVE_SZ,
        FREQ,
        CHANNELS
        );

    wave->toFile();
    
    delete wave;
    
    return(0);
}