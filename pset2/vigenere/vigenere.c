/*
$ ./vigenere 13
Usage: ./vigenere k

$ ./vigenere
Usage: ./vigenere k

$ ./vigenere bacon and eggs
Usage: ./vigenere k

$ ./vigenere bacon
plaintext: Meet me at the park at eleven am
ciphertext: Negh zf av huf pcfx bt gzrwep oz
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check to make sure that one argument was entered on the command line
    if (argc != 2)
    {
        printf("Input Error: Incorrect number of arguments.\n");
        return (1);
    }

    string key_text = argv[1]; //move command line argument into key text variable
    for (int i = 0; i < strlen(key_text); i++)
    {
        key_text[i] = tolower(key_text[i]);
    }

    for (int i = 0; i < strlen(key_text); i++)
    {
        if (isupper(key_text[i]) == 0 && islower(key_text[i]) == 0)
        {
            printf("Input Error: Incorrect format for keyword.\n");
            return (1);
        }
    }

    string plain_text = get_string("plaintext: "); //prompt user for plain text to be encrypted

    int key_location = 0; //initialize location tracking for key
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plain_text); i++)
    {
        if (isupper(plain_text[i]) || islower(plain_text[i]))
        {
            //convert uppercase letters to cipher value
            char cipher_text = toupper(plain_text[i]) + key_text[(key_location % strlen(key_text))] - 'a';
            if (cipher_text > 'Z')
            {
                cipher_text = cipher_text - 26;
            }
            if (islower(plain_text[i]))
            {
                printf("%c", tolower(cipher_text));
            }
            else
            {
                printf("%c", cipher_text);
            }
            key_location++;
        }
        //for characters that are not a letter => pass character through unmodified
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
    return (0);
}