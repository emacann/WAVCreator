#include "WAVCreator.h"

////////////////////////////////////////////////////////////////////////////////
// Constructors

WAVCreator::WAVCreator()
{
    fileName      = NULL;
    data          = NULL;

    samples       = 0;

    bitsPerSample = 0;
    numChannels   = 0;
    sampleRate    = 0;
}

WAVCreator::WAVCreator(
    char* fileName, uint32_t samples, uint32_t sampleRate,
    uint16_t numChannels, uint16_t bitsPerSample)
{
    size_t fileLenght = strlen(fileName) + 1;
    this->fileName = new char[fileLenght];
    memcpy(this->fileName, fileName, fileLenght);

    this->samples = samples;

    this->sampleRate = sampleRate;
    this->numChannels = numChannels;
    this->bitsPerSample = bitsPerSample;

    this->data = new int16_t[numChannels * samples];

    for (size_t i = 0; i < numChannels * samples; i++)
    {
        data[i] = 0;
    }
}

WAVCreator::WAVCreator(
    char* fileName, int16_t* data, uint32_t samples, uint32_t sampleRate,
    uint16_t numChannels, uint16_t bitsPerSample) 
: WAVCreator(fileName, samples, sampleRate, numChannels, bitsPerSample)
{
    memcpy(this->data, data, samples * bitsPerSample / 8 * numChannels);
}

WAVCreator::WAVCreator(
    char* fileName, uint32_t samples, int16_t* waveForm, size_t waveSamples,
    uint32_t sampleRate, uint16_t numChannels, uint16_t bitsPerSample) 
: WAVCreator(fileName, samples, sampleRate, numChannels, bitsPerSample)
{
    fillData(waveForm, waveSamples);
}

WAVCreator::WAVCreator(WAVCreator& X)
{
    WAVCreator::~WAVCreator();

    WAVCreator::WAVCreator(
        X.fileName, X.data, X.samples, X.sampleRate, 
        X.numChannels, X.bitsPerSample
        );
}

WAVCreator& 
WAVCreator::operator=(WAVCreator& X)
{
    WAVCreator::WAVCreator(X);
    return(X);
}

