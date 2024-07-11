#include <stdio.h>
#include "headers/user.h"
#include "headers/file.h"
#include <string.h>
#include "headers/utils.h"

int ajouter_utilisateur()
{

     User user;

     printf("Veuillez saisir votre nom: \n");
     scanf("%s", &user.nom);

     printf("Veuillez saisir votre prénom: \n");
     scanf("%s", &user.prenom);

     printf("Veuillez saisir votre mot de passe: \n");
     scanf("%s", &user.mot_de_passe);

     const char line[255];

     int id = 0;
     id = auto_increment(USER_FILE);

     printf("%d", id);

     sprintf(line, "%d %s %s %s \n", id, user.nom, user.prenom, user.mot_de_passe);

     ajouter_fichier(USER_FILE, line);
}

int connexion()
{

     FILE *fichier = fopen(USER_FILE, "r");

     if (fichier == NULL)
     {
          return -1;
     }

     User userTemp;

     char login[50];
     char password[50];
     char chiffre[50];
     char déchiffre[50];

     printf("Veuillez entrez votre login:\n");
     scanf("%s", login);

     printf("Veuillez entrez votre password:\n");

     system("stty -echo");
     scanf("%s", password);
     system("stty echo");

     while (
         fscanf(fichier, "%d %s %s %s %s %s %s", &userTemp.user_id, userTemp.nom, userTemp.prenom, userTemp.login, userTemp.telephone, userTemp.mot_de_passe, userTemp.role) == 7)
     {

          if (strcmp(login, userTemp.login) == 0)
          {
               strcpy(chiffre, password);
               strcpy(déchiffre, userTemp.mot_de_passe);

               chiffrerCesar(chiffre, 10);
               dechiffrerCesar(déchiffre, 10);

               if (strcmp(chiffre, userTemp.mot_de_passe) == 0)
               {
                    if (strcmp(userTemp.role, "ADMIN") == 0)
                    {
                         fclose(fichier);
                         return 0;
                    }
                    else if (strcmp(userTemp.role, "USER") == 0)
                    {
                         fclose(fichier);
                         return 1;
                    }
                    else if (strcmp(userTemp.role, "USERBLOQUE") == 0)
                    {
                         fclose(fichier);
                         return 2;
                    }
               }
               else
               {
                    fclose(fichier);
                    return -1;
               }
          }
     }

     fclose(fichier);
     return -1;
}

void afficherMenuAdmin()
{
     int choix;

     while (1)
     {
          printf("--- Menu Administrateur ---\n");
          printf("1. Ajouter un utilisateur\n");
          printf("2. Ajouter une catégorie\n");
          printf("3. Ajouter un produit\n");
          printf("4. Lister les utilisateurs\n");
          printf("5. Lister les catégories\n");
          printf("6. Lister les produits\n");
          printf("7. Déconnexion\n");
          printf("Choisissez une option: ");
          scanf("%d", &choix);

          switch (choix)
          {
          case 1:
               // Ajouter un utilisateur
               break;
          case 2:
               // Ajouter une catégorie
               break;
          case 3:
               // Ajouter un produit
               break;
          case 4:
               // Lister les utilisateurs
               break;
          case 5:
               break;
          case 6:
               break;
          case 7:
               printf("Déconnexion réussie.\n");
               exit(0);
               return;
          default:
               printf("Option invalide. Veuillez réessayer.\n");
               break;
          }
     }
}

void afficherMenuUser()
{
     int choix;

     while (1)
     {
          printf("--- Menu Utilisateur ---\n");
          printf("1. Effectuer une vente\n");
          printf("2. Imprimer l'état du jour\n");
          printf("3. Lister les produits\n");
          printf("4. Déconnexion\n");
          printf("Choisissez une option: ");
          scanf("%d", &choix);

          switch (choix)
          {
          case 1:
               break;
          case 2:
               break;
          case 3:
               break;
          case 4:
               printf("Déconnexion réussie.\n");
               exit(0);
               return;
          default:
               printf("Option invalide. Veuillez réessayer.\n");
               break;
          }
     }
}