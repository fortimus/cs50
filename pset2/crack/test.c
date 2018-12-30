#include <crypt.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    string hash = crypt("AAAAA", "50");
    printf("%s\n", hash);

}