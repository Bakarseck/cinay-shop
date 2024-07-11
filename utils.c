#include "utils.h"
#include <stdio.h>


int Atoi(char text[255])
{
    size_t i;
    for (i = 0; i < strlen(text); i++)
    {
        int r = text[i];
        if ((r < 48 || r > 57))
        {
            return -1;
        }
    }
    return 1;
}

void ScannerInt(int *a)
{
    char text[255];

invalid:
    scanf("%[^\n]s", text);
    short b = Atoi(text);
    if (b == -1)
    {
        printf("Please Enter a valid Int\n");
        goto invalid;
    }
    *a = atoi(text);

    if (*a > 1000000)
    {
        printf("Please Enter a valid Int\n");
        goto invalid;
    }
}
