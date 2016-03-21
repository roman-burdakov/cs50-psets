/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * resizes image by n times.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    if (n <= 0 || n > 100) {
        printf("Currently only positive resize from 1 to 100 is supported.\n");
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // new header 
    BITMAPFILEHEADER outBf = bf;
    BITMAPINFOHEADER outBi = bi;
    // new width and height
    outBi.biWidth *= n;
    outBi.biHeight *= n;
    // new padding
    int newPadding =  (4 - (outBi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // new size image
    outBi.biSizeImage = (sizeof(RGBTRIPLE) * outBi.biWidth + newPadding) 
        * abs(outBi.biHeight);
    // new file size
    outBf.bfSize = outBi.biSizeImage + outBf.bfOffBits;
    
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&outBf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outBi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // an array to store single row with result of resizing
    RGBTRIPLE arr[outBi.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // copy corresponding triple n times
            for (int k = 0; k < n; k++){
                int x = n * j + k;
                arr[x] = triple;
            }
        }
        // duplicate current row n times
        for (int l = 0; l < n; l++) {
            //copying the array to fulfill vertical enlargement
            for (int k = 0; k < outBi.biWidth; k++){
                fwrite(&arr[k], sizeof(RGBTRIPLE), 1, outptr);
            }
            // add new padding
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over original padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
