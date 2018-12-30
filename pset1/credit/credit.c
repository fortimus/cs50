#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    long long n;

    //collect user card number and verify that it's a positive number
    do
    {
        n = get_long_long("Credit Card #: ");

    }
    while (n < 0);

    //determines the length of the number that was entered
    int nLen = 0;
    long long nCount = n;

    do
    {
        nCount = nCount / 10;
        nLen++;
    }
    while (nCount > 0);

    //determines the card type 1 = Visa, 2 = MC, 3 = AMEX
    //ld references Leading Digits
    int cardType;
    int lD = n / pow(10, nLen - 2);

    if (lD == 34 || lD == 37)
    {
        cardType = 3;
    }
    else if (lD > 50 && lD < 56)
    {
        cardType = 2;
    }
    else if (lD > 39 && lD < 50)
    {
        cardType = 1;
    }
    else
    {
        cardType = 0;
    }

    //determine if card length is valid for the card type

    int lenValid;

    if (cardType == 1 && nLen == 13)
    {
        lenValid = 1;
    }
    else if (cardType == 1 && nLen == 16)
    {
        lenValid = 1;
    }
    else if (cardType == 2 && nLen == 16)
    {
        lenValid = 1;
    }
    else if (cardType == 3 && nLen == 15)
    {
        lenValid = 1;
    }
    else
    {
        lenValid = 0;
    }

    //run Luhn algorithm validation

    //don't proceed if card is already determined to be invalid
    if (lenValid == 0 || cardType == 0)
    {
        printf("INVALID\n");
    }

    //proceed with validation performing calculation each time
    else
    {
        char tempN[16];
        int place = 0;
        int dig1;
        int dig2;
        int dig3;
        sprintf(tempN, "%lld", n); //converts the number received to string

        //character will be converted to ASCII value and then have 48 subracted to get corresponding decimal value (e.g. 0 is ASCII 48)

        //only used if card has 16 characters
        if (nLen == 16)
        {
            dig1 = tempN[place] - 48;
            place++;
        }
        else
        {
            dig1 = 0;
        }

        //for cards with 13 or 15 characters
        if (nLen > 13)
        {
            dig2 = tempN[place] - 48;
            place++;
            dig3 = tempN[place] - 48;
            place++;
        }
        else
        {
            dig2 = 0;
            dig3 = 0;
        }

        //for all cards
        int dig4 = tempN[place] - 48;
        place++;

        int dig5 = tempN[place] - 48;
        place++;

        int dig6 = tempN[place] - 48;
        place++;

        int dig7 = tempN[place] - 48;
        place++;

        int dig8 = tempN[place] - 48;
        place++;

        int dig9 = tempN[place] - 48;
        place++;

        int dig10 = tempN[place] - 48;
        place++;

        int dig11 = tempN[place] - 48;
        place++;

        int dig12 = tempN[place] - 48;
        place++;

        int dig13 = tempN[place] - 48;
        place++;

        int dig14 = tempN[place] - 48;
        place++;

        int dig15 = tempN[place] - 48;
        place++;

        int dig16 = tempN[place] - 48;
        place++;

        //checkDig variables will be used to double the necessary digits and sum the digits when the result is larger than 9

        int checksum;
        int checkDig1;
        int checkDig3;
        int checkDig5;
        int checkDig7;
        int checkDig9;
        int checkDig11;
        int checkDig13;
        int checkDig15;

        if (dig1 > 4)
        {
            checkDig1 = (dig1 * 2) - 9;
        }
        else
        {
            checkDig1 = dig1 * 2;
        }

        if (dig3 > 4)
        {
            checkDig3 = (dig3 * 2) - 9;
        }
        else
        {
            checkDig3 = dig3 * 2;
        }

        if (dig5 > 4)
        {
            checkDig5 = (dig5 * 2) - 9;
        }
        else
        {
            checkDig5 = dig5 * 2;
        }

        if (dig7 > 4)
        {
            checkDig7 = (dig7 * 2) - 9;
        }
        else
        {
            checkDig7 = dig7 * 2;
        }

        if (dig9 > 4)
        {
            checkDig9 = (dig9 * 2) - 9;
        }
        else
        {
            checkDig9 = dig9 * 2;
        }

        if (dig11 > 4)
        {
            checkDig11 = (dig11 * 2) - 9;
        }
        else
        {
            checkDig11 = dig11 * 2;
        }

        if (dig13 > 4)
        {
            checkDig13 = (dig13 * 2) - 9;
        }
        else
        {
            checkDig13 = dig13 * 2;
        }

        if (dig15 > 4)
        {
            checkDig15 = (dig15 * 2) - 9;
        }
        else
        {
            checkDig15 = dig15 * 2;
        }

        checksum = dig2 + dig4 + dig6 + dig8 + dig10 + dig12 + dig14 + dig16 + checkDig1 + checkDig3 + checkDig5 + checkDig7 + checkDig9 +
                   checkDig11 + checkDig13 + checkDig15;

        int numValid;

        if (checksum % 10 == 0)
        {
            numValid = 1;
        }
        else
        {
            numValid = 0;
        }

        if (numValid == 1)
        {
            switch (cardType)
            {
                case 1:
                    printf("VISA\n");
                    break;
                case 2:
                    printf("MASTERCARD\n");
                    break;
                case 3:
                    printf("AMEX\n");
                    break;
                default:
                    printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}