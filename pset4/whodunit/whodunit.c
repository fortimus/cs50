// creates a copy of an image file with the noise removed

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // checks for the correct number of command line arguments
    if (argc != 3)
    {
        fprintf(stderr, "Incorrect number of arguments entered.\n");
        return 1;
    }

    // assign arguments to variables
    char *infile = argv[1];
    char *outfile = argv[2];

    // opens infile
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // create outfile
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // check to see that input file is a 24-bit uncompressed bmp
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 ||
        bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "%s is not an uncompressed 24-bit bmp.\n", infile);
        return 4;
    }

    // write outfile BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine amount of padding in the infile scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // read images pixels from infile and copy to outfile
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;

            // read the scanline pixels
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // determine if the pixel is noise. if so, convert to black, otherwise copy pixel
            if ((triple.rgbtRed == 0xFF && triple.rgbtGreen == 0x00 && triple.rgbtBlue == 0x00) ||
                (triple.rgbtRed == 0xFF && triple.rgbtGreen == 0xFF && triple.rgbtBlue == 0xFF))
            {
                triple.rgbtGreen = 0x00;
                triple.rgbtBlue = 0x00;
                triple.rgbtRed = 0x00;
            }

            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding on infile scanline
        fseek(inptr, padding, SEEK_CUR);

        // insert padding into outfile scanline
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    //close outfile
    fclose(outptr);

    // complete program
    return 0;
}