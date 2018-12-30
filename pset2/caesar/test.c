#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("s: ");
    int len = strlen(s);

    for (int i = 0; i < len; i++)
    {
        char c = s[i];
        int n = s[i];
        printf("%c  ", c);
        printf("%i  ", n);
        printf("%c\n", n);
    }
}