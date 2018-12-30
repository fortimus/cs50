#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;

    //prompt user for number of blocks and verify between 0 and 24
    do
    {
        n = get_int("Number of blocks: ");
    }
    while (n < 0 || n > 23);

    for (int i = 0; i < n; i++)
    {

        //print white space in front of pyramid. Counts total rows (minus 1) and decrements each cycle
        for (int j = n - 1; i < j; j--)
        {
            printf(" ");
        }

        //print blocks. Starts with total rows (minus 1) minus the current row (e.g. zero row of 5 block would be 4)
        //and increments each cycle until total blocks reached
        for (int k = n - i - 1; k < n; k++)
        {
            printf("#");
        }

        //print space between pyramids
        printf("  ");

        //print second set of blocks using same logic as above
        for (int l = n - i - 1; l < n; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}