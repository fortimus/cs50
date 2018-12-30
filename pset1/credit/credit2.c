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

    printf("%i\n",nLen);

    //determines the card type 1 = Visa, 2 = MC, 3 = AMEX
    //ld references Leading Digits
    int cardType;
    int lD = n / pow(10,nLen - 2);
    printf("%i\n",lD);

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

    printf("%i\n",cardType);

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

    //create variables for each digit. Ones place will be represented by dig16
    long long dig1 = 0;
    long long dig2 = 0;
    long long dig3 = 0;
    long long dig4 = 0;
    long long dig5 = 0;
    long long dig6 = 0;
    long long dig7 = 0;
    long long dig8 = 0;
    long long dig9 = 0;
    long long dig10 = 0;
    long long dig11 = 0;
    long long dig12 = 0;
    long long dig13 = 0;
    long long dig14 = 0;
    long long dig15 = 0;
    long long dig16 = 0;

    //don't proceed if card is already determined to be invalid
    if (lenValid == 0 || cardType == 0)
    {
        printf("INVALID\n");
    }

    //proceed with validation performing calculation each time
    else
    {
        long long tempN = n;
        int place = 1;

        if  (nLen == 16)
        {
            dig1 = tempN / pow(10, nLen - place);
            tempN = fmod(tempN, dig1 * pow(10, nLen));
        }
        else
        {
            dig1 = 0;
        }

        if (nLen > 13)
        {
            dig2 = tempN / pow(10, nLen - place);
            tempN = fmod(tempN, dig2 * pow(10, nLen - place));
            place++;

            dig3 = tempN / pow(10, nLen - place);
            tempN = fmod(tempN, dig3 * pow(10, nLen - place));
            place++;
        }
        else
        {
            dig2 = 0;
            dig3 = 0;
        }

        dig4 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig4 * pow(10, nLen - place));
        place++;

        dig5 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig5 * pow(10, nLen - place));
        place++;

        dig6 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig6 * pow(10, nLen - place));
        place++;

        dig7 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig7 * pow(10, nLen - place));
        place++;

        dig8 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig8 * pow(10, nLen - place));
        place++;

        dig9 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig9 * pow(10, nLen - place));
        place++;

        dig10 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig10 * pow(10, nLen - place));
        place++;

        dig11 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig11 * pow(10, nLen - place));
        place++;

        dig12 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig12 * pow(10, nLen - place));
        place++;

        dig13 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig13 * pow(10, nLen - place));
        place++;

        dig14 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig14 * pow(10, nLen - place));
        place++;

        dig15 = tempN / pow(10, nLen - place);
        tempN = fmod(tempN, dig15 * pow(10, nLen - place));
        place++;

        dig16 = tempN / pow(10, nLen - place);

        int checksum;
        int checkDig2;
        int checkDig4;
        int checkDig6;
        int checkDig8;
        int checkDig10;
        int checkDig12;
        int checkDig14;
        int checkDig16;

        if (dig2 > 4)
        {
            checkDig2 = (dig2 * 2) - 9;
        }
        else
        {
            checkDig2 = dig2 * 2;
        }

        if (dig4 > 4)
        {
            checkDig4 = (dig4 * 2) - 9;
        }
        else
        {
            checkDig4 = dig4 * 2;
        }

        if (dig6 > 4)
        {
            checkDig6 = (dig6 * 2) - 9;
        }
        else
        {
            checkDig6 = dig6 * 2;
        }

        if (dig8 > 4)
        {
            checkDig8 = (dig8 * 2) - 9;
        }
        else
        {
            checkDig8 = dig8 * 2;
        }

        if (dig10 > 4)
        {
            checkDig10 = (dig10 * 2) - 9;
        }
        else
        {
            checkDig10 = dig10 * 2;
        }

        if (dig12 > 4)
        {
            checkDig12 = (dig12 * 2) - 9;
        }
        else
        {
            checkDig12 = dig12 * 2;
        }

        if (dig14 > 4)
        {
            checkDig14 = (dig14 * 2) - 9;
        }
        else
        {
            checkDig14 = dig14 * 2;
        }

        if (dig16 > 4)
        {
            checkDig16 = (dig16 * 2) - 9;
        }
        else
        {
            checkDig16 = dig16 * 2;
        }

        checksum = dig1 + dig3 + dig5 + dig7 + dig9 + dig11 + dig13 + dig15 + checkDig2 + checkDig4 + checkDig6 + checkDig8 + checkDig10 + checkDig12 + checkDig14 + checkDig16;

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
            switch(cardType)
            {
                case '1':
                    printf("VISA\n");
                    break;
                case '2':
                    printf("MASTERCARD\n");
                    break;
                case '3':
                    printf("AMEX\n");
                default:
                    printf("INVALID\n");
            }
        }
    }
}