#include "../headers/header.h"

const char *USER_FILE = "../data/user.bin";
const char *VENTES_FILE = "../data/ventes.bin";
const char *CATEGORY_FILE = "../data/category.bin";
const char *PRODUITS_FILE = "../data/produits.bin";

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

char *chiffrerCesar(char *texte, int decalage)
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

char *dechiffrerCesar(char *texte, int decalage)
{
     return (texte, 26 - decalage);
}

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