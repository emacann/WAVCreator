#include "WAVCreator.h"

int 
main(int argc, char ** pp_argv)
{
    WAVCreator * wave =
        new WAVCreator(
        "gesoo.wav",        // Filename.
        44100,              // Samplerate.
        60,                 // Duration. (sec)
        INT16_MAX,          // Left amplitude.
        4000,               // Left frequency.
        0,                  // Left phase.
        INT16_MAX,          // Right amplitude.
        4000,               // Right frequency.
        0                   // Right phase.
        );
    
    wave->toFile();
    
    delete wave;
    
    return(0);
}