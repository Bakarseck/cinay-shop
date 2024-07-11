#include "headers/utils.h"
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

char* chiffrerCesar(char *texte, int decalage)
{
     int i;
     char c;

     for (i = 0; texte[i] != '\0'; i++)
     {
          c = texte[i];

          if (c >= 'a' && c <= 'z')
          {
               c = (c - 'a' + decalage) % 26 + 'a';
          }
          else if (c >= 'A' && c <= 'Z')
          {
               c = (c - 'A' + decalage) % 26 + 'A';
          }

          texte[i] = c;
     }

     return texte;
}

char* dechiffrerCesar(char *texte, int decalage)
{
     return (texte, 26 - decalage);
}

// Définition des fichiers
const char *USER_FILE = "data/user.bin";
const char *VENTES_FILE = "data/ventes.bin";
const char *CATEGORY_FILE = "data/category.bin";
const char *PRODUITS_FILE = "data/produits.bin";
