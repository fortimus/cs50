/*
$ ./caesar 1
plaintext:  HELLO
ciphertext: IFMMP

$ ./caesar 13
plaintext:  hello, world
ciphertext: uryyb, jbeyq

$ ./caesar 13
plaintext:  be sure to drink your Ovaltine
ciphertext: or fher gb qevax lbhe Binygvar

$ ./caesar
Usage: ./caesar k

$ ./caesar 1 2 3 4 5
Usage: ./caesar k
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check to make sure that one and only one argument was entered on the command line
    if (argc == 2)
    {
        string k = argv[1];
        int key = atoi(k);

        //collect plaintext to be encoded
        string plain = get_string("plaintext: ");
        int len = strlen(plain);
        int rotator = key % 26; //adjusts key for values greater than 26

        printf("ciphertext: ");

        //conversion algorithm. this will break the string to characters and return invidual results without recombing the output into a string
        for (int i = 0; i < len; i++)
        {
            //for capital letters
            if (plain[i] > 64 && plain[i] < 91)
            {
                int p = plain[i];
                int c = p + rotator;

                //wraparound logic (key moves cyphertext beyond z)
                if (c > 90)
                {
                    c = c - 26;
                }
                printf("%c", c);
            }

            //for lowercase letters
            else if (plain[i] > 96 && plain[i] < 123)
            {

                int p = plain[i];
                int c = p + rotator;

                if (c > 122)
                {
                    c = c - 26;
                }
                printf("%c", c);
            }

            //passes through characters that are not letters
            else
            {
                printf("%c", plain[i]);
            }
        }
        printf("\n");
    }
    else
    {
        exit(1);
        printf("Input Error: Incorrect number of arguments.\n");
    }
}