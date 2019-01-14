// creates a copy of a BMP larger or smaller based on user input

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // checks to make sure the correct input format was used
    if (argc != 4)
    {
        fprintf(stderr, "Incorrect number of arguments entered.\n");
        return 1;
    }

    // assigns arguments to variables
    float resize_value = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open infile
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open outfile
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile BITMAPFILEHEADER
    BITMAPFILEHEADER bf_infile;
    fread(&bf_infile, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile BITMAPINFOHEADER
    BITMAPINFOHEADER bi_infile;
    fread(&bi_infile, sizeof(BITMAPINFOHEADER), 1, inptr);

    // check infile to ensure that it's a BMP file
    if (bf_infile.bfType != 0x4d42 || bf_infile.bfOffBits != 54 ||
        bi_infile.biSize != 40 || bi_infile.biCompression != 0 || bi_infile.biBitCount != 24)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Input file is not an uncompressed, 24-bit BMP.\n");
        return 4;
    }

    // define values for outfile BITMAPINFOHEADER
    BITMAPINFOHEADER bi_outfile;
    bi_outfile = bi_infile;
    bi_outfile.biWidth = bi_infile.biWidth * resize_value;
    bi_outfile.biHeight = bi_infile.biHeight * resize_value;

    // determine padding for infile and outfile scanlines
    int padding_infile = (4 - (bi_infile.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_outfile = (4 - (bi_outfile.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_outfile.biSizeImage = abs(bi_outfile.biHeight) * ((abs(bi_outfile.biWidth) * sizeof(RGBTRIPLE)) + padding_outfile);

    // define values for outfile BITMAPFILEHEADER
    BITMAPFILEHEADER bf_outfile;
    bf_outfile = bf_infile;
    bf_outfile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
                        bi_outfile.biSizeImage; // *note, BITMAPFILEHEADER + BITMAPINFOHEADER + image


    // write the new BITMAPFILEHEADER and BITMAPINFOHEADER to the outfile
    fwrite(&bf_outfile, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi_outfile, sizeof(BITMAPINFOHEADER), 1, outptr);


    // enlarges file for resize_value >= 1
    if (resize_value >= 1)
    {
        // read the scanline pixels from the infile
        for (int i = 0, biHeight = abs(bi_infile.biHeight); i < biHeight; i++)
        {
            for (int row_repeat = 0; row_repeat < resize_value; row_repeat++)
            {
                for (int j = 0, biWidth = abs(bi_infile.biWidth); j < biWidth; j++)
                {
                    RGBTRIPLE triple;

                    // read each pixel
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write each pixel resize_value number of times
                    for (int pixel_repeat = 0; pixel_repeat < resize_value; pixel_repeat++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // skip scanline padding in infile, if any
                fseek(inptr, padding_infile, SEEK_CUR);

                // add padding to scanline in outfile, if any
                for (int k = 0; k < padding_outfile; k++)
                {
                    fputc(0x00, outptr);
                }

                // return pointer to beginning of scanline
                fseek(inptr, -(padding_infile + (abs(bi_infile.biWidth) * sizeof(RGBTRIPLE))), SEEK_CUR);
            }

            // return pointer to beginning of the next scanline
            fseek(inptr, padding_infile + abs(bi_infile.biWidth) * sizeof(RGBTRIPLE), SEEK_CUR);
        }
    }

    // shrinks file for resize_value < 1
    else
    {
        // determine the number of pixels and rows to skip in order to reduce the file size
        float shrink = 1 / resize_value;
        int shrink_factor = (int)shrink;

        for (int i = 0, biHeight = abs(bi_infile.biHeight); i < biHeight; i++)
        {
            // check to see if the row should be copied to the new file
            if (i % shrink_factor == 0)
            {
                for (int j = 0, biWidth = abs(bi_infile.biWidth); j < biWidth; j++)
                {
                    RGBTRIPLE triple;

                    // read each pixel
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // check to see if the pixel should be copied to the new file
                    if (j % shrink_factor == 0)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // skip scanfile padding in infile, if any
                fseek(inptr, padding_infile, SEEK_CUR);

                // insert scanfile padding in outfile, if any
                for (int k = 0; k < padding_outfile; k++)
                {
                    fputc(0x00, outptr);
                }
            }

            // skips the scanline if the row needs to be skipped
            else
            {
                fseek(inptr, padding_infile + abs(bi_infile.biWidth) * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}