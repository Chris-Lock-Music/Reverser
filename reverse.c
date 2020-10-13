// A simple program to reverse an audio file
// by Christopher Lock
// thank you to Maxim Aleksa for his help on the project

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 3)
    {
        printf("Usage: ./volume input.wav output.wav\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }


    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);


    const int CAPACITY = 200000;
    int16_t samples[CAPACITY];
    int number_of_samples = 0;

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        samples[number_of_samples] = buffer;
        number_of_samples += 1;
    }


    // write samples in reverse order (this is where you fuck with the output)
    while (number_of_samples > 0)
    {
        int16_t sample = samples[number_of_samples - 1];
        fwrite(&sample, sizeof(sample), 1, output);
        number_of_samples -= 1;
    }

    // Close files
    fclose(input);
    fclose(output);
}