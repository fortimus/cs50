// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // locates position of division symbol in argument
    int divpos = strlen(fraction) - strlen(strchr(fraction, 47));

    // extract numerator from argument
    double numer;
    char sNumerator[divpos + 1];
    for (int i = 0; i < divpos; i++)
    {
        sNumerator[i] = fraction[i];
        numer = atoi(sNumerator);
    }

    // extract denominator from argument
    double denom;
    char sDenominator[strlen(fraction) - divpos];
    for (int i = 0; i < strlen(fraction) - divpos - 1; i++)
    {
        sDenominator[i] = fraction[i + divpos + 1];
        denom = atoi(sDenominator);
    }

    // convert fraction value to number of eighth notes
    double value = (numer / denom) / 0.125;
    return (value);
}

// Calculates frequency (in Hz) of a note
// 440, 5, and 3 hard coded as base frequency for calculation is A4 @ 440Hz. C5 (A4 + 3), as the start of a new octive
// is used for calculations

int frequency(string note)
{
    string note_range = "CXDXEFXGXAXB"; // X represents placeholder for counting natural semitones

    float semitone = strlen(note_range) - strlen(strchr(note_range, note[0])); //determines distance of note from C (starting note)

    //lift or lower semitone by 12 based on distance from the 5th octive, then
    if (note[1] == '#')
    {
        semitone = semitone + (12 * (atoi(&note[2]) - 5));
        semitone++; // for sharp, increases semitone by 1
    }

    else if (note[1] == 'b')
    {
        semitone = semitone + (12 * (atoi(&note[2]) - 5));
        semitone--; // for flat, lowers semitone by 1
    }
    else
    {
        semitone = semitone + (12 * (atoi(&note[1]) - 5));
    }

    // increase calculated semitone by 3 (convert from C5 calculation to A4) and caculates frequency
    float frequency = round(440 * pow(2, ((semitone + 3) / 12)));

    return (frequency);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // checks for any values in string
    if (strcmp(s, "\0") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
