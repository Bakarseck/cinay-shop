#include <stdio.h>
#include <string.h>

void chiffrerCesar(char* texte, int decalage) {
    int i;
    char c;

    for (i = 0; texte[i] != '\0'; i++) {
        c = texte[i];

        if (c >= 'a' && c <= 'z') {
            c = (c - 'a' + decalage) % 26 + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            c = (c - 'A' + decalage) % 26 + 'A';
        }

        texte[i] = c;
    }
}

void dechiffrerCesar(char* texte, int decalage) {
    chiffrerCesar(texte, 26 - decalage);
}

int main() {
    char texte[100];
    int decalage;

    printf("Entrez le texte à chiffrer : ");
    fgets(texte, sizeof(texte), stdin);
    // Enlever le caractère de nouvelle ligne à la fin de la chaîne de caractères
    texte[strcspn(texte, "\n")] = '\0';

    printf("Entrez le décalage : ");
    scanf("%d", &decalage);

    chiffrerCesar(texte, decalage);
    printf("Texte chiffré : %s\n", texte);

    dechiffrerCesar(texte, decalage);
    printf("Texte déchiffré : %s\n", texte);

    return 0;
}
