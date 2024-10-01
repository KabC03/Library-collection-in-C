//2 Oct
#ifndef WAV_H 
#define WAV_H
#include "vector.h"



#pragma pack(push, 1)
typedef struct WavHeader{ //Thank you chatGPT :)

    char chunkID[4];        // "RIFF"
    uint32_t chunkSize;     // Size of the entire file minus 8 bytes for the two fields not included in this count
    char format[4];         // "WAVE"
    char subchunk1ID[4];    // "fmt "
    uint32_t subchunk1Size; // Size of the fmt chunk (16 for PCM)
    uint16_t audioFormat;    // Audio format (1 for PCM)
    uint16_t numChannels;     // Number of channels (1 for mono, 2 for stereo)
    uint32_t sampleRate;     // Sampling frequency (e.g., 44100)
    uint32_t byteRate;       // Number of bytes per second (sampleRate * numChannels * bitsPerSample/8)
    uint16_t blockAlign;     // Number of bytes per sample frame (numChannels * bitsPerSample/8)
    uint16_t bitsPerSample;  // Bits per sample (8, 16, 24, etc.)
    char subchunk2ID[4];     // "data"
    uint32_t subchunk2Size;  // Size of the data chunk
} WavHeader;
#pragma pack(pop)


typedef struct Wav {

    WavHeader wavHeader;
    Vector data;
} Wav;


/*
TODO:
- Initialise a wav struct
- Append to a wav
- Convolve two wavs
- Trim a wav
- Generate a wav from FT coefficients
- Reconstruct a wav from struct
*/

bool wav_init(Wav *wav, FILE *fptr);
bool wav_append(Wav *dest, Wav *src);
bool wav_reconstruct(Wav *wav, char *name);

#endif 


































