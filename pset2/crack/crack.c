/*
Design and implement a program, crack, that cracks passwords.
Implement your program in a file called crack.c in a directory called crack.
Your program should accept a single command-line argument: a hashed password.
If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error (of your choice) and exit immediately, with main returning 1 (thereby signifying an error).
Otherwise, your program must proceed to crack the given password, ideally as quickly as possible, ultimately printing the password in the clear followed by \n, nothing more, nothing less, with main returning 0.
Assume that each password has been hashed with C’s DES-based (not MD5-based) crypt function.
Assume that each password is no longer than five (5) characters. Gasp!
Assume that each password is composed entirely of alphabetical characters (uppercase and/or lowercase).

anushree:50xcIMJ0y.RXo => YES
brian:50mjprEcqC/ts => CA
bjbrown:50GApilQSG3E2 => Does not complete
lloyd:50n0AAUD.pL8g =>Does not complete
malan:50CcfIk1QrPr6 => Does not complete
maria:509nVI8B9VfuA => TF
natmelo:50JIIyhDORqMU => nope
rob:50JGnXUgaafgc => ROFL
stelios:51u8F0dkeDSbY => NO
zamyla:50cI2vYkF0YU2 => LOL

*/

#define _XOPEN_SOURCE
#include <crypt.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    if (argc == 2) //check to make sure that the correct number of arguments were entered
    {
        char *hash = argv[1];   //transfers the hash from argument into working string
        char aSalt[2]; //initialize the array for holding the salt
        int hashLen = strlen(hash);
        string letters = "\0ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        //extract the salt from the hash
        for (int i = 0; i < 2; i++)
        {
            aSalt[i] = hash[i];
        }

        //logic to cycle through all possible combinations of letters that could be used for password

        char test[6] = "\0\0\0\0\0\0";
        for (int m = 0; m < 52; m++)
        {
            for (int l = 0; l < 52; l++)
            {
                for (int k = 0; k < 52; k++)
                {
                    for (int j = 0; j < 53; j++)
                    {
                        for (int i = 0; i < 53; i++)
                        {
                            //cycles the first value in the test password
                            test[0] = letters[i];

                            //cycles the second value in the test password
                            test[1] = letters[j];


                            //cycles the third value in the test password
                            test[2] = letters[k];


                            //cycles the fourth value in the test password
                            test[3] = letters[l];


                            //cycles the fifth value in the test password
                            test[4] = letters[m];

                            //compares the test password hash to the provided hash. Matches stop the program and print the test password
                            if (strcmp(crypt(test, aSalt), hash) == 0)
                            {
                                printf("%s\n", test);
                                exit(0);
                            }

                        }
                    }
                }
            }
        }
    }
    else //exit for incorrect number of arguments
    {
        printf("Input Error: Incorrect number of arguments entered.\n");
        exit(1);
    }
}