WAVCreator::~WAVCreator()
{
    if (fileName != NULL) 
    {
        delete fileName;
        fileName = NULL;
    }
    
    if (data != NULL) 
    {
        delete data;
        data = NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Functions

void 
WAVCreator::createHeader(char* header)
{
    uint32_t subChunk1Size  = 16;       // 16 for PCM.
    uint16_t audioFormat    = 1;        //  1 for PCM.

    uint32_t byteRate       = sampleRate * numChannels * bitsPerSample / 8;
    uint16_t blockAlign     = numChannels * bitsPerSample / 8;
    uint32_t subChunk2Size  = samples * bitsPerSample / 8;

    uint32_t chunkSize      = 4 + (8 + subChunk1Size) + (8 + subChunk2Size);
    
    /* ChunkID - "RIFF"                 BIG     (4 Bytes) */
    header[0]   = 0x52;                         // 'R'
    header[1]   = 0x49;                         // 'I'
    header[2]   = 0x46;                         // 'F'
    header[3]   = 0x46;                         // 'F'
    /* ChunkSize                        LITTLE  (4 Bytes) */
    header[7]   = (char)(chunkSize >> 24)       & 0x000000FF;
    header[6]   = (char)(chunkSize >> 16)       & 0x000000FF;
    header[5]   = (char)(chunkSize >> 8)        & 0x000000FF;
    header[4]   = (char)(chunkSize)             & 0x000000FF;
    /* Format - "WAVE"                  BIG     (4 Bytes) */
    header[8]   = 0x57;                         // 'W'
    header[9]   = 0x41;                         // 'A'
    header[10]  = 0x56;                         // 'V'
    header[11]  = 0x45;                         // 'E'
    /* Subchunk1ID - "fmt "             BIG     (4 Bytes) */
    header[12]  = 0x66;                         // 'f'
    header[13]  = 0x6d;                         // 'm'
    header[14]  = 0x74;                         // 't'
    header[15]  = 0x20;                         // ' '
    /* Subchunk1Size                    LITTLE  (4 Bytes) */
    header[19]  = (char)(subChunk1Size >> 24)   & 0x000000FF;
    header[18]  = (char)(subChunk1Size >> 16)   & 0x000000FF;
    header[17]  = (char)(subChunk1Size >> 8)    & 0x000000FF;
    header[16]  = (char)(subChunk1Size)         & 0x000000FF;
    /* AudioFormat                      LITTLE  (2 Bytes) */
    header[21]  = (char)(audioFormat >> 8)      & 0x000000FF;
    header[20]  = (char)(audioFormat)           & 0x000000FF;
    /* NumChannels                      LITTLE  (2 Bytes) */
    header[23]  = (char)(numChannels >> 8)      & 0x000000FF;
    header[22]  = (char)(numChannels)           & 0x000000FF;
    /* SampleRate                       LITTLE  (4 Bytes) */
    header[27]  = (char)(sampleRate >> 24)      & 0x000000FF;
    header[26]  = (char)(sampleRate >> 16)      & 0x000000FF;
    header[25]  = (char)(sampleRate >> 8)       & 0x000000FF;
    header[24]  = (char)(sampleRate)            & 0x000000FF;
    /* ByteRate                         LITTLE  (4 Bytes) */
    header[31]  = (char)(byteRate >> 24)        & 0x000000FF;
    header[30]  = (char)(byteRate >> 16)        & 0x000000FF;
    header[29]  = (char)(byteRate >> 8)         & 0x000000FF;
    header[28]  = (char)(byteRate)              & 0x000000FF;
    /* BlockAlign                       LITTLE  (2 Bytes) */
    header[33]  = (char)(blockAlign >> 8)       & 0x000000FF;
    header[32]  = (char)(blockAlign)            & 0x000000FF;
    /* BitsPerSample                    LITTLE  (2 Bytes) */
    header[35]  = (char)(bitsPerSample >> 8)    & 0x000000FF;
    header[34]  = (char)(bitsPerSample)         & 0x000000FF;
    /* Subchunk2ID - "data"             BIG     (4 Bytes) */
    header[36]  = 0x64;                         // 'd'
    header[37]  = 0x61;                         // 'a'
    header[38]  = 0x74;                         // 't'
    header[39]  = 0x61;                         // 'a'
    /* Subchunk2Size                    LITTLE  (4 Bytes) */
    header[43]  = (char)(subChunk2Size >> 24)   & 0x000000FF;
    header[42]  = (char)(subChunk2Size >> 16)   & 0x000000FF;
    header[41]  = (char)(subChunk2Size >> 8)    & 0x000000FF;
    header[40]  = (char)(subChunk2Size)         & 0x000000FF;
}

bool 
WAVCreator::toFile()
{
    ofstream file;
    
    file.open(fileName, fstream::out | fstream::binary);
    
    if (!file.good()) 
    {
        cout << "Unable to open file for writing!" << endl << flush;
        return (false);
    }
    
    char* header = new char[44];
    createHeader(header);
    
    file.write(header, 44);
    file.write((char*)this->data, samples * bitsPerSample / 8 * numChannels);
    
    file.flush();
    file.close();
    
    delete header;
    
    return(true);
}

void
WAVCreator::fillData(int16_t* waveForm, size_t waveSamples)
{
    size_t cycles = (this->samples * this->numChannels) / waveSamples;
    size_t rest   = (this->samples * this->numChannels) % waveSamples;

    size_t i = 0;

    for (size_t n = 0; n < cycles; n++)
    {
        for (size_t j = 0; j < waveSamples; j++)
        {
            this->data[i] = waveForm[j];
            i++;
        }
    }

    for (size_t j = 0; j < rest; j++)
    {
        this->data[i] = waveForm[j];
        i++;
    }
}