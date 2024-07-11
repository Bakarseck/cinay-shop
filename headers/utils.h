#ifndef UTILS_H
#define UTILS_H

void ScannerInt(int *a);
int Atoi(char text[255]);
char* chiffrerCesar(char* texte, int decalage);
char* dechiffrerCesar(char* texte, int decalage);

// Déclaration des fichiers
extern const char* USER_FILE;
extern const char* VENTES_FILE;
extern const char* CATEGORY_FILE;
extern const char* PRODUITS_FILE;

#endif