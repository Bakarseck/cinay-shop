#include "headers/file.h"
#include "headers/user.h"
#include <stdlib.h>
#include <string.h>

// Fonction pour lire un fichier binaire et retourner son contenu
char *lire_fichier(const char *chemin_fichier)
{
     // Ouvre le fichier en mode lecture binaire ("rb")
     FILE *fichier = fopen(chemin_fichier, "rb");
     if (fichier == NULL)
     {
          perror("Erreur d'ouverture du fichier");
          return NULL;
     }

     // Se déplace à la fin du fichier pour obtenir la taille du fichier
     fseek(fichier, 0, SEEK_END);
     long taille = ftell(fichier);
     fseek(fichier, 0, SEEK_SET);

     // Alloue la mémoire pour le contenu du fichier (+1 pour le caractère nul terminant)
     char *contenu = malloc(taille + 1);
     if (contenu)
     {
          // Lit le contenu du fichier
          fread(contenu, 1, taille, fichier);
          // Ajoute le caractère nul terminant à la fin de la chaîne
          contenu[taille] = '\0';
     }

     // Ferme le fichier
     fclose(fichier);
     return contenu;
}

int ecrire_fichier(const char *chemin_fichier, const char *contenu)
{
     // Ouvre le fichier en mode écriture binaire ("wb")
     FILE *fichier = fopen(chemin_fichier, "wb");
     if (fichier == NULL)
     {
          perror("Erreur d'ouverture du fichier");
          return -1;
     }

     // Écrit le contenu dans le fichier
     size_t longueur = strlen(contenu);
     if (fwrite(contenu, sizeof(char), longueur, fichier) < longueur)
     {
          perror("Erreur d'écriture dans le fichier");
          fclose(fichier);
          return -1;
     }

     // Ferme le fichier
     fclose(fichier);
     return 0;
}

int ajouter_fichier(const char *chemin_fichier, const char *contenu)
{
     // Ouvre le fichier en mode ajout binaire ("ab")
     FILE *fichier = fopen(chemin_fichier, "ab");
     if (fichier == NULL)
     {
          perror("Erreur d'ouverture du fichier");
          return -1;
     }

     // Écrit le contenu à la fin du fichier
     size_t longueur = strlen(contenu);
     if (fwrite(contenu, sizeof(char), longueur, fichier) < longueur)
     {
          perror("Erreur d'ajout dans le fichier");
          fclose(fichier);
          return -1;
     }

     // Ferme le fichier
     fclose(fichier);
     return 0;
}

int supprimer_fichier(const char *chemin_fichier)
{
     // Supprime le fichier
     if (remove(chemin_fichier) == 0)
     {
          return 0;
     }
     else
     {
          perror("Erreur de suppression du fichier");
          return -1;
     }
}

int auto_increment(const char *chemin_fichier)
{
     FILE *fichier = fopen(chemin_fichier, "r");

     if (fichier == NULL)
     {
          return 0;
     }

     int id = 0;
     User userTemp;

     while (fscanf(fichier, "%d %s %s %s", &userTemp.user_id, userTemp.nom, userTemp.prenom, userTemp.mot_de_passe) == 4)
     {
          id = userTemp.user_id;
     }

     fclose(fichier);

     return id + 1;
}