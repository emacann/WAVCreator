#include "WAVCreator.h"

WAVCreator::WAVCreator()
{
    fileName = NULL;
    data = NULL;
    
    sampleRate  = 0;
    duration    = 0;
    
    lAmp    = 0;    rAmp    = 0;
    lFreq   = .0;   rFreq   = .0;
    lPhase  = .0;   rPhase  = .0;
}

WAVCreator::WAVCreator(
    char* fileName, uint32_t sampleRate, uint16_t duration,
    int16_t lAmp, double lFreq, double lPhase,
    int16_t rAmp, double rFreq, double rPhase)
{
    int fileLenght = strlen(fileName) + 1;
    this->fileName = new char[fileLenght];
    memcpy(this->fileName, fileName, fileLenght);
    
    this->sampleRate = sampleRate;
    this->duration = duration;
    
    this->lAmp   = lAmp;        this->rAmp   = rAmp;
    this->lFreq  = lFreq;       this->rFreq  = rFreq;
    this->lPhase = lPhase;      this->rPhase = rPhase;
    
    this->data = new int16_t[2 * sampleRate * duration];
    for (size_t i = 0; i < 2 * sampleRate * duration - 1; i += 2)
    {
        double lAngle = PI * lFreq * ((double)i / (double)sampleRate) + lPhase;
        int16_t lData = (int16_t)(lAmp * cos(lAngle));
        double rAngle = PI * rFreq * ((double)i / (double)sampleRate) + rPhase;
        int16_t rData = (int16_t)(lAmp * cos(rAngle));
        
        this->data[i]       = lData;
        this->data[i + 1]   = rData;
    }
}

WAVCreator::WAVCreator(WAVCreator& X)
{
    WAVCreator::~WAVCreator();
    WAVCreator::WAVCreator(
        X.fileName, X.sampleRate, X.duration,
        X.lAmp, X.lFreq, X.lPhase,
        X.rAmp, X.rFreq, X.rPhase);
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

void 
WAVCreator::createHeader(
    char* header, uint32_t sampleRate, uint16_t duration,
    uint16_t numChannels, uint16_t bitsPerSample
    )
{
    uint32_t subChunk1Size  = 16;       // 16 for PCM.
    uint16_t audioFormat    = 1;        //  1 for PCM.

    uint32_t byteRate       = sampleRate * numChannels * bitsPerSample / 8;
    uint16_t blockAlign     = numChannels * bitsPerSample / 8;
    uint32_t subChunk2Size  = byteRate * duration;

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
        cout << "Unable to open file for writing!" << endl;
        return (false);
    }
    
    char* header = new char[44];
    createHeader(header, sampleRate, duration);
    
    file.write(header, 44);
    file.write((char*)this->data, 4 * sampleRate * duration);
    
    file.flush();
    file.close();
    
    delete header;
    
    return(true);
}