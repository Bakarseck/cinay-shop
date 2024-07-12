#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char *USER_FILE;
extern const char *VENTES_FILE;
extern const char *CATEGORY_FILE;
extern const char *PRODUITS_FILE;

typedef struct
{
     int user_id;
     char nom[50];
     char prenom[50];
     char telephone[20];
     char login[20];
     char mot_de_passe[256]; // Crypté
     char role[10];          // 'ADMIN' ou 'USER' ou 'USERBLOQUE'
} User;

typedef struct
{
     int id;
     char libelle[50];
} Category;

typedef struct
{
     int id;
     char designation[50];
     double prix;
     int quantite;
     char code[6];
     char date_ajout[20];
     int category_id;
} Product;

int ajouter_utilisateur();
User *lire_utilisateurs(int *taille);
int supprimer_utilisateur(int user_id);

void fonctionnaliteUser();
void fonctionnaliteAdmin();

void afficherMenuUser();
void afficherMenuAdmin();

int connexion();

int ajouter_categorie(Category category);
void lister_categories();

int ajouter_produit(Product product);
void lister_produits();

void ScannerInt(int *a);
int Atoi(char text[255]);
char *chiffrerCesar(char *texte, int decalage);
char *dechiffrerCesar(char *texte, int decalage);

char *lire_fichier(const char *chemin_fichier);
int ecrire_fichier(const char *chemin_fichier, const char *contenu);
int ajouter_fichier(const char *chemin_fichier, const char *contenu);
int supprimer_fichier(const char *chemin_fichier);
int auto_increment(const char *chemin_fichier);

#endif