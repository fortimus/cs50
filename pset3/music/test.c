#include "cs50.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char s;
    printf("test: ");
    s = fgetc(stdin);
    if (s == "")
    {
        printf("hopefully you typed nothing\n");
    }
    else
    {
        printf("hopefully you typed something\n");
    }
}