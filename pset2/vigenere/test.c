#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string key_text = "BaZ"; //dummy key
    string plain_text = "BaRFoo"; //dummy plain text
    int key_location = 0; //initialize location tracking for key

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
                printf("%c",tolower(cipher_text));
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
    return(0);
}