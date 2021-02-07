#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

#define buffer_size (162 * 3)

    char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    FILE *file;
    unsigned long read_shift;
    unsigned long fread_read_chars;
    unsigned char base_read_chars;

    char buffer[buffer_size];
    char bytes[3];
    char chars[5];
    chars[4] = '\0';

    if (argc != 2)
    {
        printf("Usage: base64 [FILE]\n");
        exit(1);
    }

    char *filename = argv[1];

    if ((file = fopen(filename, "rb")) == NULL)
    {
        printf("Could not open file %s: %s\n", filename, strerror(errno));
        exit(1);
    }

    while ((fread_read_chars = fread(buffer, sizeof(char), buffer_size, file)) != 0)
    {
        read_shift = 0;

        if (fread_read_chars != buffer_size)
        {
            buffer[fread_read_chars] = '\0';
        }

        for (unsigned long i = 0; i < buffer_size / 3; i++)
        {
            memset(bytes, 0, 3);
            base_read_chars = 0;

            for (unsigned char i = 0; i < 3; i++)
            {
                if (buffer[read_shift] == '\0')
                {
                    if (base_read_chars == 0)
                    {
                        goto end;
                    }
                    break;
                }
                else
                {
                    bytes[i] = buffer[read_shift];
                    read_shift++;
                    base_read_chars++;
                }
            }

            chars[0] = alphabet[(bytes[0] >> 2) & 0b00111111];
            chars[1] = alphabet[((bytes[0] << 4) & 0b00110000) | ((bytes[1] >> 4) & 0b00001111)];
            chars[2] = '=';
            chars[3] = '=';
            if (base_read_chars > 1)
            {
                chars[2] = alphabet[((bytes[1] << 2) & 0b00111100) | ((bytes[2] >> 6) & 0b00000011)];
                if (base_read_chars > 2)
                {
                    chars[3] = alphabet[bytes[2] & 0b00111111];
                }
            }

            printf("%s", chars);
        }
    }

end:
    printf("\n");
    fclose(file);
    return 0;
}