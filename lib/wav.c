#include "wav.h"

/**
 * @brief :: Initialises a Wav data structure 
 *
 * @param :: *wav :: Wav structure to be initialised 
 * @param :: *fptr :: File pointer of source wav file 
 * 
 * @return :: bool :: Indication of if wav initialisation was successful 
 */
bool wav_init(Wav *wav, FILE *fptr) {

    

    if(fread(&(wav->wavHeader), sizeof(WavHeader), 1, fptr) != 1) {
        return false; //Unable to read wav file
    }
    /*
    if(strcmp(wav->wavHeader.chunkID, "RIFF") != 0 || strcmp(wav->wavHeader.format, "WAVE") != 0) {
        //Check for valid wav header
        return false;
    }
    */
    if(vector_init(&(wav->data), sizeof(uint8_t), wav->wavHeader.subchunk2Size) == false) {
        return false;
    }



    //Fseek to the data segment
    
    if(fseek(fptr, sizeof(WavHeader), SEEK_SET) != 0) {//NOTE: BECAUSE OF THIS ONLY CERTIAN WAV FILES WORK
        vector_destroy(&(wav->data));
        return false; 
    }

    if(vector_fread_append(&(wav->data), fptr, wav->wavHeader.subchunk2Size) == NULL) {
        return false;
    }

    return true;
}



/**
 * @brief :: Append a wav to another wav. The destinations parameters are used.Both wavs are unchanged upon failure.
 *
 * @param :: *dest :: Destination Wav structure
 * @param :: *src :: Source Wav structure 
 * 
 * @return :: bool :: Indication of if append was successful 
 */
bool wav_append(Wav *dest, Wav *src) {

    if(vector_append(&(dest->data), src->data.data, src->wavHeader.subchunk2Size) == NULL) {
        return false;
    }

    dest->wavHeader.subchunk2Size += src->wavHeader.subchunk2Size;
    dest->wavHeader.chunkSize = (sizeof(WavHeader) - 8) + dest->wavHeader.subchunk2Size;

    return true;
}





/**
 * @brief :: Reconstruct a wav from its struct 
 *
 * @param :: *wav :: Wav to reconstruct 
 * @param :: *name :: Reconstructed wav file name
 * 
 * @return :: bool :: Indication of if reconstruction was successful 
 */
bool wav_reconstruct(Wav *wav, char *name) {

    FILE *output = fopen(name, "wb");
    if(output == NULL) {
        return false;
    }
    if(fwrite(&wav->wavHeader, sizeof(WavHeader), 1, output) != 1) {
        goto close;
    }
    if(fwrite(wav->data.data, sizeof(uint8_t), wav->wavHeader.subchunk2Size, output) != wav->wavHeader.subchunk2Size) {
        goto close;
    }


    if(fclose(output) != 0) {
        return false;
    }

    return true;


close:
    fclose(output);
    return false;
} 




/**
 * @brief :: Destroy a wav and associated memory 
 *
 * @param :: *wav :: Wav to destroy 
 * 
 * @return :: void 
 */
bool wav_destroy(Wav *wav) {

    vector_destroy(&(wav->data));

    return true;
}


































