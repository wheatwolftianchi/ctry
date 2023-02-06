#include "comp0019.h"
#include <stdlib.h>

void Encode(FILE *in_file, FILE *out_file) {
  // Supress unused warnings.
  UNUSED(in_file);
  UNUSED(out_file);
  // Code goes here.
  // initialize the buffer to 3 bytes
  unsigned char buffer[4];
  // check if the in_file contains more than 3 bytes
  // read the first 4 bytes of the file(number of bases) and write it to the out_file
  size_t nob = fread(buffer, 1, 4, in_file);
  if (nob != 4)
  {
    unsigned char zeros[4] = {0,0,0,0};
    fwrite(zeros, 1, 4, out_file);
    return;
  }
  // write the first 4 bytes to the out_file
  fwrite(buffer, 1, 4, out_file);
  // convert the first 4 bytes to an unsigned int
  unsigned int numofbase = 0;
  numofbase |= buffer[0] << 24;
  numofbase |= buffer[1] << 16;
  numofbase |= buffer[2] << 8;
  numofbase |= buffer[3] << 0;
  if (numofbase == 0)
  {
    return;
  }
  // 1 byte contains 4 bases
  unsigned int numofbyte = numofbase/4;
  // initialize memory to store the bases using malloc
  unsigned char *bases = malloc(numofbase);
  unsigned char *output = malloc(numofbyte);
  unsigned char *bytesofbase = malloc(numofbyte);
  int outputcount = 0;
  // read the bases from the in_file and store them in the bytesofbase pointer
  size_t noby = fread(bytesofbase, 1, numofbyte, in_file);
  // check if the number of bases read is equal to the number of bases in the file, 1 byte contains 4 bases
  /*if (noby != numofbyte)
  {
    unsigned char zeros[4] = {0,0,0,0};
    fwrite(zeros, 1, 4, out_file);
    return;
  }*/
  // seperate the bases and save to the base pointer
  for (unsigned int i = 0; i < numofbyte; i++)
  {
    unsigned char byte = bytesofbase[i];
    unsigned char base1 = byte >> 6;
    unsigned char base2 = (byte >> 4) & 0x03;
    unsigned char base3 = (byte >> 2) & 0x03;
    unsigned char base4 = byte & 0x03;
    bases[i*4] = base1;
    bases[i*4+1] = base2;
    bases[i*4+2] = base3;
    bases[i*4+3] = base4;
  }
  // initialize LZW dictionary to 256 and 3D for current next and index using malloc
  unsigned char *dictionary = malloc(256*3);
  int dictsize = 256;
  int dictcount = 1;
  // start to stick the bases into the dictionary and expand the dictionary when necessary
  unsigned char current;
  unsigned char next;
  for (unsigned int i = 0; i < numofbase; i++)
  {
    if (i < numofbase-1)    {    
      unsigned char current = bases[i];
      unsigned char next = bases[i+1];
    }
    else{
      unsigned char current = bases[i];
    }
    // check the dictionary to see if the bases are in the dictionary and if it needs to be expanded
    if (dictcount == dictsize)
    {
      // expand the dictionary
      dictsize += 128;
      dictionary = realloc(dictionary, dictsize*3);
    }    
    // check if the bases are in the dictionary
    int found = 0;
    for (int k = 1; k < dictcount; k++)
    {
      if (dictionary[k] == current && dictionary[2*k] == next)
      {
        // add the bases to the output
        output[outputcount] = dictionary[3*k];
        i++;
        outputcount++;
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      // add the bases to the dictionary
      dictionary[dictcount] = current;
      dictionary[dictcount * 2] = next;
      dictionary[dictcount * 3] = dictcount;
      // add the bases to the output
      output[outputcount] = current;
      dictcount++;
      outputcount++;
    } 
  }
  //combine the output and fill the last byte with 0
  // 1 byte contains 4 bases
  unsigned int numofoutputbyte = outputcount/4;
  unsigned char *outputbytes = malloc(numofoutputbyte);
  for (unsigned int i = 0; i < numofoutputbyte; i++)
  {
    unsigned char byte = 0;
    byte |= output[i*4] << 6;
    byte |= output[i*4+1] << 4;
    byte |= output[i*4+2] << 2;
    byte |= output[i*4+3] << 0;
    outputbytes[i] = byte;
  }
  // write the output to the out_file
  fwrite(outputbytes, 1, numofoutputbyte, out_file);
}
