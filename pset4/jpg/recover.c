/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    // init and declare
    int n = 0;
    int block_size = 512;
    FILE *inptr, *img;
    uint8_t arr[block_size];
    char fileName[8];
    
    // check if file exists
    if ((inptr = fopen("card.raw","r")) == NULL)
    {
        printf("Could not open card.raw file.\n");
        return 1;
    }

    // loop until end of the card.raw file is reached.
    while ((fread(&arr, block_size, 1, inptr)) > 0)
    {
        // check if first 4 bytes looks like it is an jpeg image 
        if (arr[0] == 0xff && arr[1] == 0xd8 && arr[2] == 0xff &&
            (arr[3] == 0xe0 || arr[3] == 0xe1 || arr[3] == 0xe2 
            || arr[3] == 0xe3 || arr[3] == 0xe4 || arr[3] == 0xe5
            || arr[3] == 0xe6 || arr[3] == 0xe7 || arr[3] == 0xe8 
            || arr[3] == 0xe9 || arr[3] == 0xea || arr[3] == 0xeb
            || arr[3] == 0xec || arr[3] == 0xed || arr[3] == 0xee 
            || arr[3] == 0xef))
        {
            // write new file ###.jpg where ### is a number
            sprintf(fileName, "%03i.jpg", n);
            
            // for the first file
            if (img == NULL && (img = fopen(fileName, "w")) != NULL)
                fwrite(&arr, block_size, 1, img);
            else {
                // for all other files starting from 001 close previous file,
                // open new one and write first block
                fclose(img);
                if ((img = fopen(fileName, "w")) != NULL)
                    fwrite(&arr, block_size, 1, img);
            }
            n++;
        } else if (img != NULL)
            fwrite(&arr, block_size, 1, img);
    }
    
    // closing last output file
    if (img) {
        fclose(img);
    }
    
    // closing input file
    fclose(inptr);
    return 0;
}
