#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int const BLOCK_SIZE = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure program accepts one command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open input file/memory card- check if forensic image can be open for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Declare output file
    FILE *outfile = NULL;

    // Declare file number variable to keep track of images
    int file_number = 0;

    // Declare string for file name- 4 characters for ### and .jpg and null terminator
    char file_name[8];

    // Allocate buffer for image
    BYTE temp[BLOCK_SIZE];

    // Repeat until end of card- read 512 bytes into buffer
    while (fread(temp, sizeof(BYTE), BLOCK_SIZE, file))
    {
        // If start of new jpeg
        if (temp[0] == 0xff && temp[1] == 0xd8 && temp[2] == 0xff && (temp[3] & 0xf0) == 0xe0)
        {
            // If first jpeg
            if (file_number == 0)
            {
                // Create a new file and write file name and open it
                sprintf(file_name, "%03i.jpg", file_number);
                outfile = fopen(file_name, "w");
                // Keep track of number of images
                file_number++;
                fwrite(temp, sizeof(BYTE), BLOCK_SIZE, outfile);
            }
            // Continue writing if already found jpeg but more than 512 byes
            else
            {
                fclose(outfile);
                sprintf(file_name, "%03i.jpg", file_number);
                outfile = fopen(file_name, "w");
                file_number++;
                fwrite(temp, sizeof(BYTE), BLOCK_SIZE, outfile);
            }
        }
        // If start of new jpeg
        else if (file_number != 0)
        {
            fwrite(temp, sizeof(BYTE), BLOCK_SIZE, outfile);
        }
    }

    // Close when reach end of card
    fclose(file);
    fclose(outfile);
    return 0;
}