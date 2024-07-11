#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

// Fonction pour lire un fichier et retourner son contenu
char* lire_fichier(const char* chemin_fichier);

// Fonction pour écrire du texte dans un fichier
int ecrire_fichier(const char* chemin_fichier, const char* contenu);

// Fonction pour ajouter du texte à la fin d'un fichier
int ajouter_fichier(const char* chemin_fichier, const char* contenu);

// Fonction pour supprimer un fichier
int supprimer_fichier(const char* chemin_fichier);

#endif
