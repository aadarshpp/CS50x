
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int contains_signature(uint8_t block[])
{
    uint8_t signature[] = {0xff, 0xd8, 0xff};
    return block[0] == signature[0] && block[1] == signature[1] && block[2] == signature[2];
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("Unable to open the file %s\n", argv[1]);
        return 1;
    }

    uint8_t block[512];
    char filename[10];
    FILE *jpeg = NULL;
    int count = 0;

    // Read the raw file in 512-byte blocks
    while (fread(block, 512, 1, raw) == 1)
    {
        if (contains_signature(block))
        {
            if (jpeg != NULL)
                fclose(jpeg);

            // Create a new file for the next JPEG
            sprintf(filename, "%03d.jpg", count);
            jpeg = fopen(filename, "w");
            if (jpeg == NULL)
            {
                printf("Unable to open the file %s\n", filename);
                fclose(raw);
                return 1;
            }
            count++;
        }

        if (jpeg != NULL)
            fwrite(block, 512, 1, jpeg);
    }

    if (jpeg != NULL)
        fclose(jpeg);

    fclose(raw);
    return 0;
}
