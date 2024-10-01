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
    
    fseek(fptr, sizeof(WavHeader), SEEK_SET); //NOTE: BECAUSE OF THIS ONLY CERTIAN WAV FILES WORK

    //This is a bit scuffed - shouldnt really be doing manual access on vectors like this
    fread(wav->data.data, wav->wavHeader.subchunk2Size, 1, fptr);
    wav->data.top = wav->wavHeader.subchunk2Size;

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

    if(vector_append(&(dest->data), src->data.data, src->wavHeader.subchunk2Size) == false) {
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
    fwrite(&wav->wavHeader, sizeof(WavHeader), 1, output);
    fwrite(wav->data.data, sizeof(uint8_t), wav->wavHeader.subchunk2Size, output);
    vector_disp(&(wav->data), vector_print_uint8_8);
    fclose(output);

    return true;
}



































