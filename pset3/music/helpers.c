// Helper functions for music

#include "cs50.h"

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //locates position of division symbol in argument
    int divpos = strlen(fraction) - strlen(index(fraction, 47));

    //extract numerator from argument
    double numer;
    char sNumerator[divpos + 1];
    for (int i = 0; i < divpos; i++)
    {
        sNumerator[i] = fraction[i];
        numer = atoi(sNumerator);
    }

    //extract denominator from argument
    double denom;
    char sDenominator[strlen(fraction) - divpos];
    for (int i = 0; i < strlen(fraction) - divpos - 1; i++)
    {
        sDenominator[i] = fraction[i + divpos + 1];
        denom = atoi(sDenominator); 
    }

    //convert fraction value to number of eighth notes
    double value = (numer / denom) / 0.125;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    if (s[0] == "\n" && s[1] == "\0")
    {
        return 1;
    }
}
