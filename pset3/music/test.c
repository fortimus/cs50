#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    string note_range = "CXDXEFXGXAXB"; //X represents placeholder for counting natural semitones

    string note = get_string("Enter Note: ");

    printf("strlen(note_range): %lu\n", strlen(note_range));
    printf("strlen(strchr(note_range), note[0]): %lu\n", strlen(strchr(note_range, note[0])));

    float semitone = strlen(note_range) - strlen(strchr(note_range, note[0]));

    printf("semitone: %f\n", semitone);
    if (note[1] == '#')
    {
        semitone = semitone + (12 * (atoi(&note[2]) - 5));
        semitone++;
    }
    else if (note[2] == 'b')
    {
        semitone = semitone + (12 * (atoi(&note[2]) - 5));
        semitone--;
    }
    else
    {
        semitone = semitone + (12 * (atoi(&note[1]) - 5));
    }

    float frequency = round(523 * pow(2,(semitone/12)));

    printf("%f\n", semitone);
    printf("%f\n", frequency);
}