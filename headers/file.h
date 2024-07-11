#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>

// Déclaration des fonctions pour la gestion des fichiers binaires
char* lire_fichier(const char* chemin_fichier);
int ecrire_fichier(const char* chemin_fichier, const char* contenu);
int ajouter_fichier(const char* chemin_fichier, const char* contenu);
int supprimer_fichier(const char* chemin_fichier);
int auto_increment(const char* chemin_fichier);

#endif // FILE_UTILS_H
