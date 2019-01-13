// reads a raw data file looking for jpg images and moves any found images to a recover folder

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

typedef struct
{
    BYTE block_head0;
    BYTE block_head1;
    BYTE block_head2;
    BYTE block_head3;
    char block_body[508];
} __attribute__((__packed__))
BLOCK;

int main(int argc, char *argv[])
{
    // check to make sure that correct number of arguments were entered
    if (argc != 2)
    {
        fprintf(stderr, "Incorrect number of arguments entered.\n");
        return 1;
    }

    char *infile = argv[1];
    int outfile_number = 0;
    char filename[8];
    sprintf(filename, "%03i.jpg", outfile_number);
    char *outfile = filename;
    int first_image = 1;

    // open source file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // create initial outfile
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create file.\n");
        return 3;
    }

    // read next block of file
    BLOCK bl;
    fread(&bl, 1, sizeof(BLOCK), inptr);

    // check to see if the block is 512 bytes, indicating the end of the file

    while (!feof(inptr))
    {

        // check to see if block is the start of a new jpg
        if (bl.block_head0 == 0xFF && bl.block_head1 == 0xd8 && bl.block_head2 == 0xFF && (bl.block_head3 & 0xF0) == 0xE0)
        {
            // first image found
            if (first_image == 1)
            {
                // write header block to current outfile and mark that first file has been found
                fwrite(&bl, sizeof(BLOCK), 1, outptr);
                first_image = 0;
            }

            // close outfile if it's open
            else
            {
                if (outptr != NULL)
                {
                    fclose(outptr);
                }

                // increment file number
                outfile_number++;
                sprintf(filename, "%03i.jpg", outfile_number);
                outfile = filename;

                // open new outfile
                outptr = fopen(outfile, "w");
                if (outptr == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create file.\n");
                    return 3;
                }

                // write header block to current outfile
                fwrite(&bl, sizeof(BLOCK), 1, outptr);
            }
        }

        else
        {
            // check to see if first image has already been identified
            if (first_image == 0)
            {

                // write data blocks to current outfile
                fwrite(&bl, sizeof(BLOCK), 1, outptr);
            }
        }

        // reads next block of file
        fread(&bl, 1, sizeof(BLOCK), inptr);
    }

    // close outfile, close infile, completed program
    fclose(inptr);
    fclose(outptr);
    return 0;

}